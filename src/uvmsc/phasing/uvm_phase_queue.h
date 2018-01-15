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

#ifndef UVM_PHASE_QUEUE_H_
#define UVM_PHASE_QUEUE_H_

#include <systemc>
#include <queue>

//////////////

namespace uvm {

//----------------------------------------------------------------------------
// CLASS: uvm_phase_queue
//
//! This queue provides processes to transfer and retrieve data in
//! a controlled manner. The queue can have either a bounded or
//! unbounded size. A bounded queue becomes full when it contains the
//! bounded number of elements. A process that attempts to place an element into
//! a full queue will be suspended until enough room becomes available in
//! the queue. Unbounded queues never suspend a thread in a send
//! operation. This base class defines everything about a phase: behavior,
//! state, and context.
//!
//! The queue follows the FIFO mechanics. This does not guarantee the order
//! in which processes arrive at the queue, only that their arrival order
//! shall be preserved by the queue.
//----------------------------------------------------------------------------

template <typename T = int>
class uvm_phase_queue
{
 public:
  explicit uvm_phase_queue( int bound = 0 );

  int num();                // The number of elements in the queue
  void put(T m);            // Places an element in the queue
  int try_put(T m);         // Attempts to place an element in the queue
  void get(T& m);           // Retrieves an element from the queue.
  int try_get(T& m);        // Attempts to retrieves an element from the
                            // queue without blocking
  void peek(T& m);          // Copies an element from the queue without
                            // removing the message from the queue
  void empty();             // Empty the queue

 private:
  std::queue<T> m_elements;

  unsigned int m_queue_size;
  sc_core::sc_event not_full_anymore;
  sc_core::sc_event for_content;
};

//----------------------------------------------------------------------------
// Constructor
//
//! If the bound argument is 0, then the queue is unbounded (the default) and
//! a put operation shall never block. If bound is nonzero, it represents the size
//! of the queue.
//! The bound shall be positive. Negative bounds are illegal and can result in
//! indeterminate behavior, but implementations can issue a warning.
//----------------------------------------------------------------------------

template <typename T>
uvm_phase_queue<T>::uvm_phase_queue( int bound )
{
  m_queue_size = bound;
}

//----------------------------------------------------------------------------
// member function: num
//
//! The member function num returns the number of elements currently in the
//! queue. The returned value should be used with care because it is valid
//! only until the next get or put is executed on the queue. These queue
//! operations can be from different processes from the one executing the
//! member function num. Therefore, the validity of the returned value depends
//! on the time that the other member functions start and finish.
//----------------------------------------------------------------------------

template <typename T>
int uvm_phase_queue<T>::num()
{
  return m_elements.size();
}

//----------------------------------------------------------------------------
// member function: put
//
//! The member function put stores a message in the queue in strict FIFO order.
//! If the queue was created with a bounded size, the process shall be
//! suspended until there is enough room in the queue.
//----------------------------------------------------------------------------

template <typename T>
void uvm_phase_queue<T>::put(T m)
{
  while (m_queue_size!=0 && m_elements.size() >= m_queue_size)
    sc_core::wait(not_full_anymore);

  m_elements.push(m);

  if (!sc_core::sc_is_running())
    for_content.notify(sc_core::SC_ZERO_TIME);
  else
    for_content.notify();
}

//----------------------------------------------------------------------------
// member function: try_put
//
//! The member function try_put stores an element in the queue in strict FIFO
//! order. This member function is meaningful only for bounded queues.
//! If the queue is not full, then the specified element is placed in the
//! queue and the function returns a positive integer. If the queue is
//! full, the member function returns 0.
//----------------------------------------------------------------------------

template <typename T>
int uvm_phase_queue<T>::try_put(T m)
{
  if (m_queue_size!=0 && m_elements.size() >= m_queue_size)
    return 0;

  m_elements.push(m);

  if (!sc_core::sc_is_running())
    for_content.notify(sc_core::SC_ZERO_TIME);
  else
    for_content.notify();

  return 1;
}

//----------------------------------------------------------------------------
// member function: get
//
//! The member function get retrieves one element from the queue, that is,
//! removes one message from the queue. If the queue is empty, then
//! the current process blocks until an element is placed in the queue.
//----------------------------------------------------------------------------

template <typename T>
void uvm_phase_queue<T>::get(T& m)
{
  while (m_elements.size() == 0)
    sc_core::wait(for_content);

  m = m_elements.front(); // get next oldest = front element
  m_elements.pop();       // and remove it

  if (!sc_core::sc_is_running())
    not_full_anymore.notify(sc_core::SC_ZERO_TIME);
  else
    not_full_anymore.notify();
}


//----------------------------------------------------------------------------
// member function: try_get
//
//! The member function try_get tries to retrieve one element from the queue.
//! If the queue is empty, then the method returns 0. If a message is available
//! the message is retrieved, and the method returns a positive integer.
//----------------------------------------------------------------------------

template <typename T>
int uvm_phase_queue<T>::try_get(T& m)
{
  if(m_elements.size() == 0)
    return 0;

  m = m_elements.front(); // get next oldest = front element
  m_elements.pop();       // and remove it

  if (!sc_core::sc_is_running())
    not_full_anymore.notify(sc_core::SC_ZERO_TIME);
  else
    not_full_anymore.notify();

  return 1;
}

//----------------------------------------------------------------------------
// member function: peek
//
//! The member function peek copies one element from the queue without
//! removing the element from the queue. If the queue is empty,
//! then the current process blocks until a message is placed in the queue.
//!
//! Calling the member function peek can also cause one element to unblock
//! more than one process. As long as an element remains in the queue,
//! any process blocked in either a peek or get operation shall become
//! unblocked.
//----------------------------------------------------------------------------

template <typename T>
void uvm_phase_queue<T>::peek(T& m)
{
  while (m_elements.size() == 0)
    sc_core::wait(for_content);

  m = m_elements.front(); // get next oldest = front element
}

//----------------------------------------------------------------------------
// member function: empty
//
//! The member function empty removes all remaining items from the queue.
//! The queue size becomes zero.
//----------------------------------------------------------------------------

template <typename T>
void uvm_phase_queue<T>::empty()
{
  while (m_elements.size() != 0)
    m_elements.pop();

  if (!sc_core::sc_is_running())
    for_content.notify(sc_core::SC_ZERO_TIME);
  else
    for_content.notify();
}

//////////////

} // namespace uvm

#endif /* UVM_PHASE_QUEUE_H_ */
