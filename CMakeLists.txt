cmake_minimum_required (VERSION 3.1)

project (UVMSystemC VERSION 0.1.0)

option(SYSTEMC_HOME "SystemC home directory" $ENV{SYSTEMC_HOME})

set(CMAKE_PREFIX_PATH ${SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD} CACHE STRING
  "C++ standard to build all targets. Supported values are 98, 11, and 14.")
set (CMAKE_CXX_STANDARD_REQUIRED ${SystemC_CXX_STANDARD_REQUIRED} CACHE BOOL
    "The with CMAKE_CXX_STANDARD selected C++ standard is a requirement.")
mark_as_advanced(CMAKE_CXX_STANDARD_REQUIRED)

###############################################################################
# Build options
###############################################################################

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: empty, Debug, Release, RelWithDebInfo, MinSizeRel."
        FORCE)
endif (NOT CMAKE_BUILD_TYPE)


option (BUILD_SHARED_LIBS "Build shared libraries." OFF)

option (BUILD_SOURCE_DOCUMENTATION "Build source documentation with Doxygen." ON)
option (DISABLE_COPYRIGHT_MESSAGE "Do not print the copyright message when starting the application." ON)
mark_as_advanced(DISABLE_COPYRIGHT_MESSAGE)

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
        unset (HAS__x86_64__DEFINED CACHE)
    endif (APPLE)
    include (CheckSymbolExists)
    check_symbol_exists (__x86_64__ "" HAS__x86_64__DEFINED)
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
        elseif (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "macosx64")
        endif (N_OSX_ARCHITECTURES GREATER 1)
    elseif (UNIX AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
        if (HAS__x86_64__DEFINED)
            set (_TARGET_ARCH "linux64")
        endif (HAS__x86_64__DEFINED)
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
include (GNUInstallDirs)

# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Set the installation paths for headers, libraries, and documentation.
set (CMAKE_INSTALL_DOCDIR "share/doc/uvmsc" CACHE PATH
    "Documentation installation directory") # otherwise mixed-case

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
message (STATUS "Settings to build UVM-SystemC")
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
# message (STATUS "INSTALL_CMAKEDIR = ${INSTALL_CMAKEDIR}")
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


# Register the UVM-SystemC package for use from the build tree. (This registers
# the build tree with the global CMake-registry.)
export (PACKAGE ${PROJECT_NAME})

# Config
#   * <prefix>/lib/cmake/<ProjectName>/<ProjectName>Config.cmake
#   * <prefix>/lib/cmake/<ProjectName>/<ProjectName>ConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/<ProjectName>/<ProjectName>Targets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
