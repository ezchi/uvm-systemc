cmake_minimum_required (VERSION 3.1)
cmake_policy(SET CMP0001 NEW)

project (uvm-systemc CXX C)

set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD} CACHE STRING
  "C++ standard to build all targets. Supported values are 98, 11, and 14.")
set (CMAKE_CXX_STANDARD_REQUIRED ${SystemC_CXX_STANDARD_REQUIRED} CACHE BOOL
    "The with CMAKE_CXX_STANDARD selected C++ standard is a requirement.")

set(UVM_VERSION_FILE "${PROJECT_SOURCE_DIR}/src/uvmsc/base/uvm_version.h")
if(EXISTS ${UVM_VERSION_FILE})
    file(READ ${UVM_VERSION_FILE} UVM_VERSION_FILE_CONTENT)
    string(REGEX MATCH "UVM_VERSION[ \t]+\"([0-9]+)\\.([0-9]+)-([a-z0-9]+\)\"" UVM_VERSION ${UVM_VERSION_FILE_CONTENT})
    string(REGEX MATCH "([0-9]+)([-.a-z0-9]+)" UVM_VERSION ${UVM_VERSION})
    string(REGEX MATCH "UVM_RELEASE_DATE[ \t]+\"([0-9-]+)\"" UVM_RELEASE_DATE ${UVM_VERSION_FILE_CONTENT})
    string(REGEX MATCH "([0-9-]+)" UVM_RELEASE_DATE ${UVM_RELEASE_DATE})
    message("UVM_RELEASE_DATE: " ${UVM_RELEASE_DATE})
else(EXISTS ${UVM_VERSION_FILE})
    message (FATAL_ERROR "Unable to read UVM-SystemC version file")
endif(EXISTS ${UVM_VERSION_FILE})

###############################################################################
# Build options
###############################################################################

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: empty, Debug, Release, RelWithDebInfo, MinSizeRel."
        FORCE)
endif (NOT CMAKE_BUILD_TYPE)

mark_as_advanced (CMAKE_CXX_STANDARD_REQUIRED)

if (NOT (WIN32 OR CYGWIN))
    option (BUILD_SHARED_LIBS "Build shared libraries." ON)
else (NOT (WIN32 OR CYGWIN))
    option (BUILD_SHARED_LIBS "Build shared libraries." OFF)
endif (NOT (WIN32 OR CYGWIN))
if (BUILD_SHARED_LIBS AND (WIN32 OR CYGWIN))
    message (WARNING "The compilation of UVM-SystemC as a DLL on Windows is currently not supported!")
    set (BUILD_SHARED_LIBS CACHE BOOL "Build shared libraries." OFF FORCE)
endif (BUILD_SHARED_LIBS AND (WIN32 OR CYGWIN))

option (BUILD_SOURCE_DOCUMENTATION "Build source documentation with Doxygen." OFF)

option (DISABLE_COPYRIGHT_MESSAGE "Do not print the copyright message when starting the application." OFF)

option (INSTALL_TO_LIB_BUILD_TYPE_DIR
    "Install the libraries to lib-${CMAKE_BUILD_TYPE} to enable parallel installation of the different build variants. (default: OFF)"
    OFF)

if (NOT INSTALL_TO_LIB_BUILD_TYPE_DIR)
    option (INSTALL_TO_LIB_TARGET_ARCH_DIR "Install the libraries to lib-<target-arch> to facilitate linking applications, which build systems assume to find UVM-SystemC in lib-<target-arch>. (default: OFF)" OFF)
else (NOT INSTALL_TO_LIB_BUILD_TYPE_DIR)
    unset (INSTALL_TO_LIB_TARGET_ARCH_DIR CACHE)
endif (NOT INSTALL_TO_LIB_BUILD_TYPE_DIR)

if (CMAKE_HOST_UNIX AND NOT INSTALL_TO_LIB_TARGET_ARCH_DIR)
    option (INSTALL_LIB_TARGET_ARCH_SYMLINK "Install a symlink lib-<target-arch> to lib-${CMAKE_BUILD_TYPE} facilitating the linking of user code, which build system assumes to find the UVM-SystemC libraries under lib-<target-arch>." OFF)
