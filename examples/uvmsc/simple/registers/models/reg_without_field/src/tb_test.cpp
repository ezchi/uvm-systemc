// 
// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
//    Copyright 2010-2011 Cadence Design Systems, Inc.
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

#include "../inc/tb_test.h"
#include "../inc/reg_model.h"
#include "../inc/tb_env.h"

void tb_test::run_phase(uvm::uvm_phase & phase)
{
    tb_env* env{nullptr};
    uvm::uvm_status_e status;
    uvm::uvm_reg_data_t dat;
    uvm::uvm_root* uvm_top;
    uvm_top = uvm::uvm_root::get();

    phase.raise_objection(this);

    if (!(env = dynamic_cast<tb_env*>(uvm_top->find("env"))) || env == nullptr) {
        UVM_FATAL("test", "Cannot find tb_env");
    }

    env->regmodel->R->reset();
    env->regmodel->R->read(status, dat);
    if (dat != 0x0) {
        std::ostringstream str;
        str << std::hex
            << "R is not as expected after reset: 0x" << dat
            << " instead of 0x0";
        UVM_ERROR("Test", str.str());
    }
    env->regmodel->R->write(status, 0xFF);
    env->regmodel->R->read(status, dat);
    if (dat != 0xFF) {
        std::ostringstream str;
        str << std::hex
            << "R is not as expected after reset: 0x" << dat
            << " instead of 0xFF";
        UVM_ERROR("Test", str.str());
    }
    // TODO
    /* env->regmodel->randomize() with { R.value = 0xA5; }; */
    env->regmodel->R->write(status, 0xA5);
    dat = env->regmodel->R->get();
    if (dat != 0xA5) {
        std::ostringstream str;
        str << std::hex
            << "R is not as expected after reset: 0x" << dat
            << " instead of 0xA5";
        UVM_ERROR("Test", str.str());
    }

    phase.drop_objection(this);
}
