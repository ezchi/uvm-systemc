//----------------------------------------------------------------------
//   Copyright 2013-2014 NXP B.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2010 Cadence Design Systems, Inc.
//   Copyright 2010-2011 Synopsys, Inc.
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

#include "uvmsc/cb/uvm_callbacks_base.h"
#include "uvmsc/cb/uvm_typeid.h"

namespace uvm {

//------------------------------------------------------------------------------
// static data member initialization
//------------------------------------------------------------------------------

std::map<uvm_object*, uvm_queue<uvm_callback*>* >* uvm_callbacks_base::m_pool = NULL;
uvm_callbacks_base* uvm_callbacks_base::m_b_inst = m_initialize();
bool uvm_callbacks_base::m_tracing = true;

//----------------------------------------------------------------------------
// Constructor (protected)
//----------------------------------------------------------------------------
uvm_callbacks_base::uvm_callbacks_base()
{}

//----------------------------------------------------------------------------
// member function: m_initialize (static)
//
//! Implementation defined
//----------------------------------------------------------------------------

uvm_callbacks_base* uvm_callbacks_base::m_initialize()
{
  if(m_b_inst == NULL)
  {
    m_b_inst = new uvm_callbacks_base();
    m_pool = new std::map< uvm_object*, uvm_queue<uvm_callback*>* >();
  }
  return m_b_inst;
}

//----------------------------------------------------------------------------
// member function: m_am_i_a (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

bool uvm_callbacks_base::m_am_i_a( uvm_object* obj )
{
  return false;
}

//----------------------------------------------------------------------------
// member function: m_is_for_me (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

bool uvm_callbacks_base::m_is_for_me( uvm_callback* cb )
{
  return false;
}

//----------------------------------------------------------------------------
// member function: m_is_registered (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

bool uvm_callbacks_base::m_is_registered( uvm_object* obj, uvm_callback* cb )
{
  return false;
}


//----------------------------------------------------------------------------
// member function: m_get_tw_cb_q (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

uvm_queue<uvm_callback*>* uvm_callbacks_base::m_get_tw_cb_q( uvm_object* obj )
{
  return NULL;
}

//----------------------------------------------------------------------------
// member function: m_add_tw_cbs (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

void uvm_callbacks_base::m_add_tw_cbs( uvm_callback* cb, uvm_apprepend ordering)
{}

//----------------------------------------------------------------------------
// member function: m_delete_tw_cbs (virtual)
//
//! Implementation defined
//----------------------------------------------------------------------------

bool uvm_callbacks_base::m_delete_tw_cbs( uvm_callback* cb )
{
  return false;
}

//----------------------------------------------------------------------------
// member function: check_registration
//
//! Implementation defined
//! Check registration. To test registration, start at this class and
//! work down the class hierarchy. If any class returns true then
//! the pair is legal.
//----------------------------------------------------------------------------

bool uvm_callbacks_base::check_registration( uvm_object* obj, uvm_callback* cb )
{
  uvm_callbacks_base* dt = NULL;

  if (m_is_registered(obj, cb))
    return true;

    // Need to look at all possible T/CB pairs of this type
  for( unsigned int i = 0; i < m_this_type.size(); i++ )
  {
      if(m_b_inst != m_this_type[i] && m_this_type[i]->m_is_registered(obj, cb))
      return true;
  }

  if(obj == NULL)
  {
    for( unsigned int i = 0; i < m_derived_types.size(); i++ )
    {
      dt = uvm_typeid_base::get_cb(m_derived_types[i]);

      if(dt != NULL && dt->check_registration(NULL, cb))
        return true;
    }
  }

  return false;
}

} // namespace uvm
