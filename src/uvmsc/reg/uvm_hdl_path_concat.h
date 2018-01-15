//----------------------------------------------------------------------
//   Copyright 2013-2014 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010-2011 Mentor Graphics Corporation
//   Copyright 2010-2011 Cadence Design Systems, Inc.
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

#ifndef UVM_HDL_PATH_CONCAT_H_
#define UVM_HDL_PATH_CONCAT_H_

namespace uvm {


//----------------------------------------------------------------------
// Typedef: uvm_hdl_path_slice
//
//! Slice of an HDL path
//!
//! Struct that specifies the HDL variable that corresponds to all
//! or a portion of a register.
//!
//! path    - Path to the HDL variable.
//! offset  - Offset of the LSB in the register that this variable implements
//! size    - Number of bits (toward the MSB) that this variable implements
//!
//! If the HDL variable implements all of the register, \p offset and \p size
//! are specified as -1.
//----------------------------------------------------------------------

typedef struct
{
  std::string path;
  int offset;
  int size;
} uvm_hdl_path_slice;


//------------------------------------------------------------------------------
// Class: uvm_hdl_path_concat
//
//! Concatenation of HDL variables
//!
//! An vector of type uvm_hdl_path_slice specifying a concatenation
//! of HDL variables that implement a register in the HDL.
//!
//! Slices must be specified in most-to-least significant order.
//! Slices must not overlap. Gaps may exists in the concatenation
//! if portions of the registers are not implemented.
//!
//! For example, the following register
//!|
//!|        1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
//!| Bits:  5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//!|       +-+---+-------------+---+-------+
//!|       |A|xxx|      B      |xxx|   C   |
//!|       +-+---+-------------+---+-------+
//!|
//!
//! If the register is implemented using a single HDL variable,
//! The array should specify a single slice with its \p offset and \p size
//! specified as -1. For example:
//!
//!| concat.set('{ '{"r1", -1, -1} });
//!
//------------------------------------------------------------------------------

class uvm_hdl_path_concat
{
 public:

  //---------------------------------------------------------------------------
  // Variable: slices
  //
  //! Array of individual slices,
  //! stored in most-to-least significant order
  //---------------------------------------------------------------------------

  std::vector<uvm_hdl_path_slice> slices;

  //---------------------------------------------------------------------------
  // member function: set
  //
  //! Initialize the concatenation using an array literal
  //---------------------------------------------------------------------------

  void set( std::vector<uvm_hdl_path_slice> t )
  {
    slices = t;
  }

  //---------------------------------------------------------------------------
  // member function: add_slice
  //
  //! Append the specified \p slice literal to the path concatenation
  //---------------------------------------------------------------------------

  void add_slice(uvm_hdl_path_slice slice)
  {
    slices.push_back(slice);
  }

  //---------------------------------------------------------------------------
  // member function: add_path
  //
  //! Append the specified \p path to the path concatenation,
  //! for the specified number of bits at the specified \p offset.
  //---------------------------------------------------------------------------

  void add_path( const std::string& path,
      unsigned int offset = -1,
      unsigned int size = -1 )
  {
    uvm_hdl_path_slice t;
    t.offset = offset;
    t.path   = path;
    t.size   = size;
    add_slice(t);
  }

  //////////////////////////////////////////
  // Implementation defined functions
  //////////////////////////////////////////

  // helper functions to print the content of the hdl-path string
  friend std::ostream& operator<< ( std::ostream& os, const uvm_hdl_path_concat& obj );

  std::string convert2string() const
  {
    std::string s = "";
    for (unsigned int i = 0; i < slices.size(); i++)
    {
      if (i) s += "."; // skip dot for the first slice
      s += slices[i].path;
    }
    return s;

    // TODO should we also print the size and offset?
  }

}; // class uvm_hdl_path_concat


inline std::ostream& operator<< ( std::ostream& os, const uvm_hdl_path_concat& obj )
{
  os << obj.convert2string();
  return os;
}

} // namespace uvm

#endif // UVM_HDL_PATH_CONCAT_H_
