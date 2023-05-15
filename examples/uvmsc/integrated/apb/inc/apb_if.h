// 
// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
//    Copyright 2010 Cadence Design Systems, Inc.
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


#ifndef APB_IF_H_
#define APB_IF_H_

#include <systemc>
#include <uvm>

class apb_if : public sc_core::sc_module {
    public:
        apb_if(const sc_core::sc_module_name & name) :
            sc_module(name),
            pclk("pclk"),
            paddr("paddr"),
            psel("psel"),
            penable("penable"),
            pwrite("pwrite"),
            prdata("prdata"),
            pwdata("pwdata") {}

        sc_core::sc_signal<sc_dt::sc_logic>  pclk;
        sc_core::sc_signal<sc_dt::sc_lv<32>> paddr;
        sc_core::sc_signal<sc_dt::sc_logic>  psel;
        sc_core::sc_signal<sc_dt::sc_logic>  penable;
        sc_core::sc_signal<sc_dt::sc_logic>  pwrite;
        sc_core::sc_signal<sc_dt::sc_lv<32>> prdata;
        sc_core::sc_signal<sc_dt::sc_lv<32>> pwdata;
};

#endif /* APB_IF_H_ */
