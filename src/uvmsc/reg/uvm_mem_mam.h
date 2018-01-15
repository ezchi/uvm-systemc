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

#ifndef UVM_MEM_MAM_H_
#define UVM_MEM_MAM_H_

#include <string>
#include <vector>

namespace uvm {

// forward class declaration
class uvm_mem_mam_cfg;
class uvm_mem_region;
class uvm_mem_mam_policy;
class uvm_mem;


//----------------------------------------------------------------------
// CLASS: uvm_mem_mam
//
//! Memory allocation manager
//!
//! Memory allocation management utility class similar to C's malloc()
//! and free().
//! A single instance of this class is used to manage a single,
//! contiguous address space.
//----------------------------------------------------------------------

class uvm_mem_mam
{
 public:

  //--------------------------------------------------------------------
  // Type: alloc_mode_e
  //
  //! Memory allocation mode
  //!
  //! Specifies how to allocate a memory region
  //!
  //! GREEDY   - Consume new, previously unallocated memory
  //! THRIFTY  - Reused previously released memory as much as possible
  //!            (not yet implemented)
  //!--------------------------------------------------------------------

  typedef enum {GREEDY, THRIFTY} alloc_mode_e;

  //--------------------------------------------------------------------
  // Type: locality_e
  //
  //! Location of memory regions
  //!
  //! Specifies where to locate new memory regions
  //!
  //! BROAD    - Locate new regions randomly throughout the address space
  //! NEARBY   - Locate new regions adjacent to existing regions
  //--------------------------------------------------------------------

  typedef enum {BROAD, NEARBY}   locality_e;

  //--------------------------------------------------------------------
  // Variable: default_alloc
  //
  //! Region allocation policy
  //!
  //! This object is repeatedly randomized when allocating new regions.
  //--------------------------------------------------------------------

  uvm_mem_mam_policy* default_alloc;

  //--------------------------------------------------------------------
  // Group: Initialization
  //--------------------------------------------------------------------

  // Constructor
  explicit uvm_mem_mam( const std::string& name,
                        uvm_mem_mam_cfg* cfg,
                        uvm_mem* mem = NULL );

  uvm_mem_mam_cfg* reconfigure( uvm_mem_mam_cfg* cfg = NULL );

  //--------------------------------------------------------------------
  // Group: Memory Management
  //--------------------------------------------------------------------

  uvm_mem_region* reserve_region( unsigned long start_offset,
                                  unsigned int n_bytes,
                                  const std::string& fname = "",
                                  int lineno = 0 );

  uvm_mem_region* request_region( unsigned int n_bytes,
                                  uvm_mem_mam_policy* alloc = NULL,
                                  const std::string& fname = "",
                                  int lineno = 0 );

  void release_region( uvm_mem_region* region );

  void release_all_regions();

  //--------------------------------------------------------------------
  // Group: Introspection
  //--------------------------------------------------------------------

  std::string convert2string();

  uvm_mem_region* for_each( bool reset = false );

  uvm_mem* get_memory() const;

  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////

  virtual ~uvm_mem_mam(); // destructor

 private:

  // local data members

  uvm_mem* m_memory;
  uvm_mem_mam_cfg* m_cfg;

  typedef std::vector<uvm_mem_region*> m_in_use_t;
  typedef m_in_use_t::iterator m_in_use_itt;
  m_in_use_t m_in_use;

  int m_for_each_idx;
  std::string m_fname;
  int m_lineno;

}; // class uvm_mem_mam

} // namespace uvm

#endif // UVM_MEM_MAM_H_
