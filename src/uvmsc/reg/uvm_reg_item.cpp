//----------------------------------------------------------------------
//   Copyright 2013-2015 NXP B.V.
//   Copyright 2004-2009 Synopsys, Inc.
//   Copyright 2010 Mentor Graphics Corporation
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

#include "uvmsc/reg/uvm_reg_item.h"
#include "uvmsc/reg/uvm_reg_map.h"

namespace uvm {

//----------------------------------------------------------------------
// Constructor
//
//! Create a new instance of this type, giving it the optional \p name.
//----------------------------------------------------------------------

uvm_reg_item::uvm_reg_item( const std::string& name ) : uvm_sequence_item(name)
  , value(1)
{
  element = NULL;
  local_map = NULL;
  parent = NULL;
  extension = NULL;

  prior = -1;
}


//----------------------------------------------------------------------
// member function: convert2string
//
//! Returns a string showing the contents of this transaction.
//----------------------------------------------------------------------

std::string uvm_reg_item::convert2string() const
{
  std::ostringstream s, value_s;

  s << "access_kind = " << uvm_access_name[access_kind]
    << " element_kind = " << uvm_elem_kind_name[element_kind]
    << " element_name = " << ( (element == NULL) ? "NULL" : element->get_full_name() );

  if(value.size() > 1 && uvm_report_enabled(UVM_HIGH, UVM_INFO, "RegModel"))
  {
    value_s << "'{";

    for( unsigned int i = 0; i < value.size(); i++ )
       value_s << "0x" << std::hex << value[i].to_uint64() << std::endl;

    value_s << "}";
  }
  else
    value_s << "0x" << std::hex << value[0].to_uint64();

  s << " value=" << value_s.str();

  if (element_kind == UVM_MEM)
    s << " offset = 0x" << std::hex << offset.to_uint64();

  s << " map = "
    << ( map == NULL ? "NULL" : map->get_full_name() )
    << " path = " << uvm_path_name[path]
    << " status = " << uvm_status_name[status];

  return s.str();
}

//----------------------------------------------------------------------
// member function: do_copy
//
//! Copy the \p rhs object into this object. The \p rhs object must
//! derive from uvm_reg_item.
//----------------------------------------------------------------------

void uvm_reg_item::do_copy( const uvm_object& rhs )
{
  const uvm_reg_item* rhs_;

  rhs_ = dynamic_cast<const uvm_reg_item*>(&rhs);

  if (rhs_ == NULL)
  {
    UVM_ERROR("WRONG_TYPE","Provided rhs is not of type uvm_reg_item");
    return;
  }

  uvm_sequence_item::copy(rhs);

  element_kind = rhs_->element_kind;
  element = rhs_->element;
  access_kind = rhs_->access_kind;
  value = rhs_->value;
  offset = rhs_->offset;
  status = rhs_->status;
  local_map = rhs_->local_map;
  map = rhs_->map;
  path = rhs_->path;
  extension = rhs_->extension;
  bd_kind = rhs_->bd_kind;
  parent = rhs_->parent;
  prior = rhs_->prior;
  fname = rhs_->fname;
  lineno = rhs_->lineno;
}

} // namespace uvm
