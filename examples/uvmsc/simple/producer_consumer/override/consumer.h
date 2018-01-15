//----------------------------------------------------------------------
//   Copyright 2009 Cadence Design Systems, Inc.
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

#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <systemc>
#include <uvm>

// define a basic consumer that does not process the 
// input tokens; implement put() to simply print the
// token to screen

template <typename T>
class consumer : public uvm::uvm_component
{
 public:
  uvm::uvm_blocking_put_imp<T, consumer<T> > in;

  // constructor
  consumer(uvm::uvm_component_name nm)
  : uvm::uvm_component(nm),
    in("in", this)
  {}

  // use macro to generate methods that the factory requires
  UVM_COMPONENT_PARAM_UTILS(consumer<T>);

  // define put() which will consume tokens
  // made virtual, so an override will re-implement this
  virtual void put(const T& t)
  {
    // process token t

    std::ostringstream info;
    info << "consumer received " << t;
    UVM_INFO(get_full_name(), info.str(), uvm::UVM_NONE);

    sc_core::wait(5, sc_core::SC_NS);
  }
};

#endif /* CONSUMER_H_ */
