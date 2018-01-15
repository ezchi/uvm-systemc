//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010 Synopsys, Inc.
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

#ifndef UVM_STATUS_CONTAINER_H_
#define UVM_STATUS_CONTAINER_H_

#include <map>
#include <systemc>

#include "uvmsc/misc/uvm_scope_stack.h"

//////////////

namespace uvm {

// forward class declarations
class uvm_object;
class uvm_packer;
class uvm_recorder;
class uvm_printer;
class uvm_comparer;

//------------------------------------------------------------------------------
// CLASS: uvm_status_container
//
//! Internal class to contain status information for automation methods.
//------------------------------------------------------------------------------

class uvm_status_container
{
 public:

  uvm_status_container();

  ~uvm_status_container();

  // Used for checking cycles. When a data function is entered, if the depth is
  // non-zero, then then the existeance of the object in the map means that a
  // cycle has occured and the function should immediately exit. When the
  // function exits, it should reset the cycle map so that there is no memory
  // leak.

  std::map<const uvm_object*, bool> cycle_check;

  // These are the policy objects currently in use. The policy object gets set
  // when a function starts up. The macros use this.

  uvm_comparer*    comparer;
  uvm_packer*      packer;
  uvm_recorder*    recorder;
  uvm_printer*     printer;

  // The scope stack is used for messages that are emitted by policy classes.
  uvm_scope_stack* scope;

};  // class uvm_status_container



//////////////

} // namespace uvm

#endif /* UVM_STATUS_CONTAINER_H_ */
