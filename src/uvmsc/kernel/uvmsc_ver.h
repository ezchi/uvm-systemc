#pragma once

#include <string>

namespace uvm {

  extern UVM_API const char* uvm_copyright();
  extern UVM_API const char* uvm_release();
  extern UVM_API const char* uvm_version();

  extern UVM_API const unsigned int uvm_version_major;
  extern UVM_API const unsigned int uvm_version_minor;
  extern UVM_API const unsigned int uvm_version_patch;

  extern UVM_API const std::string  uvm_version_originator;
  extern UVM_API const std::string  uvm_version_release_date;
  extern UVM_API const std::string  uvm_version_prerelease;
  extern UVM_API const bool         uvm_is_prerelease;
  extern UVM_API const std::string  uvm_version_string;
  extern UVM_API const std::string  uvm_copyright_string;

#define UVMSC_1_0_BETA1

#define UVMSC_VERSION       20171208
#define UVMSC_VERSION_ORIGINATOR "Accellera"
#define UVMSC_VERSION_MAJOR      1
#define UVMSC_VERSION_MINOR      0
#define UVMSC_VERSION_PATCH      "BETA1"
#define UVMSC_IS_PRERELEASE      1

  // compliancy with IEEE 1666-2011 (see 8.6.5)
  // #define IEEE_1666_SYSTEMC     201101L

#define UVMSC_COPYRIGHT                             \
  "Copyright (c) 1996-2017 by all Contributors,\n"  \
  "ALL RIGHTS RESERVED\n"


// #define SC_VERSION_RELEASE_DATE                 \
//   UVMSC_STRINGIFY_HELPER_( UVMSC_VERSION )

// #if ( UVMSC_IS_PRERELEASE == 1 )
// #  define UVMSC_VERSION_PRERELEASE "pub_rev"
// #  define UVMSC_VERSION                                                 \
//   //     UVMSC_STRINGIFY_HELPER_( UVMSC_VERSION_MAJOR.UVMSC_VERSION_MINOR.UVMSC_VERSION_PATCH ) \
//   //     "_" UVMSC_VERSION_PRERELEASE "_" SC_VERSION_RELEASE_DATE       \
//   //     "-" UVMSC_VERSION_ORIGINATOR
// #else
// #  define UVMSC_VERSION_PRERELEASE "" // nothing
// #  define UVMSC_VERSION                                                 \
//   //     UVMSC_STRINGIFY_HELPER_( UVMSC_VERSION_MAJOR.UVMSC_VERSION_MINOR.UVMSC_VERSION_PATCH ) \
//   //     "-" UVMSC_VERSION_ORIGINATOR
// #endif

  // // THIS CLASS AND STATIC INSTANCE BELOW DETECTS BAD REV OBJECTS AT LINK TIME
  // //
  // // Each source file which includes this file for the current SystemC version
  // // will have a static instance of the class sc_api_version_XXX defined
  // // in it. That object instance will cause the constructor below
  // // to be invoked. If the version of the SystemC being linked against
  // // does not contain the constructor below a linkage error will occur.
  // //
  // // The static API check includes the SystemC version numbers as well as
  // // the underlying C++ standard version (SC_CPLUSPLUS).

  // #define SC_API_VERSION_STRING \
  //       SC_CONCAT_UNDERSCORE_( sc_api_version, \
  //       SC_CONCAT_UNDERSCORE_( UVMSC_VERSION_MAJOR, \
  //       SC_CONCAT_UNDERSCORE_( UVMSC_VERSION_MINOR, \
  //       SC_CONCAT_UNDERSCORE_( UVMSC_VERSION_PATCH, \
  //       SC_CONCAT_HELPER_( cxx, SC_CPLUSPLUS ) \
  //   ) ) ) )

  // // explicitly avoid macro expansion
  // #define SC_API_DEFINED_( Symbol ) \
  //   Symbol ## _DEFINED_
  // #define SC_API_UNDEFINED_( Symbol ) \
  //   Symbol ## _UNDEFINED_

  // // Some preprocessor switches need to be consistent between the application
  // // and the library (e.g. if sizes of classes are affected or other parts of
  // // the ABI are affected).  (Some of) these are checked here at link-time as
  // // well, by setting template parameters to sc_api_version_XXX, while only
  // // one variant is defined in sc_ver.cpp.

  // #if 0 // don't enforce check of DEBUG_SYSTEMC for now
  // // DEBUG_SYSTEMC
  // #if defined( DEBUG_SYSTEMC )
  // # define DEBUG_SYSTEMC_CHECK_ \
  //     SC_CONFIG_DEFINED_(DEBUG_SYSTEMC)
  // #else
  // # define DEBUG_SYSTEMC_CHECK_ \
  //     SC_CONFIG_UNDEFINED_(DEBUG_SYSTEMC)
  // #endif
  // extern const int DEBUG_SYSTEMC_CHECK_;
  // #endif

  // // SC_DISABLE_VIRTUAL_BIND
  // #if defined( SC_DISABLE_VIRTUAL_BIND )
  // # define SC_DISABLE_VIRTUAL_BIND_CHECK_ \
  //     SC_API_DEFINED_(SC_DISABLE_VIRTUAL_BIND)
  // #else
  // # define SC_DISABLE_VIRTUAL_BIND_CHECK_ \
  //     SC_API_UNDEFINED_(SC_DISABLE_VIRTUAL_BIND)
  // #endif
  // extern const int SC_DISABLE_VIRTUAL_BIND_CHECK_;

  // // Some preprocessor switches need to be consistent between different
  // // translation units of an application.  Those can't be easily checked
  // // during link-time.  Instead, perform a check during run-time by
  // // passing the value to the constructor of the api_version_check object.

  // // Note: Template and constructor parameters are not passed as default
  // //       values to avoid ODR violations in the check itself.

  // template // use pointers for more verbose error messages
  // <
  // //  const int * DebugSystemC,
  //   const int * DisableVirtualBind
  // >
  // struct SC_API_VERSION_STRING
  // {
  //   SC_API_VERSION_STRING
  //     (
  //        // SC_DEFAULT_WRITER_POLICY
  //        sc_writer_policy default_writer_policy
  //     );
  // };

  // #if !defined(SC_BUILD)
  // // import explicitly instantiated template
  // SC_TPLEXTERN_ template struct SC_API SC_API_VERSION_STRING
  // <
  //   &SC_DISABLE_VIRTUAL_BIND_CHECK_
  // >;

  // #if !defined(SC_DISABLE_API_VERSION_CHECK)
  // static
  // SC_API_VERSION_STRING
  // <
  // //  & DEBUG_SYSTEMC_CHECK_,
  //   & SC_DISABLE_VIRTUAL_BIND_CHECK_
  // >
  // api_version_check
  // (
  //   SC_DEFAULT_WRITER_POLICY
  // );
  // #endif // SC_DISABLE_API_VERSION_CHECK
  // #endif // SC_BUILD

    } // namespace uvm
