// 
// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010-2011 Mentor Graphics Corporation
//    All Rights Reserved Worldwide
// 
//    Licensed under the Apache License, Version 2.0 (the
//    "License"); you may not use this file except in
//    compliance with the License.  You may obtain a copy of
//    the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in
//    writing, software distributed under the License is
//    distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//    CONDITIONS OF ANY KIND, either express or implied.  See
//    the License for the specific language governing
//    permissions and limitations under the License.
// -------------------------------------------------------------
// 

#include <systemc>
#include <uvm>

#include "../inc/tb_env.h"

tb_env::~tb_env()
{
    if (regmodel) {
        delete regmodel;
    }
    if (fd) {
        delete fd;
    }
}

void tb_env::build_phase(uvm::uvm_phase & phase)
{
    regmodel = block_B::type_id::create("regmodel");
    regmodel->build();
    regmodel->lock_model();
}

void tb_env::connect_phase(uvm::uvm_phase & phase)
{
    fd = new reg_R_fd();
    regmodel->R->set_frontdoor(fd);
    regmodel->default_map->set_auto_predict(1);
}

void reg_R_fd::body()
{
    if (rw_info->access_kind == uvm::UVM_WRITE) {
        R = rw_info->value[0];
    }
    else {
        rw_info->value[0] = R;
    }
}
