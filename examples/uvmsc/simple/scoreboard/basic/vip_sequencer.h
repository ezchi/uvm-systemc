//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
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

#ifndef VIP_SEQUENCER_H_
#define VIP_SEQUENCER_H_

#include <systemc>
#include <tlm.h>
#include <uvm>

template <class REQ>
class vip_sequencer : public uvm::uvm_sequencer<REQ>
{
 public:
  vip_sequencer( uvm::uvm_component_name name ) : uvm::uvm_sequencer<REQ>( name )
  {
    std::cout << sc_core::sc_time_stamp() << ": constructor " << name << std::endl;
  }

  UVM_COMPONENT_PARAM_UTILS(vip_sequencer<REQ>);

};

#endif /* VIP_SEQUENCER_H_ */
