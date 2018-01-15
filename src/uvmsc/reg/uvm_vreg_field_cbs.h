//----------------------------------------------------------------------
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010 Mentor Graphics Corporation
//   Copyright 2013 NXP B.V.
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

#ifndef UVM_VREG_FIELD_CBS_H_
#define UVM_VREG_FIELD_CBS_H_

#include "uvmsc/cb/uvm_callback.h"
#include "uvmsc/reg/uvm_reg_model.h"

namespace uvm {

// forward class declarations
class uvm_vreg_field;
class uvm_reg_map;

//----------------------------------------------------------------------
// Class: uvm_vreg_field_cbs
//
//! Pre/post read/write callback facade class
//----------------------------------------------------------------------

class uvm_vreg_field_cbs : public uvm_callback
{
 public:
  friend class uvm_vreg;
  friend class uvm_vreg_field;

  explicit uvm_vreg_field_cbs(const std::string& name = "uvm_vreg_field_cbs");

  // TODO check argument types (pointer, references, const refs etc)

  virtual void pre_write( uvm_vreg_field* field,
                          unsigned long idx,
                          uvm_reg_data_t& wdat,
                          uvm_path_e& path,
                          uvm_reg_map*& map );

  virtual void post_write( uvm_vreg_field* field,
                           unsigned long idx,
                           uvm_reg_data_t wdat,
                           uvm_path_e path,
                           uvm_reg_map* map,
                           uvm_status_e& status );

  virtual void pre_read( uvm_vreg_field* field,
                         unsigned long idx,
                         uvm_path_e& path,
                         uvm_reg_map*& map );

  virtual void post_read( uvm_vreg_field* field,
                          unsigned long idx,
                          uvm_reg_data_t& rdat,
                          uvm_path_e path,
                          uvm_reg_map* map,
                          uvm_status_e& status );

  // local data members
 private:
  std::string m_fname;
  int    m_lineno;

}; // class uvm_vreg_field_cbs


} // namespace uvm

#endif // UVM_VREG_FIELD_CBS_H_
