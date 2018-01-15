//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
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

#include <systemc>
#include <uvm>

#include "testbench.h"
#include "dut.h"
#include "vip_if.h"

int sc_main(int, char*[]) 
{  
  // instantiate the DUT
  dut* my_dut = new dut("my_dut");
  testbench* tb = new testbench("tb");

  //uvm_config_db_options::turn_on_tracing();

  vip_if* dut_if_in = new vip_if();
  vip_if* dut_if_out = new vip_if();

  uvm::uvm_config_db<vip_if*>::set(0, "tb.agent1.*", "vif", dut_if_in);
  uvm::uvm_config_db<vip_if*>::set(0, "tb.agent2.*", "vif", dut_if_out);

  my_dut->in(dut_if_in->sig_data);
  my_dut->out(dut_if_out->sig_data);

  uvm::run_test();

  return 0;
}
