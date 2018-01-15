//----------------------------------------------------------------------
//   Copyright 2013-2014 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010-2011 Mentor Graphics Corporation
//   Copyright 2010 Cadence Design Systems, Inc.
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

#ifndef UVM_MEM_MAM_CFG_H_
#define UVM_MEM_MAM_CFG_H_

#include "uvmsc/reg/uvm_mem_mam.h"

namespace uvm {


//----------------------------------------------------------------------
// Class: uvm_mem_mam_cfg
//
//! Specifies the memory managed by an instance of a #uvm_mem_mam memory
//! allocation manager class.
//----------------------------------------------------------------------

class uvm_mem_mam_cfg
{
 public:

  //--------------------------------------------------------------------
  // variable: n_bytes
  //
  //! Number of bytes in each memory location
  //--------------------------------------------------------------------
  // TODO support randomization

  /* rand */ unsigned int n_bytes;

  //--------------------------------------------------------------------
  // variable: start_offset
  //
  //! Lowest address of managed space
  //--------------------------------------------------------------------
  // TODO change into sc_dt::sc_bv<64>?
  // TODO support randomization

  /* rand */ unsigned long start_offset; // was bit [63:0]

  //--------------------------------------------------------------------
  // variable: end_offset
  //
  //! Last address of managed space
  //--------------------------------------------------------------------
  // TODO change into sc_dt::sc_bv<64>?
  // TODO support randomization

  /* rand  */ unsigned long end_offset; // was bit [63:0]

  //--------------------------------------------------------------------
  // variable: mode
  //
  //! Region allocation mode
  //--------------------------------------------------------------------
  // TODO support randomization

  /*rand*/ uvm_mem_mam::alloc_mode_e mode;

  //--------------------------------------------------------------------
  // variable: locality
  //
  //! Region location mode
  //--------------------------------------------------------------------
  // TODO support randomization

  /*rand*/ uvm_mem_mam::locality_e locality;

  /* TODO constraint for uvm_mem_mam_cfg
  constraint uvm_mem_mam_cfg_valid {
    end_offset > start_offset;
    n_bytes < 64;
  }
  */

  uvm_mem_mam_cfg()
  {
    n_bytes = 0;
    start_offset = 0;
    end_offset = 0;
    mode = uvm_mem_mam::GREEDY;
    locality = uvm_mem_mam::BROAD;
  } // constructor

}; // class uvm_mem_mam_cfg

} // namespace uvm

#endif // UVM_MEM_MAM_CFG_H_
