//----------------------------------------------------------------------
//   Copyright 2015-2016 NXP B.V.
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

#ifndef UVM_COMPONENT_NAME_H_
#define UVM_COMPONENT_NAME_H_

#include <systemc>

//////////////

namespace uvm {


//------------------------------------------------------------------------------
// Class uvm_component_name
//
//! UVM component name registration. Same mechanism as in SystemC sc_module_name
//! to register the parent-child relationship
//------------------------------------------------------------------------------

class uvm_component_name
{
public:
  uvm_component_name( const sc_core::sc_module_name& nm );
  uvm_component_name( const char* nm );
  sc_core::sc_module_name name();
  operator const char* () const;

private:
  sc_core::sc_module_name m_name;
};

/////////////////////////////////////////////


} // namespace uvm

#endif /* UVM_COMPONENT_NAME_H_ */
