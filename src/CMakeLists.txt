###############################################################################
# Build rules for UVM-SystemC library
###############################################################################

file(GLOB_RECURSE cpp_files
  LIST_DIRECTORIES false
  *.cpp
  )

add_library (uvm-systemc ${cpp_files})

target_include_directories(
    uvm-systemc
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if (APPLE)
    # It's OK that _sc_main is an undefined symbol.
    set_target_properties(uvm-systemc PROPERTIES LINK_FLAGS -Wl,-U,_sc_main)
endif (APPLE)

target_link_libraries (uvm-systemc PUBLIC SystemC::systemc)

###############################################################################
# Install rules for UVM-SystemC library
###############################################################################

install (TARGETS uvm-systemc
    EXPORT ${TARGETS_EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT lib)

# Install the UVM-SystemC headers
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/uvm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev
    FILES_MATCHING PATTERN "*.h"
    PATTERN ".deps" EXCLUDE)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev
    FILES_MATCHING PATTERN "*.hpp"
    PATTERN ".deps" EXCLUDE)
