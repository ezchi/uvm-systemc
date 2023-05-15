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

#ifndef TB_TEST_H_
#define TB_TEST_H_

#include <systemc>
#include <uvm>

class tb_test : public uvm::uvm_test
{
    public:
        tb_test(uvm::uvm_component_name name = "tb_test"/*, uvm::uvm_component* parent = nullptr*/) :
            uvm::uvm_test(name/*, parent*/)
    {}

        virtual void run_phase(uvm::uvm_phase & phase);
};

#endif /* TB_TEST_H_ */
