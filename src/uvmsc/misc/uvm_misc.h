//----------------------------------------------------------------------
//   Copyright 2012-2016 NXP B.V.
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

#ifndef UVM_MISC_H_
#define UVM_MISC_H_

#include <cstdarg>
#include <systemc>

#include "uvmsc/misc/uvm_scope_stack.h"
#include "uvmsc/misc/uvm_status_container.h"
#include "uvmsc/misc/uvm_copy_map.h"

//////////////

namespace uvm {


// Append/prepend symbolic values for order-dependent APIs
typedef enum {
  UVM_APPEND,
  UVM_PREPEND
} uvm_apprepend;

extern const char *uvm_apprepend_name[];

std::string uvm_vector_to_string ( int value,
                                   int size,
                                   uvm_radix_enum radix = UVM_NORADIX,
                                   const std::string& radix_str = "" );

std::string uvm_vector_to_string ( uvm_bitstream_t value,
                                   int size,
                                   uvm_radix_enum radix = UVM_NORADIX,
                                   const std::string& radix_str = "" );

std::string uvm_flatten_name( const std::string& full_name, const char* scope_separator = "_" );

std::string uvm_leaf_scope( const std::string& full_name, const char* scope_separator );

std::string uvm_object_value_str( const uvm_object* v );

const std::string uvm_string_queue_join( const std::vector<std::string>& q );

/////////////////////////////////////////////////////////////////
// some other utilities functions not defined in UVM-SV
/////////////////////////////////////////////////////////////////

std::string uvm_toupper(const std::string& str);

sc_dt::sc_uint<64> uvm_realtobits( double val );

double uvm_bitstoreal( const sc_dt::sc_uint<64>& val );

sc_dt::sc_uint<32> uvm_realtobits( float val );

float uvm_bitstoreal( const sc_dt::sc_uint<32>& val );

std::string uvm_sformatf(const char* format, ...);

void enable_hdl_access(sc_core::sc_object* dut);

} // namespace uvm

#endif /* UVM_MISC_H_ */
