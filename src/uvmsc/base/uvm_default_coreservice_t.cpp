//----------------------------------------------------------------------
//   Copyright 2013 Cadence Design Inc
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

#include "uvmsc/base/uvm_root.h"
#include "uvmsc/base/uvm_component.h"
#include "uvmsc/factory/uvm_factory.h"
#include "uvmsc/factory/uvm_default_factory.h"
#include "uvmsc/base/uvm_default_coreservice_t.h"
#include "uvmsc/report/uvm_report_server.h"
#include "uvmsc/report/uvm_default_report_server.h"

namespace uvm {

//----------------------------------------------------------------------------
// member function: get_factory (virtual)
//
// Returns the currently enabled uvm factory.
// When no factory has been set before, instantiates a uvm_default_factory
//----------------------------------------------------------------------------

uvm_factory* uvm_default_coreservice_t::get_factory() const
{
  if(factory == NULL)
  {
    uvm_default_factory* f = new uvm_default_factory();
    factory = f;
  }
  return factory;
}

//----------------------------------------------------------------------------
// member function: set_factory (virtual)
//
// Sets the current uvm factory.
// Please note: it is up to the user to preserve the contents of the original
// factory or delegate calls to the original factory
//----------------------------------------------------------------------------

void uvm_default_coreservice_t::set_factory( uvm_factory* f )
{
  factory = f;
}

//----------------------------------------------------------------------------
// member function: get_default_tr_database (virtual)
//
// returns the current default record database
//
// If no default record database has been set before this method
// is called, returns an instance of <uvm_text_tr_database>
//----------------------------------------------------------------------------

/* TODO TR database
uvm_tr_database* uvm_default_coreservice_t::get_default_tr_database() const
{
  if (tr_database == NULL)
  {
    //   process p = process::self();
    uvm_text_tr_database* tx_db;
    std::string s;

    //if(p != NULL)
    //  s = p.get_randstate();

    tx_db = new uvm_tr_database("default_tr_database");
    tr_database = tx_db;

    //if(p != null)
    //  p.set_randstate(s);
  }
  return tr_database;
}

//----------------------------------------------------------------------------
// member function: set_default_tr_database (virtual)
//
// Sets the current default record database to ~db~
//----------------------------------------------------------------------------

void uvm_default_coreservice_t::set_default_tr_database( uvm_tr_database* db )
{
  tr_database = db;
}
*/

//----------------------------------------------------------------------------
// member function: get_report_server (virtual)
//
// returns the current global report_server
// if no report server has been set before, returns an instance of
// uvm_default_report_server
//----------------------------------------------------------------------------

uvm_report_server* uvm_default_coreservice_t::get_report_server() const
{
  if(report_server == NULL)
  {
    uvm_default_report_server* f = new uvm_default_report_server();
    report_server = f;
  }
  return report_server;
}

//----------------------------------------------------------------------------
// member function: set_report_server (virtual)
//
// sets the central report server to ~server~
//----------------------------------------------------------------------------

void uvm_default_coreservice_t::set_report_server( uvm_report_server* server )
{
  report_server = server;
}

//----------------------------------------------------------------------------
// member function: get_root (virtual)
//----------------------------------------------------------------------------

uvm_root* uvm_default_coreservice_t::get_root() const
{
  return uvm_root::m_uvm_get_root();
}

//----------------------------------------------------------------------------
// member function: set_component_visitor (virtual)
//
// sets the component visitor to ~v~
// (this visitor is being used for the traversal at end_of_elaboration_phase
// for instance for name checking)
//----------------------------------------------------------------------------

/* TODO uvm_visitor
void uvm_default_coreservice_t::set_component_visitor(uvm_visitor<uvm_component> v) const
{
  m_visitor=v;
}
*/

//----------------------------------------------------------------------------
// member function: get_component_visitor (virtual)
//
// retrieves the current component visitor
// if unset(or ~null~) returns a <uvm_component_name_check_visitor> instance
//----------------------------------------------------------------------------

/* TODO uvm_visitor
uvm_visitor<uvm_component> uvm_default_coreservice_t::get_component_visitor() const
{
  if(m_visitor == NULL)
  {
    uvm_component_name_check_visitor* v = new uvm_component_name_check_visitor("name-check-visitor");
    m_visitor=v;
  }
  return m_visitor;
}

*/
} // namespace uvm


