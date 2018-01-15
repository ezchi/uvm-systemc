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

#include "uvmsc/base/uvm_coreservice_t.h"
#include "uvmsc/base/uvm_default_coreservice_t.h"
#include "uvmsc/reg/uvm_mem.h"
#include "uvmsc/reg/uvm_mem_mam.h"
#include "uvmsc/reg/uvm_mem_region.h"
#include "uvmsc/reg/uvm_mem_mam_policy.h"
#include "uvmsc/reg/uvm_mem_mam_cfg.h"

namespace uvm {

//----------------------------------------------------------------------
// Constructor
//
//! Create a new manager instance
//!
//! Create an instance of a memory allocation manager
//! with the specified name and configuration.
//! This instance manages all memory region allocation within
//! the address range specified in the configuration descriptor.
//!
//! If a reference to a memory abstraction class is provided, the memory
//! locations within the regions can be accessed through the region
//! descriptor, using the uvm_mem_region::read() and
//! uvm_mem_region::write() methods.
//----------------------------------------------------------------------

uvm_mem_mam::uvm_mem_mam( const std::string& name,
                          uvm_mem_mam_cfg* cfg,
                          uvm_mem* mem )
{
  m_cfg = cfg;
  m_memory = mem;
  m_in_use.clear();

  default_alloc = new uvm_mem_mam_policy();
  m_for_each_idx = -1;
  m_lineno = 0;
  m_fname = "";
}

//----------------------------------------------------------------------
// Member function: reconfigure
//
//! Reconfigure the manager
//!
//! Modify the maximum and minimum addresses of the address space managed by
//! the allocation manager, allocation mode, or locality.
//! The number of bytes per memory location cannot be modified
//! once an allocation manager has been constructed.
//! All currently allocated regions must fall within the new address space.
//!
//! Returns the previous configuration.
//!
//! if no new configuration is specified, simply returns the current
//! configuration.
//----------------------------------------------------------------------

uvm_mem_mam_cfg* uvm_mem_mam::reconfigure( uvm_mem_mam_cfg* cfg )
{
  uvm_mem_mam_cfg* reconf;
  uvm_coreservice_t* cs = uvm_coreservice_t::get();
  uvm_root* top = cs->get_root();

  if (cfg == NULL)
    return m_cfg;

  // Cannot reconfigure n_bytes
  if (cfg->n_bytes != m_cfg->n_bytes) // TODO was !==
  {
    std::ostringstream str;
    str << "Cannot reconfigure Memory Allocation Manager with a different number of bytes ("
        << cfg->n_bytes
        << " !== "
        << m_cfg->n_bytes
        << ").";
    top->uvm_report_error("uvm_mem_mam", str.str(), UVM_LOW);
    return m_cfg;
  }

  // All currently allocated regions must fall within the new space
  for( unsigned int i = 0; i < m_in_use.size(); i++)
  {
    if (m_in_use[i]->get_start_offset() < cfg->start_offset ||
        m_in_use[i]->get_end_offset() > cfg->end_offset)
    {
      std::ostringstream str;
      str << "Cannot reconfigure Memory Allocation Manager with a currently "
          << "allocated region outside of the managed address range (["
          << m_in_use[i]->get_start_offset()
          << ":"
          << m_in_use[i]->get_end_offset()
          << "] outside of ["
          << cfg->start_offset
          << ":"
          << cfg->end_offset
          << "]).";
      top->uvm_report_error("uvm_mem_mam", str.str(), UVM_LOW);
      return m_cfg;
    }
  }

  reconf = m_cfg;
  m_cfg = cfg;

  return reconf;
}

//----------------------------------------------------------------------
// Group: Memory Management
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Member function: reserve_region
//
//! Reserve a specific memory region
//!
//! Reserve a memory region of the specified number of bytes
//! starting at the specified offset.
//! A descriptor of the reserved region is returned.
//! If the specified region cannot be reserved, null is returned.
//!
//! It may not be possible to reserve a region because
//! it overlaps with an already-allocated region or
//! it lies outside the address range managed
//! by the memory manager.
//!
//! Regions can be reserved to create "holes" in the managed address space.
//----------------------------------------------------------------------

uvm_mem_region* uvm_mem_mam::reserve_region( unsigned long start_offset,
                                             unsigned int n_bytes,
                                             const std::string& fname,
                                             int lineno )
{
  unsigned long _end_offset;
  uvm_mem_region* _region;

  m_fname = fname;
  m_lineno = lineno;

  if (n_bytes == 0)
  {
    UVM_ERROR("RegModel", "Cannot reserve 0 bytes");
    return NULL;
  }

  if (start_offset < m_cfg->start_offset)
  {
    std::ostringstream str;
    str << "Cannot reserve before start of memory space: 0x"
        << std::hex << start_offset
        << " < 0x"
        << std::hex << m_cfg->start_offset;
    UVM_ERROR("RegModel", str.str());
    return NULL;
  }

  _end_offset = start_offset + ((n_bytes-1) / m_cfg->n_bytes);
  n_bytes = (_end_offset - start_offset + 1) * m_cfg->n_bytes;

  if (_end_offset > m_cfg->end_offset)
  {
    std::ostringstream str;
    str << "Cannot reserve past end of memory space: 0x"
        << std::hex << _end_offset
        << " > 0x"
        << std::hex << m_cfg->end_offset
        << ".";
    UVM_ERROR("RegModel", str.str());
    return NULL;
  }

  std::ostringstream inf;
  inf << "Attempting to reserve [0x"
      << std::hex << start_offset
      << ":0x"
      << std::hex << _end_offset
      << "]...";
  UVM_INFO("RegModel", inf.str(), UVM_MEDIUM);

  for ( m_in_use_itt it = m_in_use.begin();
        it != m_in_use.end();
        it++ )
  {
    if (start_offset <= (*it)->get_end_offset() &&
        _end_offset >= (*it)->get_start_offset())
    {
      // Overlap!
      std::ostringstream str;
      str << "Cannot reserve [0x"
          << std::hex << start_offset
          << ":0x"
          << std::hex << _end_offset
          << "] because it overlaps with "
          << (*it)->convert2string()
          << ".";
      UVM_ERROR("RegModel", str.str());
      return NULL;
    }

    // Regions are stored in increasing start offset
    if (start_offset > (*it)->get_start_offset())
    {
      _region = new uvm_mem_region(start_offset, _end_offset,
        _end_offset - start_offset + 1, n_bytes, this);
      m_in_use.insert(it, _region);
      return _region;
    }
  }

  _region = new uvm_mem_region(start_offset, _end_offset,
      _end_offset - start_offset + 1, n_bytes, this);
  m_in_use.push_back(_region);

  return _region;
}


//----------------------------------------------------------------------
// Member function: request_region
//
//! Request and reserve a memory region
//!
//! Request and reserve a memory region of the specified number
//! of bytes starting at a random location.
//! If an policy is specified, it is randomized to determine
//! the start offset of the region.
//! If no policy is specified, the policy found in
//! the uvm_mem_mam::default_alloc class property is randomized.
//!
//! A descriptor of the allocated region is returned.
//! If no region can be allocated, NULL is returned.
//!
//! It may not be possible to allocate a region because
//! there is no area in the memory with enough consecutive locations
//! to meet the size requirements or
//! because there is another contradiction when randomizing
//! the policy.
//!
//! If the memory allocation is configured to THRIFTY or NEARBY,
//! a suitable region is first sought procedurally.
//----------------------------------------------------------------------


uvm_mem_region* uvm_mem_mam::request_region( unsigned int n_bytes,
                                             uvm_mem_mam_policy* alloc,
                                             const std::string& fname,
                                             int lineno )
{

  m_fname = fname;
  m_lineno = lineno;

  if (alloc == NULL)
    alloc = default_alloc;

  alloc->len        = (n_bytes-1) / m_cfg->n_bytes + 1;
  alloc->min_offset = m_cfg->start_offset;
  alloc->max_offset = m_cfg->end_offset;
  alloc->in_use     = m_in_use;

  /* TODO error for randomize
  if (!alloc->randomize())
  {
    UVM_ERROR("RegModel", "Unable to randomize policy");
    return NULL;
  }
  */
  return reserve_region(alloc->start_offset, n_bytes);
}


//----------------------------------------------------------------------
// Member function: release_region
//
//! Release the specified region
//!
//! Release a previously allocated memory region.
//! An error is issued if the
//! specified region has not been previously allocated or
//! is no longer allocated.
//----------------------------------------------------------------------

void uvm_mem_mam::release_region( uvm_mem_region* region )
{
  if (region == NULL) return;

  for( m_in_use_itt it = m_in_use.begin();
       it != m_in_use.end();
       it++ )
  {
    if ((*it) == region)
    {
      delete (*it); // clear memory alloc
      m_in_use.erase(it); // delete entry from vector list
      return;
    }
  }
  UVM_ERROR("RegModel", "Attempting to release unallocated region\n" +
      region->convert2string());
}

//----------------------------------------------------------------------
// Member function: release_all_regions
//
// Forcibly release all allocated memory regions.
//----------------------------------------------------------------------

void uvm_mem_mam::release_all_regions()
{
  // TODO check correctness of clean-up
  for( m_in_use_itt it = m_in_use.begin();
       it != m_in_use.end();
       it++ )
    delete (*it); // clear memory alloc

  m_in_use.clear(); // clear vector list with pointers
}



//----------------------------------------------------------------------
// Group: Introspection
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Member function: convert2string
//
//! Image of the state of the manager
//!
//! Create a human-readable description of the state of
//! the memory manager and the currently allocated regions.
//----------------------------------------------------------------------

std::string uvm_mem_mam::convert2string()
{
  std::ostringstream str;

  str << "Allocated memory regions:\n";

  for( unsigned int i = 0; i < m_in_use.size(); i++ )
  {
     str << "   "<< m_in_use[i]->convert2string() << "\n";
  }

  return str.str();
}

//----------------------------------------------------------------------
// Member function: for_each
//
//! Iterate over all currently allocated regions
//!
//! If reset is TRUE, reset the iterator
//! and return the first allocated region.
//! Returns NULL when there are no additional allocated
//! regions to iterate on.
//----------------------------------------------------------------------

uvm_mem_region* uvm_mem_mam::for_each( bool reset )
{
   if (reset)
     m_for_each_idx = -1;

   m_for_each_idx++;

   if (m_for_each_idx >= (int)m_in_use.size())
      return NULL;

   return m_in_use[m_for_each_idx];
}

//----------------------------------------------------------------------
// Member function: get_memory
//
//! Get the managed memory implementation
//!
//! Return the reference to the memory abstraction class
//! for the memory implementing
//! the locations managed by this instance of the allocation manager.
//! Returns NULL if no
//! memory abstraction class was specified at construction time.
//----------------------------------------------------------------------

uvm_mem* uvm_mem_mam::get_memory() const
{
  return m_memory;
}

//----------------------------------------------------------------------
// Destructor
//
// Implementation defined
//----------------------------------------------------------------------

uvm_mem_mam::~uvm_mem_mam()
{
  delete default_alloc;

  release_all_regions();
}

} // namespace uvm
