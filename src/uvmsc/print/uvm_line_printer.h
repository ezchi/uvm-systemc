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

#ifndef UVM_LINE_PRINTER_H_
#define UVM_LINE_PRINTER_H_

#include <systemc>

#include "uvmsc/print/uvm_printer.h"
#include "uvmsc/print/uvm_tree_printer.h"

//////////////

namespace uvm {


//------------------------------------------------------------------------------
// Class: uvm_line_printer
//
//! The line printer prints output in a line format.
//------------------------------------------------------------------------------

class uvm_line_printer : public uvm_tree_printer
{
 public:

  //----------------------------------------------------------------------------
  // Constructor
  //
  //! It differs from the #uvm_tree_printer only in that the output
  //! contains no line-feeds and no indentation.
  //----------------------------------------------------------------------------

  uvm_line_printer()
  {
    newline = " ";
    knobs.indent = 0;
  }
};

//////////////

//uvm_line_printer* uvm_default_line_printer = new uvm_line_printer();

} // namespace uvm

#endif /* UVM_LINE_PRINTER_H_ */
