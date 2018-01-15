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

#ifndef UVM_MEM_MAM_POLICY_H_
#define UVM_MEM_MAM_POLICY_H_

namespace uvm {



//----------------------------------------------------------------------
// Class: uvm_mem_mam_policy
//
// An instance of this class is randomized to determine
// the starting offset of a randomly allocated memory region.
// This class can be extended to provide additional constraints
// on the starting offset, such as word alignment or
// location of the region within a memory page.
// If a procedural region allocation policy is required,
// it can be implemented in the pre/post_randomize() method.
//----------------------------------------------------------------------

class uvm_mem_mam_policy
{
 public:
  // variable: len
  // Number of addresses required
  unsigned int len;

  // variable: start_offset
  // The starting offset of the region
  /*rand*/ unsigned long start_offset;

  // variable: min_offset
  // Minimum address offset in the managed address space
  unsigned long min_offset;

  // variable: max_offset
  // Maximum address offset in the managed address space
  unsigned long max_offset;

  // variable: in_use
  // Regions already allocated in the managed address space
  std::vector<uvm_mem_region*> in_use;

  /* TODO constraits
  constraint uvm_mem_mam_policy_valid {
    start_offset >= min_offset;
    start_offset <= max_offset - len + 1;
  }

  constraint uvm_mem_mam_policy_no_overlap {
    foreach (in_use[i]) {
      !(start_offset <= in_use[i].Xend_offsetX &&
          start_offset + len - 1 >= in_use[i].Xstart_offsetX);
    }
  }
  */

  uvm_mem_mam_policy()
  {
    len = 0;
    start_offset = 0;
    min_offset = 0;
    max_offset = 0;
    in_use.clear();
  }

}; // uvm_mem_mam_policy

} // namespace uvm

#endif // UVM_MEM_MAM_POLICY_H_
