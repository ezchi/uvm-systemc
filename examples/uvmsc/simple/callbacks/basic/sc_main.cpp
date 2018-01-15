//------------------------------------------------------------------------------
//   Copyright 2013-2014 NXP B.V.
//   Copyright 2007-2010 Mentor Graphics Corporation
//   Copyright 2007-2010 Cadence Design Systems, Inc. 
//   Copyright 2010 Synopsys, Inc.
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the "License"); you may not
//   use this file except in compliance with the License.  You may obtain a copy
//   of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//   License for the specific language governing permissions and limitations
//   under the License.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Title: Typical Callback Application
//
// This example demonstrates callback usage. The component developer defines a
// driver and driver-specific callback class. The callback class defines the
// hooks available for users to override. The component using the callbacks
// (i.e. calling the callback methods) also defines corresponding virtual
// methods for each callback hook. The developer implements each virtual methods
// to call the corresponding callback method in all registered callback objects
// using default algorithm. The end-user may then define either a callback or
// driver subtype to extend driver behavior.
//------------------------------------------------------------------------------

#include <systemc>
#include <uvm>

#include "top.h"

int sc_main(int, char*[])
{
  top* topenv = new top("topenv");

  uvm::run_test();

  return 0;
}


