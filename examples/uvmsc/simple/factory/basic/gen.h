//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
//   Copyright 2009 Cadence Design Systems, Inc.
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

#ifndef GEN_H_
#define GEN_H_

#include "packet.h"


class gen : public uvm::uvm_component
{
 public:

  UVM_COMPONENT_UTILS(gen);

  gen(uvm::uvm_component_name name) : uvm::uvm_component(name) {}

  virtual packet* get_packet()
  {
    packet* p;
    // use the factory to generate a new package
    p = packet::type_id::create("packet", this);
    return p;
  }
};

#endif /* GEN_H_ */
