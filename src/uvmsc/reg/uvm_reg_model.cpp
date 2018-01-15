//----------------------------------------------------------------------
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010-2011 Mentor Graphics Corporation
//   Copyright 2010 Cadence Design Systems, Inc.
//   Copyright 2013 NXP B.V.
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
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

#include <string>
#include <iostream>

#include "uvmsc/reg/uvm_reg_model.h"

namespace uvm {

const char* uvm_status_name[] = {
  "UVM_IS_OK",
  "UVM_NOT_OK",
  "UVM_HAS_X"
};

const char* uvm_path_name[] = {
  "UVM_FRONTDOOR",
  "UVM_BACKDOOR",
  "UVM_PREDICT",
  "UVM_DEFAULT_PATH"
};

const char* uvm_check_name[] = {
  "UVM_NO_CHECK",
  "UVM_CHECK"
};

const char* uvm_endianness_name[] = {
  "UVM_NO_ENDIAN",
  "UVM_LITTLE_ENDIAN",
  "UVM_BIG_ENDIAN",
  "UVM_LITTLE_FIFO",
  "UVM_BIG_FIFO"
};

const char* uvm_elem_kind_name[] = {
  "UVM_REG",
  "UVM_FIELD",
  "UVM_MEM"
};

const char* uvm_access_name[] = {
  "UVM_READ",
  "UVM_WRITE",
  "UVM_BURST_READ",
  "UVM_BURST_WRITE"
};

const char* uvm_hier_name[] = {
  "UVM_NO_HIER",
  "UVM_HIER"
};

const char* uvm_predict_name[] = {
  "UVM_PREDICT_DIRECT",
  "UVM_PREDICT_READ",
  "UVM_PREDICT_WRITE"
};

//----------------------------------------------------------------------
// Global function: uvm_hdl_concat2string
//
// Implementation defined
//----------------------------------------------------------------------

std::string uvm_hdl_concat2string( uvm_hdl_path_concat concat )
{
  std::ostringstream image;
  image << "{";

  if (concat.slices.size() == 1 &&
      concat.slices[0].offset == -1 &&
      concat.slices[0].size == -1)
    return concat.slices[0].path;

  for( unsigned int i = 0; i < concat.slices.size(); i++ )
  {
    uvm_hdl_path_slice slice = concat.slices[i];

    image << ((i == 0) ? "" : ", ")
          << slice.path;

    if (slice.offset >= 0)
    {
      image << "@"
            << "["
            << slice.offset
            << "+: "
            << slice.size
            << "]";
    }
  }

  image << "}";

  return image.str();
}

//----------------------------------------------------------------------
// Global function: uvm_pow
//
// Implementation defined
//
// Return power (x^y) for integers
//----------------------------------------------------------------------

int uvm_pow(unsigned int x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * uvm_pow(x, p-1);
}

//----------------------------------------------------------------------
// Global function: uvm_mask
//
// Implementation defined
//
// Returns the mask related to the maximum size of the bit vector
//----------------------------------------------------------------------

uvm_reg_data_t uvm_mask_size(unsigned int size)
{
  uvm_reg_data_t mask;
  mask = uvm_pow(2, size)-1;
  return mask;
}

///////////

} // namespace uvm
