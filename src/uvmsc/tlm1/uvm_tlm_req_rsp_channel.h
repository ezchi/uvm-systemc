//----------------------------------------------------------------------
//   Copyright 2014-2015 NXP B.V.
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

#ifndef UVM_TLM_REQ_RSP_CHANNEL_H_
#define UVM_TLM_REQ_RSP_CHANNEL_H_

#include <systemc>
#include <tlm.h>

namespace uvm {

//----------------------------------------------------------------------
// Class: uvm_tlm_req_rsp_channel<REQ,RSP>
//
//! The #uvm_tlm_req_rsp_channel contains a request FIFO of type REQ and
//! a response FIFO of type RSP. These FIFOs can be of any size. This channel is
//! particularly useful for dealing with pipelined protocols where the request
//! and response are not tightly coupled.
//!
//! Type parameters:
//!
//! REQ:         Type of the request transactions conveyed by this channel.
//! RSP:         Type of the response transactions conveyed by this channel.
//! REQ_CHANNEL: Type of TLM FIFO used for the request transactions
//! RSP_CHANNEL: Type of TLM FIFO used for the response transactions
//----------------------------------------------------------------------

template < typename REQ , typename RSP = REQ ,
     typename REQ_CHANNEL = tlm::tlm_fifo<REQ> ,
     typename RSP_CHANNEL = tlm::tlm_fifo<RSP> >
class uvm_tlm_req_rsp_channel : public tlm::tlm_req_rsp_channel<REQ,RSP,REQ_CHANNEL,RSP_CHANNEL>
{
 public:
  uvm_tlm_req_rsp_channel( int req_size = 1 , int rsp_size = 1 ) :
    tlm::tlm_req_rsp_channel<REQ,RSP,REQ_CHANNEL,RSP_CHANNEL>(req_size, rsp_size)
  {}

  uvm_tlm_req_rsp_channel( uvm_component_name name,
                           int req_size = 1, int rsp_size = 1 ) :
    tlm::tlm_req_rsp_channel<REQ,RSP,REQ_CHANNEL,RSP_CHANNEL>(name.name(), req_size, rsp_size)
  {}

  // TODO add UVM-SV specific exports and analysis ports
};


/////////////////////////////////////////////

} /* namespace uvm */

#endif /* UVM_TLM_REQ_RSP_CHANNEL_H_ */
