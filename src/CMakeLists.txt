###############################################################################
# Build rules for UVM-SystemC library
###############################################################################

add_library (uvm-systemc
    uvmsc/misc/uvm_scope_stack.cpp
    uvmsc/misc/uvm_status_container.cpp
    uvmsc/misc/uvm_misc.cpp
    uvmsc/reg/uvm_reg_map.cpp
    uvmsc/reg/uvm_reg_item.cpp
    uvmsc/reg/uvm_reg_model.cpp
    uvmsc/reg/uvm_reg_field.cpp
    uvmsc/reg/uvm_mem_region.cpp
    uvmsc/reg/uvm_reg_backdoor.cpp
    uvmsc/reg/uvm_vreg_field.cpp
    uvmsc/reg/uvm_reg_fifo.cpp
    uvmsc/reg/uvm_reg_read_only_cbs.cpp
    uvmsc/reg/uvm_reg.cpp
    uvmsc/reg/uvm_reg_indirect_data.cpp
    uvmsc/reg/uvm_reg_write_only_cbs.cpp
    uvmsc/reg/uvm_mem.cpp
    uvmsc/reg/uvm_vreg_field_cbs.cpp
    uvmsc/reg/uvm_reg_tlm_adapter.cpp
    uvmsc/reg/uvm_vreg.cpp
    uvmsc/reg/uvm_reg_indirect_ftdr_seq.cpp
    uvmsc/reg/uvm_reg_adapter.cpp
    uvmsc/reg/uvm_mem_mam.cpp
    uvmsc/reg/uvm_reg_file.cpp
    uvmsc/reg/uvm_reg_block.cpp
    uvmsc/seq/uvm_sequencer_base.cpp
    uvmsc/seq/uvm_sequence_base.cpp
    uvmsc/seq/uvm_sequence_item.cpp
    uvmsc/phasing/uvm_bottomup_phase.cpp
    uvmsc/phasing/uvm_phase.cpp
    uvmsc/phasing/uvm_domain.cpp
    uvmsc/phasing/uvm_runtime_phases.cpp
    uvmsc/phasing/uvm_objection.cpp
    uvmsc/phasing/uvm_topdown_phase.cpp
    uvmsc/phasing/uvm_common_phases.cpp
    uvmsc/phasing/uvm_process_phase.cpp
    uvmsc/dpi/uvm_hdl.cpp
    uvmsc/print/uvm_tree_printer.cpp
    uvmsc/print/uvm_printer_globals.cpp
    uvmsc/print/uvm_printer.cpp
    uvmsc/print/uvm_table_printer.cpp
    uvmsc/report/uvm_report_handler.cpp
    uvmsc/report/uvm_report_catcher_data.cpp
    uvmsc/report/uvm_report_catcher.cpp
    uvmsc/report/uvm_report_object.cpp
    uvmsc/report/uvm_default_report_server.cpp
    uvmsc/report/uvm_report_server.cpp
    uvmsc/report/uvm_report_message.cpp
    uvmsc/comps/uvm_agent.cpp
    uvmsc/cb/uvm_callbacks_base.cpp
    uvmsc/cb/uvm_callback.cpp
    uvmsc/cb/uvm_typeid.cpp
    uvmsc/conf/uvm_resource_base.cpp
    uvmsc/conf/uvm_config_db_options.cpp
    uvmsc/conf/uvm_resource_options.cpp
    uvmsc/conf/uvm_resource_pool.cpp
    uvmsc/conf/uvm_resource_db_options.cpp
    uvmsc/factory/uvm_factory_override.cpp
    uvmsc/factory/uvm_default_factory.cpp
    uvmsc/base/uvm_object_globals.cpp
    uvmsc/base/uvm_event_callback.cpp
    uvmsc/base/uvm_component.cpp
    uvmsc/base/uvm_component_name.cpp
    uvmsc/base/uvm_root.cpp
    uvmsc/base/uvm_coreservice_t.cpp
    uvmsc/base/uvm_object.cpp
    uvmsc/base/uvm_mutex.cpp
    uvmsc/base/uvm_transaction.cpp
    uvmsc/base/uvm_globals.cpp
    uvmsc/base/uvm_default_coreservice_t.cpp
    uvmsc/base/uvm_event.cpp
    uvmsc/base/uvm_version.cpp
    uvmsc/policy/uvm_recorder.cpp
    uvmsc/policy/uvm_packer.cpp
    uvmsc/policy/uvm_comparer.cpp
    )

target_compile_definitions (
    uvm-systemc
    PRIVATE
    UVM_BUILD
    UVM_INCLUDE_FX
    $<$<BOOL:${DEBUG_UVM}>:DEBUG_UVM>
    $<$<BOOL:${DISABLE_COPYRIGHT_MESSAGE}>:UVM_DISABLE_COPYRIGHT_MESSAGE>
    )

# target_compile_options(
#     uvm-systemc
#     PRIVATE
#     $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wno-unused-parameter -Wno-unused-variable>
#     )

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

# set_target_properties (uvm-systemc
#     PROPERTIES
#     LINKER_LANGUAGE CXX
#     VERSION ${UVM_VERSION}
#     INSTALL_NAME_DIR ${CMAKE_INSTALL_FULL_LIBDIR})


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
    FILES_MATCHING PATTERN "*.h")
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev
    FILES_MATCHING PATTERN "*.hpp")
