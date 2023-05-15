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

#include "../inc/apb_agent.h"
#include "../inc/apb_sequencer.h"
#include "../inc/apb_master.h"
#include "../inc/apb_monitor.h"

apb_agent::apb_agent(uvm::uvm_component_name name) :
    uvm::uvm_agent(name),
    sqr(nullptr),
    drv(nullptr),
    mon(nullptr),
    vif(nullptr)
{}

apb_agent::~apb_agent()
{
    if (sqr)
    {
        delete sqr;
    }
    if (drv)
    {
        delete drv;
    }
    if (mon)
    {
        delete mon;
    }
}

void apb_agent::build_phase(uvm::uvm_phase& phase)
{
    uvm::uvm_agent::build_phase(phase);

    mon = apb_monitor::type_id::create("mon", this);
    assert(mon);

    if (get_is_active() == uvm::UVM_ACTIVE)
    {
        sqr = apb_sequencer::type_id::create("sqr", this);
        assert(sqr);
        drv = apb_master::type_id::create("drv", this);
        assert(drv);
    }

    if (!uvm::uvm_config_db<apb_if*>::get(this, "", "vif", vif)) {
        UVM_FATAL("APB/AGT/NOVIF", "No virtual interface specified for this agent instance");
    }
}

void apb_agent::connect_phase(uvm::uvm_phase& phase)
{
    if (get_is_active() == uvm::UVM_ACTIVE) {
        drv->seq_item_port.connect(sqr->seq_item_export);
    }
}
