//------------------------------------------------------------------------------
//   Copyright 2013-2016 NXP B.V.
//   Copyright 2007-2010 Mentor Graphics Corporation
//   Copyright 2007-2010 Cadence Design Systems, Inc.
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
//------------------------------------------------------------------------------

#include "uvmsc/base/uvm_event_callback.h"

namespace uvm {

//------------------------------------------------------------------------------
// CLASS: uvm_event_callback
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constructor
//
// Creates a new callback object.
//------------------------------------------------------------------------------

uvm_event_callback::uvm_event_callback( const std::string& name )
: uvm_object(name)
{}

//------------------------------------------------------------------------------
// Member function: pre_trigger (virtual)
//
// This callback is called just before triggering the associated event.
// In a derived class, override this method to implement any pre-trigger
// functionality.
//
// If your callback returns 1, then the event will not trigger and the
// post-trigger callback is not called. This provides a way for a callback
// to prevent the event from triggering.
//
// In the function, ~e~ is the <uvm_event> that is being triggered, and ~data~
// is the optional data associated with the event trigger.
//------------------------------------------------------------------------------

bool uvm_event_callback::pre_trigger( const uvm_event* e, const uvm_object* data ) const
{
  return false;
}

//------------------------------------------------------------------------------
// Member function: post_trigger (virtual)
//
// This callback is called after triggering the associated event.
// In a derived class, override this method to implement any post-trigger
// functionality.
//
//
// In the function, \p e is the #uvm_event that is being triggered, and \p data
// is the optional data associated with the event trigger.
//------------------------------------------------------------------------------

void uvm_event_callback::post_trigger( const uvm_event* e, const uvm_object* data ) const
{
  return;
}

//------------------------------------------------------------------------------
// Member function: create (virtual)
//
//------------------------------------------------------------------------------
uvm_object* uvm_event_callback::create( const std::string& name )
{
  return NULL;
}

///////////////

} // namespace uvm
