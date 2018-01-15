//----------------------------------------------------------------------
//   Copyright 2013-2016 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010-2011 Mentor Graphics Corporation
//   Copyright 2010 Cadence Design Systems, Inc.
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

#ifndef UVM_MEM_REGION_H_
#define UVM_MEM_REGION_H_

#include <string>

#include "uvmsc/reg/uvm_reg_model.h"

namespace uvm {


// forward class declaration
class uvm_mem_mam;
class uvm_mem_mam_cfg;
class uvm_mem_region;
class uvm_mem_mam_policy;
class uvm_mem;
class uvm_vreg;
class uvm_reg_map;
class uvm_sequence_base;

//----------------------------------------------------------------------
// CLASS: uvm_mem_region
//
//! Allocated memory region descriptor
//!
//! Each instance of this class describes an allocated memory region.
//! Instances of this class are created only by
//! the memory manager, and returned by the
//! uvm_mem_mam::reserve_region() and uvm_mem_mam::request_region()
//! methods.
//----------------------------------------------------------------------

class uvm_mem_region
{
 public:
  friend class uvm_mem_mam;

  //--------------------------------------------------------------------
  // UVM Standard LRM API below
  //--------------------------------------------------------------------

  unsigned long get_start_offset() const;

  unsigned long get_end_offset() const;

  unsigned int get_len() const;

  unsigned int get_n_bytes() const;

  void release_region();

  uvm_mem* get_memory() const;

  uvm_vreg* get_virtual_registers() const;

  void write( uvm_status_e& status, // output
              uvm_reg_addr_t offset,
              uvm_reg_data_t value,
              uvm_path_e path = UVM_DEFAULT_PATH,
              uvm_reg_map* map = NULL,
              uvm_sequence_base* parent = NULL,
              int prior = -1,
              uvm_object* extension = NULL,
              const std::string& fname = "",
              int lineno = 0 );

  void read( uvm_status_e& status, // output
             uvm_reg_addr_t offset,
             uvm_reg_data_t& value, // output
             uvm_path_e path = UVM_DEFAULT_PATH,
             uvm_reg_map* map = NULL,
             uvm_sequence_base* parent = NULL,
             int prior = -1,
             uvm_object* extension = NULL,
             const std::string& fname = "",
             int lineno = 0 );

  void burst_write( uvm_status_e& status, // output
                    uvm_reg_addr_t offset,
                    std::vector<uvm_reg_data_t> value,
                    uvm_path_e path = UVM_DEFAULT_PATH,
                    uvm_reg_map* map = NULL,
                    uvm_sequence_base* parent = NULL,
                    int prior  = -1,
                    uvm_object* extension = NULL,
                    const std::string& fname  = "",
                    int lineno = 0);

  void burst_read( uvm_status_e& status, // output
                   uvm_reg_addr_t offset,
                   std::vector<uvm_reg_data_t>& value, // output
                   uvm_path_e path = UVM_DEFAULT_PATH,
                   uvm_reg_map* map = NULL,
                   uvm_sequence_base* parent = NULL,
                   int prior = -1,
                   uvm_object* extension = NULL,
                   const std::string& fname  = "",
                   int lineno = 0 );

  void poke( uvm_status_e& status, // output
             uvm_reg_addr_t offset,
             uvm_reg_data_t value,
             uvm_sequence_base* parent = NULL,
             uvm_object* extension = NULL,
             const std::string& fname = "",
             int lineno = 0 );

  void peek( uvm_status_e& status, // output
             uvm_reg_addr_t offset,
             uvm_reg_data_t& value, // output
             uvm_sequence_base* parent = NULL,
             uvm_object* extension = NULL,
             const std::string& fname = "",
             int lineno = 0 );

  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////

 private:
  uvm_mem_region( unsigned long start_offset,
                  unsigned long end_offset,
                  unsigned int len,
                  unsigned int n_bytes,
                  uvm_mem_mam* parent );

  std::string convert2string();

  // local data members

  unsigned int m_len;
  unsigned int m_n_bytes;
  uvm_mem_mam* m_parent;
  std::string       m_fname;
  int          m_lineno;
  uvm_vreg*    m_vreg;

  unsigned long m_start_offset;
  unsigned long m_end_offset;

}; // class uvm_mem_region

} // namespace uvm

#endif // UVM_MEM_MAM_H_
