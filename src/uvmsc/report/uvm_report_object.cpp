//----------------------------------------------------------------------
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2012-2016 NXP B.V.
//   Copyright 2007-2010 Mentor Graphics Corporation
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

#include <systemc>

#include "uvmsc/base/uvm_object_globals.h"
#include "uvmsc/report/uvm_report_object.h"
#include "uvmsc/report/uvm_report_handler.h"
#include "uvmsc/report/uvm_report_message.h"

namespace uvm {

//----------------------------------------------------------------------------
// initialization of static data members
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// constructor
//
//! Creates a new report object with the given name.
//----------------------------------------------------------------------------

uvm_report_object::uvm_report_object( const std::string& name ) : uvm_object(name)
{
  // moved start of report handler to sepeate method
  // to enable passing of full name (this is not possible
  // during constructor initialization)
}

//----------------------------------------------------------------------
// Group: Reporting
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: uvm_report_enabled
//
// Returns the nearest uvm_report_object when called. From inside a
// uvm_component, the member function returns this.
//----------------------------------------------------------------------

uvm_report_object* uvm_report_object::uvm_get_report_object() const
{
  return const_cast<uvm_report_object*>(this); // FIXME no const_cast!
}

//----------------------------------------------------------------------
// member function: uvm_report_enabled
//
// Returns true if the configured verbosity for this severity/id is greater
// than ~verbosity~, else returns false.
//
// See also <get_report_verbosity_level> and the
// global version of <uvm_report_enabled>.
//----------------------------------------------------------------------

bool uvm_report_object::uvm_report_enabled( int verbosity,
                                            uvm_severity severity,
                                            const std::string& id ) const
{
  if (get_report_verbosity_level(severity, id) < verbosity )
    return false;
  else
    return true;
}

//----------------------------------------------------------------------
// member function: uvm_report
//
//----------------------------------------------------------------------

void uvm_report_object::uvm_report( uvm_severity severity,
                                    const std::string& id,
                                    const std::string& message,
                                    int verbosity,
                                    const std::string& filename,
                                    int line,
                                    const std::string& context_name,
                                    bool report_enabled_checked ) const
{
  uvm_report_message* l_report_message;

  if (verbosity == -1)
    verbosity = (severity == UVM_ERROR) ? UVM_LOW :
                (severity == UVM_FATAL) ? UVM_NONE : UVM_MEDIUM;

  if (report_enabled_checked == 0)
  {
    if (!uvm_report_enabled(verbosity, severity, id))
      return;
  }

  l_report_message = uvm_report_message::new_report_message();
  l_report_message->set_report_message(severity, id, message,
                                      verbosity, filename, line, context_name);

  uvm_process_report_message(l_report_message);
}

//----------------------------------------------------------------------
// member function: uvm_report_info
//
//! The member function #uvm_report_info shall issue an info message using
//! the current messages report object.
//----------------------------------------------------------------------

void uvm_report_object::uvm_report_info( const std::string& id,
                                         const std::string& message,
                                         int verbosity,
                                         const std::string& filename,
                                         int line,
                                         const std::string& context_name,
                                         bool report_enabled_checked ) const
{
  uvm_report( UVM_INFO, id, message, verbosity,
              filename, line, context_name, report_enabled_checked);
}

//----------------------------------------------------------------------
// member function: uvm_report_warning
//
//! The member function #uvm_report_warning shall issue a warning message using
//! the current messages report object.
//----------------------------------------------------------------------

void uvm_report_object::uvm_report_warning( const std::string& id,
                                            const std::string& message,
                                            int verbosity,
                                            const std::string& filename,
                                            int line,
                                            const std::string& context_name,
                                            bool report_enabled_checked ) const
{
  uvm_report( UVM_WARNING, id, message, verbosity,
              filename, line, context_name, report_enabled_checked);
}

//----------------------------------------------------------------------
// member function: uvm_report_error
//
//! The member function #uvm_report_error shall issue an error message using
//! the current messages report object.
//----------------------------------------------------------------------

void uvm_report_object::uvm_report_error( const std::string& id,
                                          const std::string& message,
                                          int verbosity,
                                          const std::string& filename,
                                          int line,
                                          const std::string& context_name,
                                          bool report_enabled_checked ) const
{
  uvm_report( UVM_ERROR, id, message, verbosity,
              filename, line, context_name, report_enabled_checked);
}

//----------------------------------------------------------------------
// member function: uvm_report_fatal
//
//! The member function #uvm_report_fatal shall issue a fatal message using
//! the current messages report object. This message shall bypass any message
//! catching callbacks.
//----------------------------------------------------------------------

void uvm_report_object::uvm_report_fatal( const std::string& id,
                                          const std::string& message,
                                          int verbosity,
                                          const std::string& filename,
                                          int line,
                                          const std::string& context_name,
                                          bool report_enabled_checked ) const
{
  uvm_report( UVM_FATAL, id, message, verbosity,
              filename, line, context_name, report_enabled_checked);
}

//----------------------------------------------------------------------
// member function: uvm_process_report_message (virtual)
//
// This member function takes a preformed uvm_report_message, populates it with
// the report object and passes it to the report handler for processing.
// It is expected to be checked for verbosity and populated.
//----------------------------------------------------------------------
void uvm_report_object::uvm_process_report_message( uvm_report_message* report_message ) const
{
  // TODO fix const
  uvm_report_object* obj = const_cast<uvm_report_object*>(this);
  report_message->set_report_object(obj);

  m_rh->process_report_message(report_message);
}

//--------------------------------------------------------------------------
// Group: Verbosity Configuration
//--------------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: get_report_verbosity_level
//
// Gets the verbosity level in effect for this object. Reports issued
// with verbosity greater than this will be filtered out. The severity
// and tag arguments check if the verbosity level has been modified for
// specific severity/tag combinations.
//----------------------------------------------------------------------

int uvm_report_object::get_report_verbosity_level( uvm_severity severity,
                                                   const std::string& id) const
{
  return m_rh->get_verbosity_level( severity, id );
}

//----------------------------------------------------------------------
// member function: get_report_max_verbosity_level
//----------------------------------------------------------------------

int uvm_report_object::get_report_max_verbosity_level() const
{
  return m_rh->m_max_verbosity_level;
}

//----------------------------------------------------------------------
// member function: set_report_verbosity_level
//
//! The member function #set_report_verbosity_level shall set the maximum
//! verbosity level for reports for this component. Any report from this
//! component whose verbosity exceeds this maximum will be ignored.
//----------------------------------------------------------------------

void uvm_report_object::set_report_verbosity_level( int verbosity_level )
{
  m_rh->set_verbosity_level(verbosity_level);
}

//----------------------------------------------------------------------
// member function: set_report_id_verbosity
//
//! The member function set_report_id_verbosity shall associate the
//! specified verbosity with reports of the given id. A verbosity
//! associated with a particular id takes precedence over a verbosity
//! associated with a severity.
//----------------------------------------------------------------------

void uvm_report_object::set_report_id_verbosity( const std::string& id, int verbosity )
{
  m_rh->set_id_verbosity(id, verbosity);
}

//----------------------------------------------------------------------
// member function: set_report_severity_id_verbosity
//
//! The member function set_report_severity_id_verbosity shall associate
//! the specified verbosity with reports of the given severity-id pair.
//! A verbosity associated with a particular severity-id pair takes
//! precedence over an verbosity associated with id, which take precedence
//! over an an verbosity associated with a severity.
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_id_verbosity( uvm_severity severity,
                                                          const std::string& id,
                                                          int verbosity )
{
  m_rh->set_severity_id_verbosity(severity, id, verbosity);
}

//----------------------------------------------------------------------
// Group: Action Configuration
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: get_report_action
//
//! Gets the action associated with reports having the given \p severity
//! and  \p id.
//----------------------------------------------------------------------

int uvm_report_object::get_report_action( uvm_severity severity,
                                          const std::string& id ) const
{
  return m_rh->get_action( severity, id );
}


//----------------------------------------------------------------------
// member function: set_report_severity_action
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_action( uvm_severity severity,
                                                    uvm_action action )
{
  m_rh->set_severity_action(severity, action);
}

//----------------------------------------------------------------------
// member function: set_report_id_action
//----------------------------------------------------------------------

void uvm_report_object::set_report_id_action( const std::string& id, uvm_action action)
{
  m_rh->set_id_action(id, action);
}

//----------------------------------------------------------------------
// member function: set_report_severity_id_action
//
//! This member function associates the specified \p action or actions with reports of the
//! given \p severity, \p id, or \p severity - \p id pair. An action associated with a
//! particular \p severity - \p id pair takes precedence over an action associated with
//! \p id, which takes precedence over an an action associated with a \p severity.
//!
//! The argument \p action can take the value UVM_NO_ACTION, or it can be a
//! bitwise OR of any combination of UVM_DISPLAY, UVM_LOG, UVM_COUNT,
//! UVM_STOP, UVM_EXIT, and UVM_CALL_HOOK.
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_id_action( uvm_severity severity,
                                                       const std::string& id,
                                                       uvm_action action )
{
  m_rh->set_severity_id_action(severity, id, action);
}


//--------------------------------------------------------------------------
// Group: File Configuration
//--------------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: get_report_file_handle
//
// Gets the file descriptor associated with reports having the given
// ~severity~ and ~id~.
//----------------------------------------------------------------------

//TODO returned int?
UVM_FILE uvm_report_object::get_report_file_handle( uvm_severity severity,
                                                    const std::string& id) const
{
  return m_rh->get_file_handle( severity, id );
}


//----------------------------------------------------------------------
// member function: set_report_default_file
//
//----------------------------------------------------------------------

void uvm_report_object::set_report_default_file ( UVM_FILE file )
{
  m_rh->set_default_file(file);
}


//----------------------------------------------------------------------
// member function: set_report_id_file
//
//----------------------------------------------------------------------

void uvm_report_object::set_report_id_file( const std::string& id,
                                            UVM_FILE file )
{
  m_rh->set_id_file(id, file);
}

//----------------------------------------------------------------------
// member function: set_report_severity_file
//
//----------------------------------------------------------------------
void uvm_report_object::set_report_severity_file( uvm_severity severity,
                                                  UVM_FILE file )
{
  m_rh->set_severity_file(severity, file);
}

//----------------------------------------------------------------------
// member function: set_report_severity_id_file
//
// These methods configure the report handler to direct some or all of its
// output to the given file descriptor. The ~file~ argument must be a
// multi-channel descriptor (mcd) or file id compatible with $fdisplay.
//
// A FILE descriptor can be associated with with reports of
// the given ~severity~, ~id~, or ~severity-id~ pair.  A FILE associated with
// a particular ~severity-id~ pair takes precedence over a FILE associated
// with ~id~, which take precedence over an a FILE associated with a
// ~severity~, which takes precedence over the default FILE descriptor.
//
// When a report is issued and its associated action has the UVM_LOG bit
// set, the report will be sent to its associated FILE descriptor.
// The user is responsible for opening and closing these files.
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_id_file( uvm_severity severity,
                                                     const std::string& id,
                                                     UVM_FILE file )
{
  m_rh->set_severity_id_file(severity, id, file);
}


//--------------------------------------------------------------------------
// Group: Override Configuration
//--------------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: set_report_severity_override
//
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_override( uvm_severity cur_severity,
                                                      uvm_severity new_severity)
{
  m_rh->set_severity_override(cur_severity, new_severity);
}

//----------------------------------------------------------------------
// member function: set_report_severity_id_override
//
//! This member function provides the ability to upgrade or downgrade a message in
//! terms of severity given \p severity and \p id.  An upgrade or downgrade for
//! a specific \p id takes precedence over an upgrade or downgrade associated
//! with a \p severity.
//----------------------------------------------------------------------

void uvm_report_object::set_report_severity_id_override( uvm_severity cur_severity,
                                                         const std::string& id,
                                                         uvm_severity new_severity)
{
  m_rh->set_severity_id_override(cur_severity, id, new_severity);
}


//----------------------------------------------------------------------
// Group: Report Handler Configuration
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// member function: set_report_handler
//
// Sets the report handler, overwriting the default instance. This allows
// more than one component to share the same report handler.
//----------------------------------------------------------------------

void uvm_report_object::set_report_handler( uvm_report_handler* handler )
{
  m_rh = handler;
}

//----------------------------------------------------------------------
// member function: get_report_handler
//
// Returns the underlying report handler to which most reporting tasks
// are delegated.
//----------------------------------------------------------------------

uvm_report_handler* uvm_report_object::get_report_handler() const
{
  return m_rh;
}

//----------------------------------------------------------------------
// member function: reset_report_handler
//
// Resets the underlying report handler to its default settings. This clears
// any settings made with the set_report_* methods (see below).
//----------------------------------------------------------------------

void uvm_report_object::reset_report_handler()
{
  m_rh->initialize();
}

//----------------------------------------------------------------------
// member function: start_report_handler
//
// Implementation defined
// Start the report handler
//----------------------------------------------------------------------

void uvm_report_object::start_report_handler(const std::string& name)
{
  m_rh = uvm_report_handler::type_id::create(name);
}




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////// Implementation-defined member functions start here ////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------------

uvm_report_object::~uvm_report_object()
{
}


/////////////////////

} // namespace uvm

