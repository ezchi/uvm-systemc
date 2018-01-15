//----------------------------------------------------------------------
//   Copyright 2011 Cypress Semiconductor
//   Copyright 2010 Mentor Graphics Corporation
//   Copyright 2012-2013 NXP B.V.
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
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

#ifndef UVM_RESOURCE_DB_H_
#define UVM_RESOURCE_DB_H_

#include <typeinfo>

#include "uvmsc/conf/uvm_resource.h"
#include "uvmsc/conf/uvm_resource_db_options.h"

namespace uvm {

 // forward class references

class uvm_resource_db_options;

//class uvm_cmdline_processor; // TODO command line interface

//----------------------------------------------------------------------
// class: uvm_resource_db<T>
//
//! The class uvm_resource_db provides a convenience interface for
//! the resources facility.  In many cases basic operations such as
//! creating and setting a resource or getting a resource could take
//! multiple lines of code using the interfaces in #uvm_resource_base or
//! #uvm_resource<T>.  The convenience layer in #uvm_resource_db
//! reduces many of those operations to a single line of code.
//----------------------------------------------------------------------

template <typename T = uvm_object*>
class uvm_resource_db
{
 public:

  //--------------------------------------------------------------------------
  // UVM Standard LRM API below
  //--------------------------------------------------------------------------

  static uvm_resource<T>* get_by_type( const std::string& scope );

  static uvm_resource<T>* get_by_name( const std::string& scope,
                                       const std::string& name,
                                       bool rpterr = true );

  static uvm_resource<T>* set_default( const std::string& scope,
                                       const std::string& name );

  static void set( const std::string& scope,
                   const std::string& name,
                   const T& val,
                   uvm_object* accessor = NULL );

  static void set_anonymous( const std::string& scope,
                             const T& val,
                             uvm_object* accessor = NULL );

  static void set_override( const std::string& scope,
                            const std::string& name,
                            const T& val,
                            uvm_object* accessor = NULL );

  static void set_override_type( const std::string& scope,
                                 const std::string& name,
                                 const T& val,
                                 uvm_object* accessor = NULL );

  static void set_override_name( const std::string& scope,
                                 const std::string& name,
                                 const T& val,
                                 uvm_object* accessor = NULL );

  static bool read_by_name( const std::string& scope,
                            const std::string& name,
                            T& val,
                            uvm_object* accessor = NULL );

  static bool read_by_type( const std::string& scope,
                            T& val,
                            uvm_object* accessor = NULL );

  static bool write_by_name( const std::string& scope,
                             const std::string& name,
                             const T& val,
                             uvm_object* accessor = NULL );

  static bool write_by_type( const std::string& scope,
                             const T& val,
                             uvm_object* accessor = NULL );

  static void dump();

  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////

 protected:
  static void m_show_msg( const std::string& id,
                          const std::string& rtype,
                          const std::string& action,
                          const std::string& scope,
                          const std::string& name,
                          uvm_object* accessor,
                          uvm_resource<T>* rsrc );

 private:
  // All of the functions in this class are static, so there is no need
  // to instantiate this class ever.  To make sure that the constructor
  // is never called we make it private
  uvm_resource_db();
  virtual ~uvm_resource_db(){};

};


//----------------------------------------------------------------------
// member function: get_by_type (static)
//
//! Get a resource by type.  The type is specified in the database
//! class parameter so the only argument to this function is the
//! \p scope.
//----------------------------------------------------------------------

template <typename T>
uvm_resource<T>* uvm_resource_db<T>::get_by_type( const std::string& scope )
{
  return uvm_resource<T>::get_by_type( scope, uvm_resource<T>::get_type() );
}

//----------------------------------------------------------------------
// member function: get_by_name (static)
//
//! Imports a resource by \p name. The first argument is the \p name of the
//! resource to be retrieved and the second argument is the current
//! \p scope. The \p rpterr flag indicates whether or not to generate
// a warning if no matching resource is found.
//----------------------------------------------------------------------

template <typename T>
uvm_resource<T>* uvm_resource_db<T>::get_by_name( const std::string& scope,
                                                  const std::string& name,
                                                  bool rpterr )
{
  return uvm_resource<T>::get_by_name(scope, name, rpterr);
}

//----------------------------------------------------------------------
// member function: set_default (static)
//
//! Add a new item into the resources database. The item will not be
//! written to so it will have its default value. The resource is
//! created using \p name and \p scope as the lookup parameters.
//----------------------------------------------------------------------

template <typename T>
uvm_resource<T>* uvm_resource_db<T>::set_default( const std::string& scope,
                                                  const std::string& name )
{
  uvm_resource<T>* r;

  r = new uvm_resource<T>(name, scope);
  r->set();
  return r;
}

//----------------------------------------------------------------------
// member function: set (static)
//
//! Create a new resource, write a \p val to it, and set it into the
//! database using \p name and \p scope as the lookup parameters. The
//! \p accessor is used for auditting.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::set( const std::string& scope,
                              const std::string& name,
                              const T& val,
                              uvm_object* accessor )
{
  uvm_resource<T>* rsrc = new uvm_resource<T>(name, scope);
  rsrc->write(val, accessor);
  rsrc->set();

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/SET", "Resource", "set", scope, name, accessor, rsrc);

}