else (CMAKE_HOST_UNIX AND NOT INSTALL_TO_LIB_TARGET_ARCH_DIR)
    unset (INSTALL_LIB_TARGET_ARCH_SYMLINK CACHE)
endif (CMAKE_HOST_UNIX AND NOT INSTALL_TO_LIB_TARGET_ARCH_DIR)

mark_as_advanced(DISABLE_COPYRIGHT_MESSAGE)

###############################################################################
# Set UVMSC_TARGET_ARCH depending on OS and processor type
###############################################################################

message (STATUS "Checking OS and processor type.")

if (APPLE)
    list (LENGTH CMAKE_OSX_ARCHITECTURES N_OSX_ARCHITECTURES)
endif (APPLE)

if (NOT APPLE OR (APPLE AND (N_OSX_ARCHITECTURES LESS 2)))
    if (APPLE)
        if (N_OSX_ARCHITECTURES EQUAL 1)
            message (STATUS "The target architecture will be passed explicitly to the Apple compiler.")
            set (CMAKE_REQUIRED_FLAGS "-arch ${CMAKE_OSX_ARCHITECTURES}")
        endif (N_OSX_ARCHITECTURES EQUAL 1)
        unset (HAS__i386_DEFINED CACHE)
        unset (HAS__x86_64__DEFINED CACHE)
        unset (HAS__ppc__DEFINED CACHE)
    endif (APPLE)
    include (CheckSymbolExists)
    check_symbol_exists (__LP64__ "" HAS__LP64__DEFINED)
    check_symbol_exists (__sparc "" HAS__sparc_DEFINED)
    check_symbol_exists (__sparc__ "" HAS__sparc__DEFINED)
    check_symbol_exists (__hppa "" HAS__hppa_DEFINED)
    check_symbol_exists (__x86_64__ "" HAS__x86_64__DEFINED)
    check_symbol_exists (__i386 "" HAS__i386_DEFINED)
    check_symbol_exists (__aarch64__ "" HAS__aarch64__DEFINED)
    check_symbol_exists (__ppc__ "" HAS__ppc__DEFINED)
    check_symbol_exists (__powerpc "" HAS__powerpc_DEFINED)
endif (NOT APPLE OR (APPLE AND (N_OSX_ARCHITECTURES LESS 2)))


