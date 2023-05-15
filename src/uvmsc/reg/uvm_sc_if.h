//----------------------------------------------------------------------
//   Copyright 2016-2021 NXP B.V.
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

// simple SystemC RW interface for demonstration of UVM backdoor purpose only

#ifndef UVM_SC_IF_H_
#define UVM_SC_IF_H_

#include <systemc>

namespace uvm {


template <typename T>
class uvm_sc_if
{
 public:
  uvm_sc_if(){}

  virtual bool write(const T& v, int start = -1, int stop = -1) = 0;
  virtual T read(int start = -1, int stop = -1) const = 0;
};


} // namespace uvm

#endif // UVM_SC_IF_H_
