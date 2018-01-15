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
//
//   Original Author: Martin Barnasconi, NXP Semiconductors
//   Created on: 2012-10-27
//
//----------------------------------------------------------------------

#ifndef DUT_H_
#define DUT_H_

#include <systemc>

class dut : public sc_core::sc_module
{
 public:
  sc_core::sc_in<int> in;
  sc_core::sc_out<int> out;

  void func()
  {
    int val;
    val = in.read();
    std::cout << sc_core::sc_time_stamp() << ": " << name() << " received value " << val << std::endl;
    std::cout << sc_core::sc_time_stamp() << ": " << name() << " send value " << val+1 << std::endl;
    out.write(val+1);
  }

  SC_CTOR(dut) : in("in"), out("out")
  {
    SC_METHOD(func);
    sensitive << in;
  }

};

#endif /* DUT_H_ */