# Set UVMSC_TARGET_ARCH according to the detected
# OS/processor/compiler platform
if (NOT UVMSC_TARGET_ARCH)
    if ($ENV{UVMSC_TARGET_ARCH})
        message (STATUS "Using UVMSC_TARGET_ARCH from the environment.")
        set (_TARGET_ARCH $ENV{UVMSC_TARGET_ARCH})
    elseif (APPLE)
        if (N_OSX_ARCHITECTURES GREATER 1)
            set (_TARGET_ARCH "macosxuniversal")
        elseif (HAS__i386_DEFINED)
            set (_TARGET_ARCH "macosx")
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "macosx64")
        elseif (HAS__ppc__DEFINED)
            set (_TARGET_ARCH "macosxppc")
        elseif (HAS__ppc64__DEFINED)
            set (_TARGET_ARCH "macosxppc64")
        else (HAS__i386_DEFINED)
            set (_TARGET_ARCH "macosxunknown")
        endif (N_OSX_ARCHITECTURES GREATER 1)
    elseif (UNIX AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        if (HAS__i386_DEFINED)
            set (_TARGET_ARCH "linux")
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "linux64")
        elseif (HAS__aarch64__DEFINED)
            set (_TARGET_ARCH "linuxaarch64")
        elseif (HAS__powerpc_DEFINED)
            # Untested platform.
            set (_TARGET_ARCH "linuxppc")
        elseif (HAS__sparc_DEFINED OR HAS__sparc__DEFINED)
            # Untested platform.
            set (_TARGET_ARCH "linuxsparc")
        else (HAS__i386_DEFINED)
            # Untested platform.
            set (_TARGET_ARCH "linuxunknown")
        endif (HAS__i386_DEFINED)
    elseif (UNIX AND CMAKE_SYSTEM_NAME MATCHES ".*BSD")
        if (HAS__i386_DEFINED)
            set (_TARGET_ARCH "bsd")
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "bsd64")
        else (HAS__i386_DEFINED)
            # Untested platform.
            set (_TARGET_ARCH "bsdunknown")
        endif (HAS__i386_DEFINED)
    elseif (UNIX AND CMAKE_SYSTEM_NAME STREQUAL "SunOS"
            AND (HAS__sparc_DEFINED OR HAS__sparc__DEFINED))
        # Untested platform.
        set (_TARGET_ARCH "sparcOS5")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (_TARGET_ARCH "gcc${_TARGET_ARCH}")
        endif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    elseif (UNIX AND CMAKE_SYSTEM_NAME STREQUAL "HP-UX" AND HAS__hppa_DEFINED)
        # Untested platform.
        set (_TARGET_ARCH "hpux11")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (_TARGET_ARCH "gcc${_TARGET_ARCH}")
        endif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if (HAS__LP64__DEFINED)
            set (_TARGET_ARCH "${_TARGET_ARCH}64")
        endif (HAS__LP64__DEFINED)
    elseif (MSVC)
        set (_TARGET_ARCH "msvc")
        if (CMAKE_CL_64)
            set (_TARGET_ARCH "${_TARGET_ARCH}64")
        endif (CMAKE_CL_64)
    elseif (CYGWIN)
        if (HAS__i386_DEFINED)
            set (_TARGET_ARCH "cygwin")
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "cygwin64")
        else (HAS__i386_DEFINED)
            set (_TARGET_ARCH "cygwinunknown")
        endif (HAS__i386_DEFINED)
    elseif (WIN32
            AND ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")))
        # MinGW platform, as CYGWIN already has been handled
        if (HAS__i386_DEFINED)
            set (_TARGET_ARCH "mingw")
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "mingw64")
        else (HAS__i386_DEFINED)
            set (_TARGET_ARCH "mingwunknown")
        endif (HAS__i386_DEFINED)
    else ($ENV{UVMSC_TARGET_ARCH})
        # Unknown platform, so guess a UVM-SystemC target architecture value.
        string (TOLOWER "${CMAKE_SYSTEM_NAME}${CMAKE_PROCESSOR_NAME}" _TARGET_ARCH)
    endif ($ENV{UVMSC_TARGET_ARCH})
    set (UVMSC_TARGET_ARCH ${_TARGET_ARCH} CACHE STRING "UVM-SystemC Target Architecture")
    unset (_TARGET_ARCH)
endif (NOT UVMSC_TARGET_ARCH)


