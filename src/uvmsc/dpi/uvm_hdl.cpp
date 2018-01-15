//----------------------------------------------------------------------
//   Copyright 2007-2010 Mentor Graphics Corporation
//   Copyright 2013 NXP B.V.
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
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

#include "uvmsc/dpi/uvm_hdl.h"

namespace uvm {

//----------------------------------------------------------------------
// Function: uvm_hdl_check_path
//
// Checks that the given HDL ~path~ exists. Returns 0 if NOT found, 1 otherwise.
//----------------------------------------------------------------------

bool uvm_hdl_check_path( const std::string& path )
{
  std::string objname;
  int id1 = -1;
  int id2 = -1;

  uvm_extract_path_index(path, objname, id1, id2);
  sc_core::sc_object* obj = sc_core::sc_find_object(objname.c_str());

  if (obj == NULL)
  {
    uvm_report_error("HDL_CHK_PATH", "Object " + objname + " not found in design hierarchy.");
    return false;
  }

  return true;
}


//----------------------------------------------------------------------
// Function: uvm_hdl_release
//
// Releases a value previously set with <uvm_hdl_force>.
// Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

bool uvm_hdl_release( const std::string& path )
{
  uvm_report_error("HDL_RELEASE", "HDL signal release not available without DPI.");
  return false;
}

//----------------------------------------------------------------------
// Function: uvm_hdl_release_time
//
// Release the value on the given ~path~ after the specified amount of ~time~.
// Returns 1 if the call succeeded, 0 otherwise.
//----------------------------------------------------------------------

bool uvm_hdl_release_time( const std::string& path, sc_core::sc_time time )
{
  uvm_report_error("HDL_RELEASE_TIME", "HDL signal release with time not available without DPI.");
  return false;
}

} // namespace uvm
