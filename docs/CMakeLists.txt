set (DOC_FILES
    UVM_goes_Universal_-_Introducing_UVM_in_SystemC_-_DVCON_Europe_2015.pdf
    uvm-systemc-language-reference-manual.pdf
    )

foreach (DOC_FILE ${DOC_FILES})
    get_filename_component (DOC_INSTALL_PATH ${DOC_FILE} PATH)
    install (FILES ${DOC_FILE}
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/${DOC_INSTALL_PATH}
        COMPONENT doc)
endforeach (DOC_FILE ${DOC_FILES})

if (BUILD_SOURCE_DOCUMENTATION)
    find_package (Doxygen REQUIRED)
    add_custom_target (doxygen ALL
        DEPENDS doxygen-uvmsc)

    # UVM-SystemC source code documentation
    set (PACKAGE_NAME ${PROJECT_NAME})
    string(TOLOWER "${PROJECT_NAME}" PACKAGE_TARNAME)
    set (PACKAGE_VERSION ${UVM_VERSION})
    set (top_srcdir ${CMAKE_SOURCE_DIR})

    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/uvmsc/doxygen/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/Doxyfile @ONLY)
    if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html)
        file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html)
    endif (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html)
    set_source_files_properties (${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html
        PROPERTIES GENERATED 1)
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/Doxyfile
        DEPENDS uvmsc
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen
        COMMENT "Building the UVM-SystemC source code documentation using Doxygen.")
    add_custom_target (doxygen-uvmsc
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html/index.html)
    install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/html
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/uvmsc/doxygen
        COMPONENT doc)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/uvmsc/doxygen/${PACKAGE_TARNAME}.tag
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/uvmsc/doxygen
        COMPONENT doc)
endif (BUILD_SOURCE_DOCUMENTATION)
