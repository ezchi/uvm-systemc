//----------------------------------------------------------------------
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010-2011 Synopsys, Inc.
//   Copyright 2012-2015 NXP B.V.
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

#ifndef UVM_SEQUENCER_PARAM_BASE_H_
#define UVM_SEQUENCER_PARAM_BASE_H_

#include <sstream>
#include <tlm.h>

#include <list>

#include "uvmsc/base/uvm_component_name.h"
#include "uvmsc/seq/uvm_sequencer_base.h"
#include "uvmsc/seq/uvm_sequence_base.h"
#include "uvmsc/base/uvm_transaction.h"
#include "uvmsc/base/uvm_object_globals.h"

namespace uvm {

// forward declarations
//class uvm_sequence_base;
class uvm_sequence_item;

//----------------------------------------------------------------------
// CLASS: uvm_sequencer_param_base <REQ,RSP>
//
//! Extends class #uvm_sequencer_base with an API depending on specific
//! request (REQ) and response (RSP) types.
//----------------------------------------------------------------------

template <typename REQ = uvm_sequence_item, typename RSP = REQ>
class uvm_sequencer_param_base : public uvm_sequencer_base
{
 public:
  tlm::tlm_fifo<REQ> m_req_fifo;
  //tlm::tlm_analysis_fifo<REQ> m_req_fifo; // TODO add analysis fifo

  explicit uvm_sequencer_param_base( uvm_component_name name_ );
  virtual ~uvm_sequencer_param_base();

  void send_request(uvm_sequence_base* sequence_ptr,
                    uvm_sequence_item* seq_item,
                    bool rerandomize = false);

  REQ get_current_item() const;

  // Group: Requests

  // int get_num_reqs_sent();
  // void set_num_last_reqs(unsigned int max);
  // unsigned int get_num_last_reqs();
  // REQ last_req(unsigned int n = 0);

  // Group: Responses

  // uvm_analysis_export<RSP> rsp_export;
  // int get_num_rsps_received();
  // void set_num_last_rsps(unsigned int max);
  // unsigned int get_num_last_rsps();
  // RSP last_rsp(unsigned int n = 0);


  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////

  virtual const char* kind() const; // SystemC API

  virtual const std::string get_type_name() const;

  void put_response_base( const RSP& rsp );
  void m_last_req_push_front( REQ& item );
  void m_last_rsp_push_front( const RSP* item );

 private:
  // class data members
  unsigned int m_num_reqs_sent;
  unsigned int m_num_last_reqs;
  unsigned int m_num_last_rsps;
  unsigned int m_num_rsps_received;


  typedef std::list<REQ*> m_last_req_buffer_listT;
  typedef typename m_last_req_buffer_listT::iterator m_last_req_buffer_list_ItT;
  m_last_req_buffer_listT m_last_req_buffer;