//----------------------------------------------------------------------
// member function: set_anonymous (static)
//
//! Create a new resource, write a \p val to it, and set it into the
//! database.  The resource has no name and therefore will not be
//! entered into the name map. But is does have a \p scope for lookup
//! purposes. The \p accessor is used for auditting.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::set_anonymous( const std::string& scope,
                                        const T& val,
                                        uvm_object* accessor )
{
  uvm_resource<T>* rsrc = new uvm_resource<T>("", scope);
  rsrc->write(val, accessor);
  rsrc->set();

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/SETANON", "Resource", "set", scope, "", accessor, rsrc);

}

//----------------------------------------------------------------------
// member function set_override (static)
//
//! Create a new resource, write \p val to it, and set it into the
//! database. Set it at the beginning of the queue in the type map and
//! the name map so that it will be (currently) the highest priority
//! resource with the specified name and type.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::set_override( const std::string& scope,
                                       const std::string& name,
                                       const T& val,
                                       uvm_object* accessor )
{
  uvm_resource<T>* rsrc = new uvm_resource<T>(name, scope);
  rsrc->write(val, accessor);
  rsrc->set_override();

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/SETOVRD", "Resource", "set", scope, name, accessor, rsrc);
}

//----------------------------------------------------------------------
// member function set_override_type (static)
//
//! Create a new resource, write \p val to it, and set it into the
//! database.  Set it at the beginning of the queue in the type map so
//! that it will be (currently) the highest priority resource with the
//! specified type. It will be normal priority (i.e. at the end of the
//! queue) in the name map.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::set_override_type( const std::string& scope,
                                            const std::string& name,
                                            const T& val,
                                            uvm_object* accessor )
{
  uvm_resource<T>* rsrc = new uvm_resource<T>(name, scope);
  rsrc->write(val, accessor);
  rsrc->set_override(uvm_resource_types::TYPE_OVERRIDE);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/SETOVRDTYP","Resource", "set", scope, name, accessor, rsrc);

}

//----------------------------------------------------------------------
// member function set_override_name (static)
//
//! Create a new resource, write \p val to it, and set it into the
//! database.  Set it at the beginning of the queue in the name map so
//! that it will be (currently) the highest priority resource with the
//! specified name. It will be normal priority (i.e. at the end of the
//! queue) in the type map.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::set_override_name( const std::string& scope,
                                            const std::string& name,
                                            const T& val,
                                            uvm_object* accessor )
{
  uvm_resource<T>* rsrc = new uvm_resource<T>(name, scope);
  rsrc->write(val, accessor);
  rsrc->set_override(uvm_resource_types::NAME_OVERRIDE);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/SETOVRDNAM","Resource", "set", scope, name, accessor, rsrc);

}

//----------------------------------------------------------------------
// member function: read_by_name (static)
//
//! locate a resource by \p name and \p scope and read its value. The value
//! is returned through the output argument \p val. The return value is a bit
//! that indicates whether or not the read was successful. The \p accessor
//! is used for auditting.
//----------------------------------------------------------------------

template <typename T>
bool uvm_resource_db<T>::read_by_name( const std::string& scope,
                                       const std::string& name,
                                       T& val,
                                       uvm_object* accessor )
{
  uvm_resource<T>* rsrc = get_by_name(scope, name);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/RDBYNAM", "Resource", "read", scope, name, accessor, rsrc);

  if(rsrc == NULL)
    return false;

  val = rsrc->read(accessor);

  return true;
}

