//----------------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
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
//----------------------------------------------------------------------------

#ifndef UVM_FACTORY_OVERRIDE_H_
#define UVM_FACTORY_OVERRIDE_H_

#include <string>

//////////////////////

namespace uvm {


// forward class declarations
class uvm_object_wrapper;


//----------------------------------------------------------------------------
// Class: uvm_factory_override
//
// Implementation defined class
//----------------------------------------------------------------------------

class uvm_factory_override
{
 public:
  uvm_factory_override( const std::string& full_inst_path_ = "",
                        const std::string& orig_type_name_ = "",
                        uvm_object_wrapper* orig_type_ = NULL,
                        uvm_object_wrapper* ovrd_type_ = NULL );

 public: //data members
  std::string full_inst_path;
  std::string orig_type_name;
  std::string ovrd_type_name;
  bool selected;
  uvm_object_wrapper* orig_type;
  uvm_object_wrapper* ovrd_type;
};


} // namespace uvm

//////////////////////

#endif // UVM_FACTORY_OVERRIDE_H_
