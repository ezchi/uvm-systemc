//----------------------------------------------------------------------
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010 Mentor Graphics Corporation
//   Copyright 2013-2014 NXP B.V.
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

#include "uvmsc/reg/uvm_vreg_field_cbs.h"

namespace uvm {

//----------------------------------------------------------------------
// Constructor
//
// Create new callback method
//----------------------------------------------------------------------

uvm_vreg_field_cbs::uvm_vreg_field_cbs( const std::string& name ) : uvm_callback(name)
{}

//----------------------------------------------------------------------
// member function: pre_write (virtual)
//
//! Callback called before a write operation.
//!
//! The registered callback methods are invoked before the invocation
//! of the virtual register pre-write callbacks and
//! after the invocation of the uvm_vreg_field::pre_write() method.
//!
//! The written value \p wdat, access \p path and address \p map,
//! if modified, modifies the actual value, access path or address map
//! used in the register operation.
//----------------------------------------------------------------------

void uvm_vreg_field_cbs::pre_write( uvm_vreg_field* field,
                                    unsigned long idx,
                                    uvm_reg_data_t& wdat,
                                    uvm_path_e& path,
                                    uvm_reg_map*& map )
{}

//----------------------------------------------------------------------
// member function: post_write (virtual)
//
//! Called after a write operation
//!
//! The registered callback methods are invoked after the invocation
//! of the virtual register post-write callbacks and
//! before the invocation of the uvm_vreg_field::post_write() method.
//!
//! The \p status of the operation,
//! if modified, modifies the actual returned status.
//----------------------------------------------------------------------

void uvm_vreg_field_cbs::post_write( uvm_vreg_field* field,
                                     unsigned long idx,
                                     uvm_reg_data_t wdat,
                                     uvm_path_e path,
                                     uvm_reg_map* map,
                                     uvm_status_e& status )
{}

//----------------------------------------------------------------------
// member function: pre_read (virtual)
//
//! Called before a virtual field read.
//!
//! The registered callback methods are invoked after the invocation
//! of the virtual register pre-read callbacks and
//! after the invocation of the uvm_vreg_field::pre_read() method.
//!
//! The access \p path and address \p map,
//! if modified, modifies the actual access path or address map
//! used in the register operation.
//----------------------------------------------------------------------

void uvm_vreg_field_cbs::pre_read( uvm_vreg_field* field,
                                   unsigned long idx,
                                   uvm_path_e& path,
                                   uvm_reg_map*& map )
{}

//----------------------------------------------------------------------
// member function: post_read (virtual)
//
//! Called after a virtual field read.
//!
//! The registered callback methods are invoked after the invocation
//! of the virtual register post-read callbacks and
//! before the invocation of the uvm_vreg_field::post_read() method.
//!
//! The readback value \p rdat and the \p status of the operation,
//! if modified, modifies the actual returned readback value and status.
//----------------------------------------------------------------------

void uvm_vreg_field_cbs::post_read( uvm_vreg_field* field,
                                    unsigned long idx,
                                    uvm_reg_data_t& rdat,
                                    uvm_path_e path,
                                    uvm_reg_map* map,
                                    uvm_status_e& status )
{}

/////////

} // namespace uvm
