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

#include "uvmsc/base/uvm_component_name.h"
#include "uvmsc/base/uvm_coreservice_t.h"
#include "uvmsc/base/uvm_default_coreservice_t.h"

namespace uvm {


//------------------------------------------------------------------------------
// Class uvm_component_name
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------

uvm_component_name::uvm_component_name( const sc_core::sc_module_name& nm ) : m_name( nm )
{}

uvm_component_name::uvm_component_name( const char* nm ) : m_name( nm )
{
  uvm_coreservice_t* cs = uvm_coreservice_t::get();
  cs->get_root();
}

//------------------------------------------------------------------------------
// member function: name
//------------------------------------------------------------------------------

sc_core::sc_module_name uvm_component_name::name()
{
  return m_name;
}

//------------------------------------------------------------------------------
// operator const char*
//------------------------------------------------------------------------------

uvm_component_name::operator const char* () const
{
  return m_name;
}


} // namespace uvm
