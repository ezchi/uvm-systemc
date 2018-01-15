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

#ifndef UVM_COPY_MAP_H_
#define UVM_COPY_MAP_H_

//////////////

namespace uvm {

//------------------------------------------------------------------------------
// CLASS: uvm_copy_map
//
//! Internal class used to map rhs to lhs so when a cycle is found in the rhs,
//! the correct lhs object can be bound to it.
//------------------------------------------------------------------------------

class uvm_copy_map
{
 public:

  void set(uvm_object* key, uvm_object* obj)
  {
    m_map[key] = obj;
  }

  uvm_object* get(uvm_object* key)
  {
    if (m_map.find(key) != m_map.end())
       return m_map[key];
    return NULL;
  }

  void clear()
  {
    m_map.clear();
  }

  void erase(uvm_object* v) // was delete, but this a reserved word in C++
  {
    m_map.erase(v);
  }

 private:
  std::map<uvm_object*,uvm_object*> m_map;

}; // class uvm_copy_map

} // namespace uvm

#endif /* UVM_COPY_MAP_H_ */