###############################################################################
# Set the installation paths
###############################################################################

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if (IS_ABSOLUTE $ENV{UVMSC_HOME})
        set (_CMAKE_INSTALL_PREFIX $ENV{UVMSC_HOME})
    elseif (UNIX)
        set (_CMAKE_INSTALL_PREFIX "/opt/uvmsc")
    elseif (WIN32)
        file (TO_CMAKE_PATH $ENV{ProgramFiles} _WIN32_INSTALL_PREFIX)
        set (_CMAKE_INSTALL_PREFIX "${_WIN32_INSTALL_PREFIX}/uvmsc")
        unset (_WIN32_INSTALL_PREFIX)
    else (EXISTS $ENV{SYSTEMC_ROOT_DIR})
        set (_CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/uvmsc")
    endif (IS_ABSOLUTE $ENV{UVMSC_HOME})
    set (CMAKE_INSTALL_PREFIX ${_CMAKE_INSTALL_PREFIX} CACHE PATH "Installation root directory" FORCE)
    unset (_CMAKE_INSTALL_PREFIX)
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Set the installation paths for headers, libraries, and documentation.
set (CMAKE_INSTALL_DOCDIR "share/doc/uvmsc" CACHE PATH
    "Documentation installation directory") # otherwise mixed-case
if (INSTALL_TO_LIB_BUILD_TYPE_DIR)
    # Install libraries to lib-${CMAKE_BUILD_TYPE} so that different build variants
    # of the library can be installed in parallel to the same UVM-SystemC root
    # directory. The find_package() mechanism in config-mode of CMake will then
    # automatically find the correct libraries matching the chosen
    # ${CMAKE_BUILD_TYPE}.
    set (_INSTALL_LIBDIR lib-${CMAKE_BUILD_TYPE})
    string (TOLOWER ${_INSTALL_LIBDIR} _INSTALL_LIBDIR)
    set (CMAKE_INSTALL_LIBDIR ${_INSTALL_LIBDIR} CACHE PATH
        "Object code libraries installation directory" FORCE)
    unset (_INSTALL_LIBDIR)
elseif (INSTALL_TO_LIB_TARGET_ARCH_DIR)
    # Some build systems assume to find UVM-SystemC in lib-<target-arch>
    set (CMAKE_INSTALL_LIBDIR lib-${UVMSC_TARGET_ARCH} CACHE PATH
        "Object code libraries installation directory" FORCE)
endif (INSTALL_TO_LIB_BUILD_TYPE_DIR)
include (GNUInstallDirs)

# Install symlink lib-<target-arch> to lib-${CMAKE_BUILD_TYPE}
if (INSTALL_LIB_TARGET_ARCH_SYMLINK AND CMAKE_HOST_UNIX)
    install (CODE "
    EXECUTE_PROCESS(COMMAND cmake -E create_symlink ${CMAKE_INSTALL_LIBDIR} lib-${UVMSC_TARGET_ARCH}
                    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX})
  ")
endif (INSTALL_LIB_TARGET_ARCH_SYMLINK AND CMAKE_HOST_UNIX)

if (INSTALL_TO_LIB_BUILD_TYPE_DIR OR INSTALL_TO_LIB_TARGET_ARCH_DIR)
    set (UVMSC_INSTALL_CMAKEDIR share/cmake/UVMSC CACHE PATH
        "CMake package configuration installation directory" FORCE)
else (INSTALL_TO_LIB_BUILD_TYPE_DIR OR INSTALL_TO_LIB_TARGET_ARCH_DIR)
  set (UVMSC_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/UVMSC CACHE PATH
      "CMake package configuration installation directory for the UVM-SystemC package.")
endif (INSTALL_TO_LIB_BUILD_TYPE_DIR OR INSTALL_TO_LIB_TARGET_ARCH_DIR)
mark_as_advanced(UVMSC_INSTALL_CMAKEDIR)
set(UVMSC_INSTALL_FULL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/${UVMSC_INSTALL_CMAKEDIR}")


###############################################################################
# Configure RPATH so that all targets find the libraries they link to
###############################################################################

# Starting from CMake 2.8.12 use CMake's full RPATH support on Mac OS X
set (CMAKE_MACOSX_RPATH TRUE)

# Use, i.e., don't skip, the full RPATH for the build tree.
set (CMAKE_SKIP_BUILD_RPATH  FALSE)

# For build, don't use the install RPATH already (but later on when installing).
set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# Set the RPATH to be used when installing.
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")

# Add the automatically determined parts of the RPATH, which point to
# directories outside the build tree, to the install RPATH.
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set the RPATH to be used when installing, but only if it's not a system directory
list (FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
if ("${isSystemDir}" STREQUAL "-1")
  set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
endif ("${isSystemDir}" STREQUAL "-1")


###############################################################################
# Configure status
###############################################################################

message (STATUS "========================================================================")
message (STATUS "Settings to build UVM-SystemC ${UVM_VERSION} (${UVM_RELEASE_DATE})")
message (STATUS "------------------------------------------------------------------------")
message (STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message (STATUS "BUILD_SOURCE_DOCUMENTATION = ${BUILD_SOURCE_DOCUMENTATION}")
message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message (STATUS "DISABLE_COPYRIGHT_MESSAGE = ${DISABLE_COPYRIGHT_MESSAGE}")
message (STATUS "UVMSC_TARGET_ARCH = ${UVMSC_TARGET_ARCH}")
message (STATUS "UVM_VERSION = ${UVM_VERSION}")
message (STATUS "INSTALL_TO_LIB_BUILD_TYPE_DIR = ${INSTALL_TO_LIB_BUILD_TYPE_DIR}")
message (STATUS "INSTALL_TO_LIB_TARGET_ARCH_DIR = ${INSTALL_TO_LIB_TARGET_ARCH_DIR}")
message (STATUS "INSTALL_LIB_TARGET_ARCH_SYMLINK = ${INSTALL_LIB_TARGET_ARCH_SYMLINK}")
message (STATUS "------------------------------------------------------------------------")
message (STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message (STATUS "CMAKE_CXX_STANDARD_REQUIRED = ${CMAKE_CXX_STANDARD_REQUIRED}")
message (STATUS "CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message (STATUS "CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}")
if (DEFINED CMAKE_OSX_ARCHITECTURES)
  message (STATUS "CMAKE_OSX_ARCHITECTURES = ${CMAKE_OSX_ARCHITECTURES}")
endif (DEFINED CMAKE_OSX_ARCHITECTURES)
if (DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
  message (STATUS "CMAKE_OSX_DEPLOYMENT_TARGET = ${CMAKE_OSX_DEPLOYMENT_TARGET}")
endif (DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
if (DEFINED CMAKE_OSX_SYSROOT)
  message (STATUS "CMAKE_OSX_SYSROOT = ${CMAKE_OSX_SYSROOT}")
endif(DEFINED CMAKE_OSX_SYSROOT)
message (STATUS "------------------------------------------------------------------------")
message (STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
message (STATUS "CMAKE_INSTALL_BINDIR = ${CMAKE_INSTALL_BINDIR}")
message (STATUS "CMAKE_INSTALL_DOCDIR = ${CMAKE_INSTALL_DOCDIR}")
message (STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}")
message (STATUS "CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}")
message (STATUS "INSTALL_CMAKEDIR = ${INSTALL_CMAKEDIR}")
message (STATUS "========================================================================")


###############################################################################
# Subdirectories
###############################################################################

add_subdirectory (docs)
add_subdirectory (src)
# add_subdirectory (examples)


###############################################################################
# Install README files
###############################################################################

install (FILES AUTHORS
               ChangeLog
               INSTALL
               LICENSE
               NEWS
               NOTICE
               README
               RELEASENOTES
         DESTINATION ${CMAKE_INSTALL_DOCDIR}
         COMPONENT doc)


###############################################################################
# Provide package of the UVM-SystemC library to other programs using CMake
###############################################################################

# Export the UVM-SystemC library target for usage by other programs
# ... to local build tree
export (TARGETS uvm-systemc
        NAMESPACE UVMSC::
        FILE UVMSCTargets.cmake)
# ... to installation tree
install (EXPORT UVMSCTargets
         NAMESPACE UVMSC::
         DESTINATION ${UVMSC_INSTALL_CMAKEDIR}
         COMPONENT dev)

# Register the UVM-SystemC package for use from the build tree. (This registers
# the build tree with the global CMake-registry.)
export (PACKAGE UVMSC)

# Create the <Package>Config.cmake and <Package>ConfigVersion files
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/UVMSCConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/UVMSCConfig.cmake
  INSTALL_DESTINATION ${UVMSC_INSTALL_CMAKEDIR})
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/UVMSCConfigVersion.cmake"
  VERSION ${UVM_VERSION}.${UVM_RELEASE_DATE}
  COMPATIBILITY AnyNewerVersion
)

# Install the <Package>Config.cmake and <Package>ConfigVersion.cmake
install(FILES "${PROJECT_BINARY_DIR}/UVMSCConfig.cmake"
              "${PROJECT_BINARY_DIR}/UVMSCConfigVersion.cmake"
        DESTINATION "${UVMSC_INSTALL_CMAKEDIR}"
        COMPONENT dev)
