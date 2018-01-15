//----------------------------------------------------------------------
//   Copyright 2013-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2012-2017 NXP B.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010-2011 Synopsys, Inc.
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

#include "uvmsc/factory/uvm_factory_override.h"
#include "uvmsc/base/uvm_globals.h"
#include "uvmsc/factory/uvm_object_wrapper.h"

namespace uvm {

//----------------------------------------------------------------------------
// constructor uvm_factor_overridey
//----------------------------------------------------------------------------

uvm_factory_override::uvm_factory_override( const std::string& full_inst_path_,
                                            const std::string& orig_type_name_,
                                            uvm_object_wrapper* orig_type_,
                                            uvm_object_wrapper* ovrd_type_ )
{
  if (ovrd_type_ == NULL)
    uvm_report_fatal( "NULLWR",
                      "Attempting to register a NULL override object with the factory",
                      UVM_NONE);

  full_inst_path = full_inst_path_;
  orig_type_name = (orig_type_ == NULL) ? orig_type_name_ : (orig_type_->get_type_name() );
  orig_type      = orig_type_;
  ovrd_type_name = ovrd_type_->get_type_name();
  ovrd_type      = ovrd_type_;
}

} // namespace uvm
