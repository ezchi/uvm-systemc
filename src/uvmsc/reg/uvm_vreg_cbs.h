//----------------------------------------------------------------------
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010 Mentor Graphics Corporation
//   Copyright 2013-2014 NXP B.V.
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

#ifndef UVM_VREG_CBS_H_
#define UVM_VREG_CBS_H_

#include "uvmsc/cb/uvm_callback.h"

namespace uvm {

// forward class declarations
class uvm_vreg;
class uvm_reg_map;

//------------------------------------------------------------------------------
// Class: uvm_vreg_cbs
//
//! Pre/post read/write callback facade class
//------------------------------------------------------------------------------

class uvm_vreg_cbs : public uvm_callback
{
 public:
  friend class uvm_vreg;

  uvm_vreg_cbs(const std::string& name = "uvm_reg_cbs") : uvm_callback(name)
  {}

  //-------------------------------------------------------------------------
  // member function: pre_write
  //
  //! Callback called before a write operation.
  //!
  //! The registered callback methods are invoked after the invocation
  //! of the uvm_vreg::pre_write() method.
  //! All virtual register callbacks are executed after the corresponding
  //! virtual field callbacks
  //! The pre-write virtual register and field callbacks are executed
  //! before the corresponding pre-write memory callbacks
  //!
  //! The written value \p wdat, access \p path and address \p map,
  //! if modified, modifies the actual value, access path or address map
  //! used in the virtual register operation.
  //-------------------------------------------------------------------------

  virtual void pre_write( uvm_vreg* rg,
                          unsigned long idx,
                          uvm_reg_data_t& wdat,
                          uvm_path_e& path,
                          uvm_reg_map*& map ) {}

  //-------------------------------------------------------------------------
  // member function: post_write
  //
  //! Called after register write.
  //!
  //! The registered callback methods are invoked before the invocation
  //! of the uvm_reg::post_write() method.
  //! All register callbacks are executed before the corresponding
  //! virtual field callbacks
  //! The post-write virtual register and field callbacks are executed
  //! after the corresponding post-write memory callbacks
  //!
  //! The \p status of the operation,
  //! if modified, modifies the actual returned status.
  //-------------------------------------------------------------------------

  virtual void post_write( uvm_vreg* rg,
                           unsigned long idx,
                           uvm_reg_data_t wdat,
                           uvm_path_e path,
                           uvm_reg_map* map,
                           uvm_status_e& status) {}

  //-------------------------------------------------------------------------
  // member function: pre_read
  //
  //! Called before register read.
  //!
  //! The registered callback methods are invoked after the invocation
  //! of the uvm_reg::pre_read() method.
  //! All register callbacks are executed after the corresponding
  //! virtual field callbacks
  //! The pre-read virtual register and field callbacks are executed
  //! before the corresponding pre-read memory callbacks
  //!
  //! The access \p path and address \p map,
  //! if modified, modifies the actual access path or address map
  //! used in the register operation.
  //-------------------------------------------------------------------------

  virtual void pre_read( uvm_vreg* rg,
                         unsigned long idx,
                         uvm_path_e& path,
                         uvm_reg_map*& map ) {}


  //-------------------------------------------------------------------------
  // member function: post_read
  //
  //! Called after register read.
  //!
  //! The registered callback methods are invoked before the invocation
  //! of the uvm_reg::post_read() method.
  //! All register callbacks are executed before the corresponding
  //! virtual field callbacks
  //! The post-read virtual register and field callbacks are executed
  //! after the corresponding post-read memory callbacks
  //!
  //! The readback value \p rdat and the \p status of the operation,
  //! if modified, modifies the actual returned readback value and status.
  //-------------------------------------------------------------------------

  virtual void post_read( uvm_vreg* rg,
                          unsigned idx,
                          uvm_reg_data_t& rdat,
                          uvm_path_e path,
                          uvm_reg_map* map,
                          uvm_status_e& status) {}


  // local data members
 private:

  std::string m_fname;
  int    m_lineno;

}; // class uvm_vreg_cbs

} // namespace uvm

#endif // UVM_VREG_CBS_H_
