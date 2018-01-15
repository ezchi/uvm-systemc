//----------------------------------------------------------------------
//   Copyright 2013-2016 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010-2011 Mentor Graphics Corporation
//   Copyright 2010 Cadence Design Systems, Inc.
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

#include <iostream>
#include <string>

#include "uvmsc/reg/uvm_mem_region.h"
#include "uvmsc/reg/uvm_mem.h"
#include "uvmsc/reg/uvm_mem_mam.h"

namespace uvm {

//----------------------------------------------------------------------
// Member function: get_start_offset
//
//! Get the start offset of the region
//!
//! Return the address offset, within the memory,
//! where this memory region starts.
//----------------------------------------------------------------------

unsigned long uvm_mem_region::get_start_offset() const
{
  return m_start_offset;
}

//----------------------------------------------------------------------
// Member function: get_end_offset
//
//! Get the end offset of the region
//!
//! Return the address offset, within the memory,
//! where this memory region ends.
//----------------------------------------------------------------------

unsigned long uvm_mem_region::get_end_offset() const
{
  return m_end_offset;
}

//----------------------------------------------------------------------
// Member function: get_len
//
//! Size of the memory region
//!
//! Return the number of consecutive memory locations
//! (not necessarily bytes) in the allocated region.
//----------------------------------------------------------------------

unsigned int uvm_mem_region::get_len() const
{
   return m_len;
}


//----------------------------------------------------------------------
// Member function: get_n_bytes
//
//! Number of bytes in the region
//!
//! Return the number of consecutive bytes in the allocated region.
//! If the managed memory contains more than one byte per address,
//! the number of bytes in an allocated region may
//! be greater than the number of requested or reserved bytes.
//----------------------------------------------------------------------

unsigned int uvm_mem_region::get_n_bytes() const
{
  return m_n_bytes;
}

//----------------------------------------------------------------------
// Member function: release_region
//
//! Release this region
//----------------------------------------------------------------------

void uvm_mem_region::release_region()
{
   m_parent->release_region(this);
}

//----------------------------------------------------------------------
// Member function: get_memory
//
//! Get the memory where the region resides
//!
//! Return a reference to the memory abstraction class
//! for the memory implementing this allocated memory region.
//! Returns NULL if no memory abstraction class was specified
//! for the allocation manager that allocated this region.
//----------------------------------------------------------------------

uvm_mem* uvm_mem_region::get_memory() const
{
  return m_parent->get_memory();
}


//----------------------------------------------------------------------
// Member function: get_virtual_registers
//
//! Get the virtual register array in this region
//!
//! Return a reference to the virtual register array abstraction class
//! implemented in this region.
//! Returns NULL if the memory region is
//! not known to implement virtual registers.
//----------------------------------------------------------------------

uvm_vreg* uvm_mem_region::get_virtual_registers() const
{
   return m_vreg;
}

//----------------------------------------------------------------------
// Member function: write
//
//! Write to a memory location in the region.
//!
//! Write to the memory location that corresponds to the
//! specified \p offset within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::write() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::write( uvm_status_e& status, // output
                            uvm_reg_addr_t offset,
                            uvm_reg_data_t value,
                            uvm_path_e path,
                            uvm_reg_map* map,
                            uvm_sequence_base* parent,
                            int prior,
                            uvm_object* extension,
                            const std::string& fname,
                            int lineno )
{
  uvm_mem* mem = m_parent->get_memory();

  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::write() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset > m_len)
  {
    std::ostringstream str;
    str << "Attempting to write to an offset outside of the allocated region ("
        << offset
        << " > "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str() );
    status = UVM_NOT_OK;
    return;
  }

  mem->write(status, offset + get_start_offset(), value,
    path, map, parent, prior, extension);
}

//----------------------------------------------------------------------
// Member function: read
//
//! Read from a memory location in the region.
//!
//! Read from the memory location that corresponds to the
//! specified \p offset within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::read() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::read( uvm_status_e& status, // output
                           uvm_reg_addr_t offset,
                           uvm_reg_data_t& value, // output
                           uvm_path_e path,
                           uvm_reg_map* map,
                           uvm_sequence_base* parent,
                           int prior,
                           uvm_object* extension,
                           const std::string& fname,
                           int lineno )
{
  uvm_mem* mem = m_parent->get_memory();

  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::read() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset > m_len)
  {
    std::ostringstream str;
    str << "Attempting to read from an offset outside of the allocated region ("
        << offset
        << " > "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str());
    status = UVM_NOT_OK;
    return;
  }

  mem->read(status, offset + get_start_offset(), value,
    path, map, parent, prior, extension);
}

