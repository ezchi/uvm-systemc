//----------------------------------------------------------------------
//   Copyright 2016 NXP B.V.
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

// simple dummy register class for demonstration of uvm-backdoor purpose only

#ifndef UVM_SC_REG_H_
#define UVM_SC_REG_H_

#include <systemc>

class uvm_sc_reg_base : public sc_core::sc_object
{
 public:

  uvm_sc_reg_base(const char* name)
  : sc_core::sc_object(name)
  {}
};


template <typename T>
class uvm_sc_reg : public uvm_sc_reg_base
{
 public:
  uvm_sc_reg(const char* name)
  : uvm_sc_reg_base(name)
  {}

  uvm_sc_reg()
  : uvm_sc_reg_base(sc_core::sc_gen_unique_name("sc_reg"))
  {}

  uvm_sc_reg& operator=(const T& value)
  {
    write(value, -1, -1);
    return *this;
  }

  uvm_sc_reg& operator=(const uvm_sc_reg& reg)
  {
    write(reg.read(), -1, -1);
    return *this;
  }

  bool write(const T& value, int start=-1, int stop=-1)
  {
    using namespace sc_core;

    if (start==-1)
    {
      reg = value;
      ev.notify();
      return true;
    }

    if (stop ==-1)
    {
      reg[start] = value;
      ev.notify();
      return true;
    }

    reg.range(start,stop) = value;
    ev.notify();
    return true;
  }

  T read(int start=-1, int stop=-1) const
  {
    T tmp;

    if (start==-1)
    {
      tmp = reg;
      return tmp;
    }

    if (stop ==-1)
    {
      tmp = reg[start];
      return tmp;
    }

    tmp = reg.range(start, stop);
    return tmp;
  }

  unsigned int to_uint() const
  {
    return reg.to_uint();
  }

  const sc_core::sc_event& default_event() const
  {
    return ev;
  }

  const sc_core::sc_event& value_changed_event() const
  {
    return ev;
  }

  // data members
 private:
  T reg;
  sc_core::sc_event ev;
};

#endif // UVM_SC_REG_H_
