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

#ifndef UVM_PRINTER_KNOBS_H_
#define UVM_PRINTER_KNOBS_H_

#include <systemc>

#include "uvmsc/base/uvm_object_globals.h"

//////////////

#define UVM_STDOUT 1

namespace uvm {

//------------------------------------------------------------------------------
// Class: uvm_printer_knobs
//
//! The class #uvm_printer_knobs defines the printer settings available to all
//! printer subtypes.
//------------------------------------------------------------------------------

class uvm_printer_knobs
{
 public:

  // constructor
  uvm_printer_knobs()
  : header(true),
    footer(true),
    full_name(false),
    identifier(true),
    type_name(true),
    size(true),
    depth(-1),
    reference(true),
    begin_elements(5),
    end_elements(5),
    prefix(""),
    indent(2),
    show_root(false),
    mcd(UVM_STDOUT),
    separator("{}"),
    show_radix(true),
    default_radix(UVM_HEX),
    dec_radix(""),         // was originally 'd in SV
    bin_radix("'b"),
    oct_radix("'o"),
    unsigned_radix(""),    // was originally 'd in SV
    hex_radix("0x")        // was originally 'h in SV
  {
  }

  // Variable: header
  //
  //! Indicates whether the function #print_header should be called when
  //! printing an object.

  bool header;

  // Variable: footer
  //
  //! Indicates whether the function #print_footer should be called when
  //! printing an object.

  bool footer;

  // Variable: full_name
  //
  //! Indicates whether #adjust_name should print the full name of an identifier
  //! or just the leaf name.

  bool full_name;

  // Variable: identifier
  //
  //! Indicates whether #adjust_name should print the identifier. This is useful
  //! in cases where you just want the values of an object, but no identifiers.

  bool identifier;

  // Variable: type_name
  //
  //! Controls whether to print a field's type name.

  bool type_name;

  // Variable: size
  //
  //! Controls whether to print a field's size.

  bool size;

  // Variable: depth
  //
  //! Indicates how deep to recurse when printing objects.
  //! A depth of -1 means to print everything.

  int depth;

  // Variable: reference
  //
  //! Controls whether to print a unique reference ID for object handles.
  //! The behavior of this knob is simulator-dependent.

  bool reference;

  // Variable: begin_elements
  //
  //! Defines the number of elements at the head of a list to print.
  //! Use -1 for no max.

  int begin_elements;

  // Variable: end_elements
  //
  //! This defines the number of elements at the end of a list that
  //! should be printed.

  int end_elements;

  // Variable: prefix
  //
  //! Specifies the string prepended to each output line

  std::string prefix;

  // Variable: indent
  //
  //! This knob specifies the number of spaces to use for level indentation.
  //! The default level indentation is two spaces.

  int indent;

  // Variable: show_root
  //
  //! This setting indicates whether or not the initial object that is printed
  //! (when current depth is 0) prints the full path name. By default, the first
  //! object is treated like all other objects and only the leaf name is printed.

  bool show_root;

  // Variable: mcd
  //
  //! This is a file descriptor, or multi-channel descriptor, that specifies
  //! where the print output should be directed.
  //!
  //! By default, the output goes to the standard output of the simulator.

  int mcd;

  // Variable: separator
  //
  //! For tree printers only, determines the opening and closing
  //! separators used for nested objects.

  std::string separator;

  // Variable: show_radix
  //
  //! Indicates whether the radix string ('h, and so on) should be prepended to
  //! an integral value when one is printed.

  bool show_radix;

  // Variable: default_radix
  //
  //! This knob sets the default radix to use for integral values when no radix
  //! enum is explicitly supplied to the print_int() method.

  uvm_radix_enum default_radix;

  // Variable: dec_radix
  //
  //! This string should be prepended to the value of an integral type when a
  //! radix of #UVM_DEC is used for the radix of the integral object.
  //!
  //! When a negative number is printed, the radix is not printed since only
  //! signed decimal values can print as negative.

  std::string dec_radix;

  // Variable: bin_radix
  //
  //! This string should be prepended to the value of an integral type when a
  //! radix of #UVM_BIN is used for the radix of the integral object.

  std::string bin_radix;

  // Variable: oct_radix
  //
  //! This string should be prepended to the value of an integral type when a
  //! radix of #UVM_OCT is used for the radix of the integral object.

  std::string oct_radix;

  // Variable: unsigned_radix
  //
  //! This is the string which should be prepended to the value of an integral
  //! type when a radix of #UVM_UNSIGNED is used for the radix of the integral
  //! object.

  std::string unsigned_radix;

  // Variable: hex_radix
  //
  //! This string should be prepended to the value of an integral type when a
  //! radix of #UVM_HEX is used for the radix of the integral object.

  std::string hex_radix;

  // member function: get_radix_str
  //
  //# Converts the radix from an enumerated to a printable radix according to
  //# the radix printing knobs (bin_radix, and so on).

  std::string get_radix_str( uvm_radix_enum radix ) const
  {

    if(show_radix == 0)
      return "";

    if(radix == UVM_NORADIX)
      radix = default_radix;

    switch(radix)
    {
      case UVM_BIN: return bin_radix;
      case UVM_OCT: return oct_radix;
      case UVM_DEC: return dec_radix;
      case UVM_HEX: return hex_radix;
      case UVM_UNSIGNED: return unsigned_radix;
      default: return "";
    }
  }
}; // class uvm_printer_knobs


//////////////

} // namespace uvm

#endif /* UVM_PRINTER_KNOBS_H_ */
