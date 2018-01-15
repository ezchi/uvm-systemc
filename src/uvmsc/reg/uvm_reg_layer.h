//----------------------------------------------------------------------
//   Copyright 2013 NXP B.V.
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

#ifndef UVM_REG_LAYER_H_
#define UVM_REG_LAYER_H_

#include "uvmsc/reg/uvm_reg_adapter.h"
#include "uvmsc/reg/uvm_reg_backdoor.h"
#include "uvmsc/reg/uvm_reg_block.h"
#include "uvmsc/reg/uvm_reg_bus_op.h"
#include "uvmsc/reg/uvm_reg_cbs.h"
#include "uvmsc/reg/uvm_reg_cbs_types.h"
#include "uvmsc/reg/uvm_reg_field.h"
#include "uvmsc/reg/uvm_reg_fifo.h"
#include "uvmsc/reg/uvm_reg_file.h"
#include "uvmsc/reg/uvm_reg_frontdoor.h"
#include "uvmsc/reg/uvm_reg_indirect_data.h"
#include "uvmsc/reg/uvm_reg_indirect_ftdr_seq.h"
#include "uvmsc/reg/uvm_reg_item.h"
#include "uvmsc/reg/uvm_reg_map.h"
#include "uvmsc/reg/uvm_reg_model.h"
#include "uvmsc/reg/uvm_reg_predictor.h"
#include "uvmsc/reg/uvm_reg_read_only_cbs.h"
#include "uvmsc/reg/uvm_reg_sequence.h"
#include "uvmsc/reg/uvm_reg_tlm_adapter.h"
#include "uvmsc/reg/uvm_reg_write_only_cbs.h"
#include "uvmsc/reg/uvm_reg.h"
#include "uvmsc/reg/uvm_vreg.h"
#include "uvmsc/reg/uvm_vreg_cbs.h"
#include "uvmsc/reg/uvm_vreg_field.h"
#include "uvmsc/reg/uvm_vreg_field_cbs.h"
#include "uvmsc/reg/uvm_mem.h"
#include "uvmsc/reg/uvm_mem_mam.h"
#include "uvmsc/reg/uvm_mem_region.h"
#include "uvmsc/reg/uvm_mem_mam_policy.h"
#include "uvmsc/reg/uvm_mem_mam_cfg.h"
#include "uvmsc/reg/uvm_hdl_path_concat.h"

#include "uvmsc/reg/sequences/uvm_reg_bit_bash_seq.h"
#include "uvmsc/reg/sequences/uvm_reg_mem_hdl_paths_seq.h"

// dummy sc register
#include "uvmsc/reg/uvm_sc_reg.h"

#endif /* UVM_REG_LAYER_H_ */