//----------------------------------------------------------------------
// Member function: burst_write
//
//! Write to a set of memory location in the region.
//!
//! Write to the memory locations that corresponds to the
//! specified \p burst within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::burst_write() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::burst_write( uvm_status_e& status, // output
                                  uvm_reg_addr_t offset,
                                  std::vector<uvm_reg_data_t> value,
                                  uvm_path_e path,
                                  uvm_reg_map* map,
                                  uvm_sequence_base* parent,
                                  int prior,
                                  uvm_object* extension,
                                  const std::string& fname,
                                  int lineno )
{
  uvm_mem* mem = m_parent->get_memory();

  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::burst_write() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset + value.size() > m_len)
  {
    std::ostringstream str;
    str << "Attempting to burst-write to an offset outside of the allocated region (burst to ["
        << offset
        << ":"
        << offset + value.size()
        << "] > mem_size "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str() );
    status = UVM_NOT_OK;
    return;
  }

  mem->burst_write(status, offset + get_start_offset(), value,
    path, map, parent, prior, extension);
}



//----------------------------------------------------------------------
// Member function: burst_read
//
//! Read from a set of memory location in the region.
//!
//! Read from the memory locations that corresponds to the
//! specified \p burst within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::burst_read() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::burst_read( uvm_status_e& status, // output
                                 uvm_reg_addr_t offset,
                                 std::vector<uvm_reg_data_t>& value, //output
                                 uvm_path_e path,
                                 uvm_reg_map* map,
                                 uvm_sequence_base* parent,
                                 int prior,
                                 uvm_object* extension,
                                 const std::string& fname,
                                 int lineno )
{
  uvm_mem* mem = m_parent->get_memory();

  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::burst_read() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset + value.size() > m_len)
  {
    std::ostringstream str;
    str << "Attempting to burst-read to an offset outside of the allocated region (burst to ["
        << offset
        << ":"
        << offset + value.size()
        << "] > mem_size "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str() );
    status = UVM_NOT_OK;
    return;
  }

  mem->burst_read(status, offset + get_start_offset(), value,
      path, map, parent, prior, extension);
}

//----------------------------------------------------------------------
// Member function: poke
//
//! Deposit in a memory location in the region.
//!
//! Deposit the specified value in the memory location
//! that corresponds to the
//! specified \p offset within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::poke() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::poke( uvm_status_e& status, // output
                           uvm_reg_addr_t offset,
                           uvm_reg_data_t value,
                           uvm_sequence_base* parent,
                           uvm_object* extension,
                           const std::string& fname,
                           int lineno )
{
  uvm_mem* mem = m_parent->get_memory();

  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::poke() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset > m_len)
  {
    std::ostringstream str;
    str << "Attempting to poke to an offset outside of the allocated region ("
        << offset
        << " > "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str() );
    status = UVM_NOT_OK;
    return;
  }

  mem->poke(status, offset + get_start_offset(), value, "", parent, extension);
}

//----------------------------------------------------------------------
// Member function: peek
//
//! Sample a memory location in the region.
//!
//! Sample the memory location that corresponds to the
//! specified \p offset within this region.
//! Requires that the memory abstraction class be associated with
//! the memory allocation manager that allocated this region.
//!
//! See uvm_mem::peek() for more details.
//----------------------------------------------------------------------

void uvm_mem_region::peek( uvm_status_e& status, // output
                           uvm_reg_addr_t offset,
                           uvm_reg_data_t& value, // output
                           uvm_sequence_base* parent,
                           uvm_object* extension,
                           const std::string& fname,
                           int lineno )
{
  uvm_mem* mem = m_parent->get_memory();
  m_fname = fname;
  m_lineno = lineno;

  if (mem == NULL)
  {
    UVM_ERROR("RegModel", "Cannot use uvm_mem_region::peek() on a region that was allocated by a Memory Allocation Manager that was not associated with a uvm_mem instance");
    status = UVM_NOT_OK;
    return;
  }

  if (offset > m_len)
  {
    std::ostringstream str;
    str << "Attempting to peek from an offset outside of the allocated region ("
        << offset
        << " > "
        << m_len
        << ").";
    UVM_ERROR("RegModel", str.str() );
    status = UVM_NOT_OK;
    return;
  }

  mem->peek(status, offset + get_start_offset(), value, "", parent, extension);
}

//----------------------------------------------------------------------
// Constructor
//
// Implementation defined
//----------------------------------------------------------------------

uvm_mem_region::uvm_mem_region( unsigned long start_offset,
                                unsigned long end_offset,
                                unsigned int len,
                                unsigned int n_bytes,
                                uvm_mem_mam* parent )
  : m_len(len), m_n_bytes(n_bytes), m_parent(parent),
    m_start_offset(start_offset), m_end_offset(end_offset)
{
  m_vreg = NULL;
  m_lineno = 0;
  m_fname = "";

}

//----------------------------------------------------------------------
// Member function: convert2string
//
// Implementation defined
//----------------------------------------------------------------------

std::string uvm_mem_region::convert2string()
{
  // TODO seems incomplete...
  // $sformat(convert2string, "['h%h:'h%h]",
  //          this.Xstart_offsetX, this.Xend_offsetX);
  return "";
}

} // namespace uvm