  typedef std::list<const RSP*> m_last_rsp_buffer_listT;
  typedef typename m_last_rsp_buffer_listT::iterator m_last_rsp_buffer_list_ItT;
  m_last_rsp_buffer_listT m_last_rsp_buffer;
};

/////////////////////////////////////////////
// Class implementation starts here
/////////////////////////////////////////////

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
uvm_sequencer_param_base<REQ,RSP>::uvm_sequencer_param_base( uvm_component_name name_ )
  : uvm_sequencer_base( name_ ),
    m_req_fifo("m_req_fifo", UVM_MAX_SEQS) // set fifo depth here
{
  m_num_reqs_sent = 0;
  m_num_last_reqs = 1;
  m_num_last_rsps = 0;
  m_num_rsps_received = 0;

  m_last_req_buffer.clear();
  m_last_rsp_buffer.clear();
}

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
uvm_sequencer_param_base<REQ,RSP>::~uvm_sequencer_param_base()
{
  for (m_last_req_buffer_list_ItT
       it = m_last_req_buffer.begin();
       it != m_last_req_buffer.end();
       it++ )
    delete *it;

  for (m_last_rsp_buffer_list_ItT
       it = m_last_rsp_buffer.begin();
       it != m_last_rsp_buffer.end();
       it++ )
    delete *it;
}


//----------------------------------------------------------------------
// member function: send_request
//
//! The send_request function may only be called after a #wait_for_grant call.
//! This call will send the request item, \p seq_item, to the sequencer pointed to by
//! \p sequence_ptr. The sequencer will forward it to the driver. If \p rerandomize
//! is set, the item will be randomized before being sent to the driver.
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
void uvm_sequencer_param_base<REQ,RSP>::send_request( uvm_sequence_base* sequence_ptr,
                                                      uvm_sequence_item* seq_item,
                                                      bool rerandomize)
{
  REQ* param_tp;
  REQ param_t;

  if (sequence_ptr == NULL)
    uvm_report_fatal("SNDREQ", "Send request sequence_ptr is null", UVM_NONE);

  if (sequence_ptr->m_wait_for_grant_semaphore < 1)
    uvm_report_fatal("SNDREQ", "Send request called without wait_for_grant", UVM_NONE);

  sequence_ptr->m_wait_for_grant_semaphore--;

  param_tp = dynamic_cast<REQ*>(seq_item);

  if (param_tp != NULL)
  {
    param_t = *param_tp; // TODO workaround: dereference to get const REQ& for the TLM put. Alternative?

    if (rerandomize)
    {
      // TODO no randomization for UVM-SC yet
      // report error is dummy for now
      uvm_report_error("SEQR-RND", "Randomization not implemented and thus skipped", UVM_NONE);

      //if (!param_t->randomize())
      //  uvm_report_warning("SQRSNDREQ", "Failed to rerandomize sequence item in send_request");
    }

    if (param_t.get_transaction_id() == -1)
      param_t.set_transaction_id(sequence_ptr->m_next_transaction_id++);

    m_last_req_push_front(param_t);
  }
  else
    uvm_report_fatal(name(),"Send_request failed to cast sequence item", UVM_NONE);

  param_t.set_sequence_id(sequence_ptr->m_get_sqr_sequence_id(m_sequencer_id, 1)); //TODO no direct access to m_get_sqr_sequence_id

  seq_item->set_sequencer(this);

  if (!m_req_fifo.nb_put(param_t))
  {
    std::ostringstream str;
    str << "Concurrent calls to send_request() not supported. Check your driver for concurrent calls to get_next_item()";
    uvm_report_fatal(name(), str.str(), UVM_NONE);
  }

  m_num_reqs_sent++;

  // Grant any locks as soon as possible
  grant_queued_locks();
}

//----------------------------------------------------------------------
// member function: get_current_item
//
//! Returns the request_item currently being executed by the sequencer. If the
//! sequencer is not currently executing an item, this method will return NULL.
//!
//! The sequencer is executing an item from the time that get_next_item or peek
//! is called until the time that get or item_done is called.
//!
//! Note that a driver that only calls get() will never show a current item,
//! since the item is completed at the same time as it is requsted.
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
REQ uvm_sequencer_param_base<REQ,RSP>::get_current_item() const
{
  REQ req;
  if (!m_req_fifo.nb_peek(req))
    return NULL;
  return req;
}

////////////////////////////////////////////////////////////////////////
//////// Implementation-defined member functions start here ////////////
////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------
// member function: put_response_base
//
// Implementation-defined member function
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
void uvm_sequencer_param_base<REQ,RSP>::put_response_base(const RSP& rsp)
{
  uvm_sequence_base* sequence_ptr;

  m_last_rsp_push_front(&rsp);
  m_num_rsps_received++;

  // Check that set_id_info() was called
  if (rsp.get_sequence_id() == -1)
    uvm_report_fatal("SQRPUT", "Driver put a response with invalid sequence_id", UVM_NONE);

  sequence_ptr = m_find_sequence(rsp.get_sequence_id());

  if (sequence_ptr != NULL)
  {
    // If the response_handler is enabled for this sequence,
    // then call the response handler
    if ( sequence_ptr->get_use_response_handler() )
    {
      sequence_ptr->response_handler(&rsp);
      return;
    }
    sequence_ptr->put_response(rsp);
  }
  else
  {
    std::ostringstream str;
    str << "Dropping response for sequence '" << rsp.get_name() << "' (id= " << rsp.get_sequence_id() << "), since sequence is not found. Probable cause: sequence exited or has been killed.";
    uvm_report_info("Sequencer", str.str() );
  }

}

//----------------------------------------------------------------------
// member function: m_last_rsp_push_front
//
// Implementation-defined member function
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
void uvm_sequencer_param_base<REQ,RSP>::m_last_rsp_push_front(const RSP* item)
{
  if(!m_num_last_rsps)
    return;

  if(m_last_rsp_buffer.size() == m_num_last_rsps)
    m_last_rsp_buffer.pop_back();

  m_last_rsp_buffer.push_front(item);
}


//----------------------------------------------------------------------
// member function: m_last_req_push_front
//
// Implementation-defined member function
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
void uvm_sequencer_param_base<REQ,RSP>::m_last_req_push_front(REQ& item)
{
  if(!m_num_last_reqs)
    return;

  if(m_last_req_buffer.size() == m_num_last_reqs)
    m_last_req_buffer.pop_back();

  m_last_req_buffer.push_front(&item);
}

//----------------------------------------------------------------------
// member function: kind (virtual)
//
// SystemC API
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
const char* uvm_sequencer_param_base<REQ,RSP>::kind() const
{
  return "uvm::uvm_sequencer_param_base";
}

//----------------------------------------------------------------------
// member function: get_type_name (virtual)
//
// Implementation-defined member function
//----------------------------------------------------------------------

template <typename REQ, typename RSP>
const std::string uvm_sequencer_param_base<REQ,RSP>::get_type_name() const
{
  return std::string(this->kind());
}

} /* namespace uvm */

#endif /* UVM_SEQUENCER_PARAM_BASE_H_ */
