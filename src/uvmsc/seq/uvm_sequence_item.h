//----------------------------------------------------------------------
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2010 Cadence Design Systems, Inc.
//   Copyright 2010 Synopsys, Inc.
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

#ifndef UVM_SEQUENCE_ITEM_H_
#define UVM_SEQUENCE_ITEM_H_

#include "uvmsc/base/uvm_transaction.h"

namespace uvm {

// forward declaration of necessary classes.
class uvm_sequence_base;
class uvm_sequencer_base;

//------------------------------------------------------------------------------
// CLASS: uvm_sequence_item
//
//! The base class uvm_sequence_item is for user-defined sequence items and also the base class for
//! the #uvm_sequence class. The class #uvm_sequence_item provides the basic
//! functionality for objects, both sequence items and sequences, to operate in
//! the sequence mechanism.
//------------------------------------------------------------------------------ 

class uvm_sequence_item: public uvm_transaction
{
  friend class uvm_sequencer_base;
  template <typename REQ, typename RSP> friend class uvm_sequencer_param_base;
  template <typename REQ, typename RSP> friend class uvm_sequencer;

 public:
  //--------------------------------------------------------------------------
  // Constructors and destructor
  //--------------------------------------------------------------------------

  uvm_sequence_item();
  explicit uvm_sequence_item( uvm_object_name name_ );

  virtual ~uvm_sequence_item();

  //--------------------------------------------------------------------------
  // UVM Standard LRM API below
  //--------------------------------------------------------------------------

  void set_item_context( uvm_sequence_base* parent_seq,
                         uvm_sequencer_base* sequencer = NULL);

  void set_use_sequence_info(bool value);

  bool get_use_sequence_info() const;

  void set_id_info(uvm_sequence_item& item);

  virtual void set_sequencer(uvm_sequencer_base* sequencer);

  uvm_sequencer_base* get_sequencer() const;

  void set_parent_sequence(uvm_sequence_base* parent);

  uvm_sequence_base* get_parent_sequence() const;

  void set_depth(int value);

  int get_depth() const;

  virtual bool is_item() const;

  const std::string get_root_sequence_name() const;

  const uvm_sequence_base* get_root_sequence() const;

  const std::string get_sequence_path() const;

  //--------------------------------------------------------------------------
  // Recording interface
  //--------------------------------------------------------------------------

  // not implemented yet

  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////

  virtual const std::string get_type_name() const { return "uvm::uvm_sequence_item"; }

  virtual void do_print( const uvm_printer& printer ) const;

protected:

  int get_sequence_id() const; // moved to private, see LRM text

  void set_sequence_id(int id);

 private:

  virtual void m_set_p_sequencer();

  // member variables below

  bool print_sequence_info;

 protected:
  uvm_sequence_base* m_parent_sequence;

  uvm_sequencer_base* m_sequencer;

 private:
  bool m_use_sequence_info;
  int m_sequence_id;
  mutable int m_depth;

};

/////////////////////////////////////////////
/////////////////////////////////////////////

} /* namespace uvm */

#endif /* UVM_SEQUENCE_ITEM_H_ */
