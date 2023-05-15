//
//------------------------------------------------------------------------------
//   Copyright 2021 NXP B.V.
//   Copyright 2011 Mentor Graphics Corporation
//   Copyright 2011 Cadence Design Systems, Inc. 
//   Copyright 2011 Synopsys, Inc.
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
//------------------------------------------------------------------------------
//

#include <systemc>
#include <uvm>

#include "../inc/reg_model.h"

reg_R::~reg_R()
{
    if (_dummy) {
        delete _dummy;
    }
}

void reg_R::build()
{
    _dummy = uvm::uvm_reg_field::type_id::create("value");
    _dummy->configure(this, 8, 0, "RW", 0, 0x0, 1, 1, 1);
}

void block_B::build()
{
    default_map = create_map("default_map", 0, 4, uvm::UVM_BIG_ENDIAN);

    R = reg_R::type_id::create("R");
    R->configure(this, NULL);
    R->build();

    default_map->add_reg(R, 0x0, "RW");
}
