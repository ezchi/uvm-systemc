//------------------------------------------------------------------------------
//   Copyright 2010 Mentor Graphics Corporation
//   Copyright 2013-2014 NXP B.V.
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
//------------------------------------------------------------------------------
//
// This example demonstrates the 6 sequence priority algorithms
// available via the uvm_sequencer.
//
// It contains a sequence which runs 4 sub-sequences on a driver
// which counts how many sequence_items it has received from each
// sub-sequencer. To add some interest, the sub-sequences have different
// priorities and are offset in time:
//
// seq_1 - Has priority 500 (highest) and generates new items after a delay of #1;
// seq_2 - Has priority 500 (joint-highest) and generates new items after a delay of #2;
// seq_3 - Has priority 300 (medium) and generates new items after a delay of #3;
// seq_4 - Has priority 200 (lowest) and generates new items after a delay of #4;
//
// To run the different examples then the following needs to typed at the vsim command line:
//
// vsim +ARB_TYPE=<arb_type> top -do "run -all"
//
// Where ARB_TYPE is one of SEQ_ARB_FIFO, SEQ_ARB_WEIGHTED, SEQ_ARB_RANDOM,
//                          SEQ_ARB_STRICT_FIFO, SEQ_ARB_STRICT_RANDOM,
//                          SEQ_ARB_USER
//
// The driver will display a log of how many sequence items have been received
// from each sequence.
//
// The user arbitration method implemented for the SEQ_ARB_USER option is to always
// select the item last added to the sequence_item queue. This is the inverse of
// the default algorithm (SEQ_ARB_FIFO).
//
// from : https://verificationacademy.com/cookbook/Sequences/Arbitration
//------------------------------------------------------------------------------

#include <uvm>
#include <systemc>

#include "arb_test.h"

int sc_main(int, char*[])
{
  // TODO move arb_type setting to command line option
  uvm::uvm_config_db<int>::set(0, "*", "arb_type", uvm::SEQ_ARB_STRICT_RANDOM );

  uvm::run_test("arb_test");

  return 0;
}
