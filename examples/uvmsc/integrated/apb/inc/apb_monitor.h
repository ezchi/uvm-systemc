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

#ifndef APB_MONITOR_H_
#define APB_MONITOR_H_

#include <systemc>
#include <uvm>

#include "apb_if.h"
#include "apb_rw.h"

class apb_monitor : public uvm::uvm_monitor
{
    public:
        apb_if* sigs;

        uvm::uvm_analysis_port<apb_rw> ap;

        UVM_COMPONENT_UTILS(apb_monitor);

        apb_monitor(uvm::uvm_component_name name);

        virtual void build_phase(uvm::uvm_phase & phase);

        virtual void run_phase(uvm::uvm_phase & phase);
};

#endif /* APB_MONITOR_H_ */