//----------------------------------------------------------------------
//   Copyright 2007-2010 Mentor Graphics Corporation
//   Copyright 2013-2021 NXP B.V.
//   All Rights Reserved Worldwide
//   
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//   
//       http://www.apache.org/licenses/LICENSE-2.0
//   
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// TITLE: UVM HDL Backdoor Access support routines.
//
// These routines provide an interface to the DPI/PLI
// implementation of backdoor access used by registers.
//
// TODO implementation not done yet
//----------------------------------------------------------------------

#ifndef UVM_HDL_H_
#define UVM_HDL_H_

#include <systemc>
#include <sstream>

#include "uvmsc/base/uvm_globals.h"

#include "uvmsc/reg/uvm_sc_if.h"

namespace uvm {

#ifndef UVM_HDL_MAX_WIDTH
#define UVM_HDL_MAX_WIDTH 1024
#endif

/* 
 * VARIABLE: uvm_hdl_max_width
 *
 * Sets the maximum size bit vector for backdoor access. 
 * This parameter will be looked up by the 
 * DPI-C code using:
 *   vpi_handle_by_name(
 *     "uvm_pkg::UVM_HDL_MAX_WIDTH", 0);
 *
 * TODO - do we define a variable for UVM-SC?
 * parameter int uvm_hdl_max_width = `UVM_HDL_MAX_WIDTH;
 */

typedef sc_dt::sc_uint_base uvm_hdl_data_t;

bool uvm_hdl_check_path(const std::string& path );
bool uvm_hdl_release(const std::string& path);
bool uvm_hdl_release_time( const std::string& path, sc_core::sc_time time );

//----------------------------------------------------------------------
// Function: uvm_hdl_deposit
//
// Sets the given HDL ~path~ to the specified ~value~.
// Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

template <typename T>
bool uvm_hdl_deposit( const std::string& path, const T& value )
{
  std::string objname1, objname2;
  int idx_start = -1;
  int idx_stop = -1;
  int vidx_start = -1;
  int vidx_stop = -1;

  uvm_extract_path_index(path, objname1, idx_start, idx_stop);
  // check again, perhaps we've hit a vector
  uvm_extract_path_index(objname1, objname2, vidx_start, vidx_stop);

  /*
  std::cout << " uvm_hdl_deposit to path " << path << std::endl;
  std::cout << " objname1 " << objname1 << std::endl;
  std::cout << " idx_start: " << idx_start << std::endl;
  std::cout << " idx_stop: " << idx_stop << std::endl;

  std::cout << " objname2 " << objname2 << std::endl;
  std::cout << " vidx_start: " << vidx_start << std::endl;
  std::cout << " vidx_stop: " << vidx_stop << std::endl;
  */

  sc_core::sc_object* obj = sc_core::sc_find_object(objname2.c_str());

  if (obj == NULL)
  {
    uvm_report_error("HDL_DEPOSIT", "Object " + objname2 + " not found in design hierarchy.");
    return false;
  }

  // possibility 1: backdoor register represented by object of type sc_signal
  sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* sig_md = dynamic_cast<sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* > (obj);
  if (sig_md != NULL)
  {
    if ((idx_start != -1) && (idx_stop != -1))
    {
      uvm_report_error("HDL_DEPOSIT", "Writing part-select on sc_signal<T> is not supported. ");
      return false;
    }

    sig_md->write(value); // write all bits

    std::ostringstream str;
    str << "Value 0x" << std::hex << value << " written to " << path << ".";
    uvm_report_info("HDL_DEPOSIT", str.str(), uvm::UVM_FULL);
    return true;
  }

  // possibility 2: backdoor register represented by object of type uvm_sc_if
  uvm_sc_if<T>* interf = dynamic_cast<uvm_sc_if<T>* > (obj);
  if (interf != NULL)
  {
    if ( (idx_start > (value.length()-1)) || (idx_start < -1) ||
         (idx_stop > (value.length()-1)) || (idx_stop < -1) )
    {
      uvm_report_error("HDL_DEPOSIT", "Specified index for bit select is out of range.");
      return false;
    }

    interf->write(value, idx_start, idx_stop);
    std::ostringstream str;
    str << "Value 0x" << std::hex << value << " written to " << path << ".";
    uvm_report_info("HDL_DEPOSIT", str.str(), uvm::UVM_FULL);
    return true;
  }

  // // possibility 3: backdoor registers represented by sc_vector containing object of type uvm_sc_if or sc_signal
  sc_core::sc_vector_base* vec = dynamic_cast<sc_core::sc_vector_base* > (obj);
  if (vec != NULL)
  {
    // vector found, but no index, meaning the first index was valid
    if (vidx_start == -1)
    {
      vidx_start = idx_start;
      idx_start = -1;
      idx_stop = -1;
    }

    std::vector<sc_core::sc_object*> vec_element = vec->get_elements();

    if ( (vidx_start > (((int)vec_element.size())-1)) || (vidx_start < 0) )
    {
      uvm_report_error("HDL_DEPOSIT", "Specified index of sc_vector out of range.");
      return false;
    }

    uvm_sc_if<T>* interf = dynamic_cast<uvm_sc_if<T>* > (vec_element[vidx_start]);
    if (interf != NULL)
    {

      if ( (idx_start > (value.length()-1)) || (idx_start < -1) ||
           (idx_stop > (value.length()-1)) || (idx_stop < -1) )
      {
        uvm_report_error("HDL_DEPOSIT", "Specified index for bit select is out of range.");
        return false;
      }

      interf->write(value, idx_start, idx_stop);
      std::ostringstream str;
      str << "Value 0x" << std::hex << value << " written to " << path << ".";
      uvm_report_info("HDL_DEPOSIT", str.str(), uvm::UVM_FULL);
      return true;
    }

    sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* sig_md = dynamic_cast<sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* > (vec_element[vidx_start]);
    if (sig_md != NULL)
    {
      if ((idx_start != -1) && (idx_stop != -1))
      {
        uvm_report_error("HDL_DEPOSIT", "Writing part-select on sc_signal<T> is not supported. ");
        return false;
      }

      sig_md->write(value);
      std::ostringstream str;
      str << "Value 0x" << std::hex << value << " written to " << path << ".";
      uvm_report_info("HDL_DEPOSIT", str.str(), uvm::UVM_FULL);
      return true;
    }
  }

  uvm_report_error("HDL_DEPOSIT", "Object " + objname2 + " is not of type uvm_sc_if or sc_signal.");
  return false;
}

//----------------------------------------------------------------------
// Function: uvm_hdl_force
//
// Forces the ~value~ on the given ~path~. Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

template <typename T>
bool uvm_hdl_force( const std::string& path, const T& value )
{
  uvm_report_error("HDL_FORCE", "HDL signal force not available without DPI.");
  return false;
}

//----------------------------------------------------------------------
// Function: uvm_hdl_force_time
//
// Forces the ~value~ on the given ~path~ for the specified amount of ~force_time~.
// If ~force_time~ is 0, <uvm_hdl_deposit> is called.
// Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

template <typename T>
bool uvm_hdl_force_time( const std::string& path, const T& value, sc_core::sc_time force_time )
{
  uvm_report_error("HDL_FORCE_TIME", "HDL signal force with time not available without DPI.");
  return false;
}


//----------------------------------------------------------------------
// Function: uvm_hdl_release_and_read
//
// Releases a value previously set with <uvm_hdl_force>.
// Returns 1 if the call succeeded, 0 otherwise. ~value~ is set to
// the HDL value after the release. For 'reg', the value will still be
// the forced value until it has bee procedurally reassigned. For 'wire',
// the value will change immediately to the resolved value of its
// continuous drivers, if any. If none, its value remains as forced until
// the next direct assignment.
//----------------------------------------------------------------------

template <typename T>
bool uvm_hdl_release_and_read( const std::string& path, T& value )
{
  uvm_report_error("HDL_RELEASE_READ", "HDL signal release and read not available without DPI.");
  return false;
}


//----------------------------------------------------------------------
// Function: uvm_hdl_read()
//
// Gets the value at the given ~path~.
// Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

template <typename T>
bool uvm_hdl_read( const std::string& path, T& value )
{
  std::string objname1, objname2;
  int idx_start = -1;
  int idx_stop = -1;
  int vidx_start = -1;
  int vidx_stop = -1;

  uvm_extract_path_index(path, objname1, idx_start, idx_stop);
  // check again, perhaps we've hit a vector
  uvm_extract_path_index(objname1, objname2, vidx_start, vidx_stop);

  /*
  std::cout << " uvm_hdl_read to path " << path << std::endl;
  std::cout << " objname1 " << objname1 << std::endl;
  std::cout << " idx_start: " << idx_start << std::endl;
  std::cout << " idx_stop: " << idx_stop << std::endl;

  std::cout << " objname2 " << objname2 << std::endl;
  std::cout << " vidx_start: " << vidx_start << std::endl;
  std::cout << " vidx_stop: " << vidx_stop << std::endl;
  */
  sc_core::sc_object* obj = sc_core::sc_find_object(objname2.c_str());

  if (obj == NULL)
  {
    uvm_report_error("HDL_READ", "Object " + objname2 + " not found in design hierarchy.");
    return false;
  }

  // possibility 1: backdoor register represented by object of type sc_signal
  sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* sig_md = dynamic_cast<sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* > (obj);
  if (sig_md != NULL)
  {
    if ((idx_start != -1) && (idx_stop != -1))
    {
      uvm_report_error("HDL_DEPOSIT", "Reading part-select on sc_signal<T> is not supported. ");
      return false;
    }

    value = sig_md->read();

    std::ostringstream str;
    str << "Value 0x" << std::hex << value << " read from " << path << ".";
    uvm_report_info("HDL_READ", str.str(), uvm::UVM_FULL);
    return true;
  }

  // possibility 2: backdoor register represented by object of type uvm_sc_if
  uvm_sc_if<T>* interf = dynamic_cast<uvm_sc_if<T>* > (obj);
  if (interf != NULL)
  {
    if ( (idx_start > (value.length()-1)) || (idx_start < -1) ||
         (idx_stop > (value.length()-1)) || (idx_stop < -1) )
    {
      uvm_report_error("HDL_DEPOSIT", "Specified index for bit select is out of range.");
      return false;
    }

    value = interf->read(idx_start, idx_stop);
    std::ostringstream str;
    str << "Value 0x" << std::hex << value << " read from " << path << ".";
    uvm_report_info("HDL_READ", str.str(), uvm::UVM_FULL);
    return true;
  }

  // // possibility 3: backdoor registers represented by sc_vector containing object of type uvm_sc_if or sc_signal
  sc_core::sc_vector_base* vec = dynamic_cast<sc_core::sc_vector_base* > (obj);
  if (vec != NULL)
  {
    // vector found, but no index, meaning the first index was valid
    if (vidx_start == -1)
    {
      vidx_start = idx_start;
      idx_start = -1;
      idx_stop = -1;
    }

    std::vector<sc_core::sc_object*> vec_element = vec->get_elements();

    if ( (vidx_start > (((int)vec_element.size())-1)) || (vidx_start < 0) )
    {
      uvm_report_error("HDL_DEPOSIT", "Specified index of sc_vector out of range.");
      return false;
    }

    uvm_sc_if<T>* interf = dynamic_cast<uvm_sc_if<T>* > (vec_element[vidx_start]);
    if (interf != NULL)
    {
      if ( (idx_start > (value.length()-1)) || (idx_start < -1) ||
           (idx_stop > (value.length()-1)) || (idx_stop < -1) )
      {
        uvm_report_error("HDL_DEPOSIT", "Specified index for bit select is out of range.");
        return false;
      }

      value = interf->read(idx_start, idx_stop);
      std::ostringstream str;
      str << "Value 0x" << std::hex << value << " read from " << path << ".";
      uvm_report_info("HDL_READ", str.str(), uvm::UVM_FULL);
      return true;
    }

    sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* sig_md = dynamic_cast<sc_core::sc_signal<T, sc_core::SC_MANY_WRITERS>* > (vec_element[vidx_start]);
    if (sig_md != NULL)
    {
      if ((idx_start != -1) && (idx_stop != -1))
      {
        uvm_report_error("HDL_DEPOSIT", "Reading part-select on sc_signal<T> is not supported. ");
        return false;
      }

      value = sig_md->read();
      std::ostringstream str;
      str << "Value 0x" << std::hex << value << " read from " << path << ".";
      uvm_report_info("HDL_READ", str.str(), uvm::UVM_FULL);
      return true;
    }
  }

  uvm_report_error("HDL_READ", "Object " + objname2 + " is not of type uvm_sc_if or sc_signal.");
  return false;
}


} // namespace uvm

#endif // UVM_HDL_H_
