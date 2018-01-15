//----------------------------------------------------------------------
//   Copyright 2013-2014 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010 Mentor Graphics Corporation
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

#ifndef UVM_REG_BUS_OP_H_
#define UVM_REG_BUS_OP_H_

#include "uvmsc/reg/uvm_reg_model.h"

namespace uvm {


//------------------------------------------------------------------------------
// typedef: uvm_reg_bus_op
//
//! Struct that defines a generic bus transaction for register and memory
//! accesses, having \p kind (read or write), \p address, \p data, and
//! \p byte_enable information.
//!
//! If the bus is narrower than the register or memory location being accessed,
//! there will be multiple of these bus operations for every abstract
//! #uvm_reg_item transaction. In this case, \p data represents the portion
//! of uvm_reg_item::value being transferred during this bus cycle.
//! If the bus is wide enough to perform the register or memory operation in
//! a single cycle, \p data will be the same as uvm_reg_item::value.
//------------------------------------------------------------------------------

typedef struct
{
  //--------------------------------------------------------------------------
  // Variable: kind
  //
  //! Kind of access: READ or WRITE.
  //--------------------------------------------------------------------------
  uvm_access_e kind;


  //--------------------------------------------------------------------------
  // Variable: addr
  //
  //! The bus address.
  //--------------------------------------------------------------------------
  uvm_reg_addr_t addr;


  //--------------------------------------------------------------------------
  // Variable: data
  //
  //! The data to write. If the bus width is smaller than the register or
  //! memory width, \p data represents only the portion of \p value that is
  //! being transferred this bus cycle.
  //--------------------------------------------------------------------------
  uvm_reg_data_t data;

   
  //--------------------------------------------------------------------------
  // Variable: n_bits
  //
  //! The number of bits of <uvm_reg_item::value> being transferred by
  //! this transaction.
  //--------------------------------------------------------------------------

  unsigned int n_bits;

  /* TODO constraints
  constraint valid_n_bits {
     n_bits > 0;
     n_bits <= `UVM_REG_DATA_WIDTH;
  }
  */


  //--------------------------------------------------------------------------
  // Variable: byte_en
  //
  //! Enables for the byte lanes on the bus. Meaningful only when the
  //! bus supports byte enables and the operation originates from a field
  //! write/read.
  //--------------------------------------------------------------------------
  uvm_reg_byte_en_t byte_en;


  //--------------------------------------------------------------------------
  // Variable: status
  //
  //! The result of the transaction: UVM_IS_OK, UVM_HAS_X, UVM_NOT_OK.
  //! See #uvm_status_e.
  //--------------------------------------------------------------------------
  uvm_status_e status;

} uvm_reg_bus_op;

} // namespace uvm

#endif // UVM_REG_BUS_OP_H_