//----------------------------------------------------------------------
// member function: read_by_type (static)
//
//! Read a value by type.  The value is returned through the output
//! argument \p val.  The \p scope is used for the lookup. The return
//! value is a bit that indicates whether or not the read is successful.
//! The \p accessor is used for auditting.
//----------------------------------------------------------------------

template <typename T>
bool uvm_resource_db<T>::read_by_type( const std::string& scope,
                                       T& val,
                                       uvm_object* accessor )
{
  uvm_resource<T>* rsrc = get_by_type(scope);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/RDBYTYP", "Resource", "read", scope, "", accessor, rsrc);

  if(rsrc == NULL)
    return false;

  val = rsrc->read(accessor);
  return true;
}

//----------------------------------------------------------------------
// member function: write_by_name (static)
//
//! Write a \p val into the resources database. First, look up the
//! resource by \p name and \p scope.  If it is not located then add a new
//! resource to the database and then write its value.
//!
//! Because the \p scope is matched to a resource which may be a
//! regular expression, and consequently may target other scopes beyond
//! the \p scope argument. Care must be taken with this function. If
//! a #get_by_name match is found for \p name and \p scope then \p val
//! will be written to that matching resource and thus may impact
//! other scopes which also match the resource.
//----------------------------------------------------------------------

template <typename T>
bool uvm_resource_db<T>::write_by_name( const std::string& scope,
                                        const std::string& name,
                                        const T& val,
                                        uvm_object* accessor )
{
  uvm_resource<T>* rsrc = get_by_name(scope, name);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/WR", "Resource", "written", scope, name, accessor, rsrc);

  if(rsrc == NULL)
    return false;

  rsrc->write(val, accessor);

  return true;
}

//----------------------------------------------------------------------
// member function: write_by_type (static)
//
//! Write a \p val into the resources database. First, look up the
//! resource by type.  If it is not located then add a new resource to
//! the database and then write its value.
//!
//! Because the \p scope is matched to a resource which may be a
//! regular expression, and consequently may target other scopes beyond
//! the \p scope argument. Care must be taken with this function. If
//! a #get_by_name match is found for \p name and \p scope then \p val
//! will be written to that matching resource and thus may impact
//! other scopes which also match the resource.
//----------------------------------------------------------------------

template <typename T>
bool uvm_resource_db<T>::write_by_type( const std::string& scope,
                                        const T& val,
                                        uvm_object* accessor )
{
  uvm_resource<T>* rsrc = get_by_type(scope);

  if(uvm_resource_db_options::is_tracing())
    m_show_msg("RSRCDB/WRTYP", "Resource", "written", scope, "", accessor, rsrc);

  if(rsrc == NULL)
    return false;

  rsrc->write(val, accessor);

  return true;
}

//----------------------------------------------------------------------
// member function: dump (static)
//
//! Dump all the resources in the resource pool. This is useful for
//! debugging purposes.  This function does not use the parameter T, so
//! it will dump the same thing -- the entire database -- no matter the
//! value of the parameter.
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::dump()
{
  //TODO dump
  uvm_resource_pool* rp = uvm_resource_pool::get();
  //m_uvm_resource_default_converters::do_register();
  rp->dump();
}


//----------------------------------------------------------------------
// member function: show_msg (static)
//
//! Implementation defined
//! Internal helper function to print resource accesses
//----------------------------------------------------------------------

template <typename T>
void uvm_resource_db<T>::m_show_msg( const std::string& id,
                                     const std::string& rtype,
                                     const std::string& action,
                                     const std::string& scope,
                                     const std::string& name,
                                     uvm_object* accessor,
                                     uvm_resource<T>* rsrc)
 {
   std::string type_name = (std::string)typeid(T).name();

   std::ostringstream msg;
   // format was "%s '%s%s' (type %s) %s by %s = %s"

   msg << "'"
       << rtype
       << scope
       << ( (name.empty()) ? "" : "." )
       << name
       << "' (type "
       << type_name
       << ") "
       << action
       << " by "
       << ( ( accessor == NULL ) ? "NULL (accessor not set)" : accessor->get_full_name() )
       << " = "
       << ( ( rsrc==NULL ) ? "NULL (failed lookup)" : rsrc->convert2string() );

   UVM_INFO(id, msg.str(), UVM_LOW);
}


} // namespace uvm

#endif // UVM_RESOURCE_DB_H_
