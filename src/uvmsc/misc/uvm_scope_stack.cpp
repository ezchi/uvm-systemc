//----------------------------------------------------------------------
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2012-2013 NXP B.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010 Synopsys, Inc.
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

#include <sstream>
#include <systemc>

#include "uvmsc/misc/uvm_scope_stack.h"

//////////////

namespace uvm {

//----------------------------------------------------------------------------
// Class: uvm_scope_stack - implementation
//----------------------------------------------------------------------------

uvm_scope_stack::uvm_scope_stack()
{}

uvm_scope_stack::~uvm_scope_stack()
{}

int uvm_scope_stack::depth() const
{
  return m_stack.size();
}

std::string uvm_scope_stack::get() const
{
  std::string v;
  if(m_stack.size() == 0)
    return m_arg;

  std::string g = m_stack[0];

  for( unsigned int i = 1; i < m_stack.size(); ++i)
  {
    v = m_stack[i];

    if( !v.empty() && (v[0] == '[' || v[0] == '(' || v[0] == '{'))
      g = g+v;
    else
      g = g+"."+v;
  }

  if( !m_arg.empty() )
  {
    if( !g.empty() )
      g = g + "." + m_arg;
    else
      g = m_arg;
  }

  return g;
}

std::string uvm_scope_stack::get_arg() const
{
  return m_arg;
}

void uvm_scope_stack::set( const std::string& s )
{
  m_stack.clear();

  m_stack.push_back(s);
  m_arg = "";
}

void uvm_scope_stack::down( const std::string& s )
{
  m_stack.push_back(s);
  m_arg = "";
}

void uvm_scope_stack::down_element( int element )
{
  std::stringstream str;
  str << "[" << element << "]";
  m_stack.push_back(str.str());
  m_arg = "";
}

void uvm_scope_stack::up_element()
{
  std::string s;
  if(!m_stack.size())
    return;

  s = m_stack.back();
  m_stack.pop_back();
  if( !s.empty() && s[0] != '[' )
  {
    m_stack.push_back(s);
  }

}

void uvm_scope_stack::up( const char* separator  )
{
  bool found = false;
  std::string s;

  while(m_stack.size() && !found )
  {
    s = m_stack.back(); // get last element
    m_stack.pop_back(); // and remove it

    if( *separator == '.' )
    {
      if (s.empty() || (s[0] != '[' && s[0] != '(' && s[0] != '{') )
        found = true;
    }
    else
    {
      if( !s.empty() && s[0] == *separator )
        found = true;
    }
  }
  m_arg = "";
}

 void uvm_scope_stack::set_arg( const std::string& arg )
 {
   if(arg.empty())
     return;

   m_arg = arg;
 }

void uvm_scope_stack::set_arg_element( const std::string& arg, int ele )
{
  std::ostringstream str;
  str << ele;
  m_arg = arg + "[" + str.str() + "]";
}


void uvm_scope_stack::unset_arg( const std::string& arg )
{
  if( arg == m_arg )
    m_arg = "";
}

} // namespace uvm
