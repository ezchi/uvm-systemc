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
    uvmsc/base/uvm_transaction.cpp
    uvmsc/base/uvm_globals.cpp
    uvmsc/base/uvm_default_coreservice_t.cpp
    uvmsc/base/uvm_event.cpp
    uvmsc/base/uvm_version.cpp
    uvmsc/policy/uvm_recorder.cpp
    uvmsc/policy/uvm_packer.cpp
    uvmsc/policy/uvm_comparer.cpp
    # UVM-SystemC headers
    uvm
    uvm.h
    uvmsc/misc/uvm_status_container.h
    uvmsc/misc/uvm_copy_map.h
    uvmsc/misc/uvm_misc.h
    uvmsc/misc/uvm_scope_stack.h
    uvmsc/reg/uvm_vreg.h
    uvmsc/reg/uvm_reg_frontdoor.h
    uvmsc/reg/uvm_reg_map.h
    uvmsc/reg/uvm_mem_region.h
    uvmsc/reg/uvm_reg_model.h
    uvmsc/reg/uvm_reg_block.h
    uvmsc/reg/uvm_reg_fifo.h
    uvmsc/reg/uvm_reg_sequence.h
    uvmsc/reg/uvm_reg_indirect_data.h
    uvmsc/reg/uvm_reg_cbs_types.h
    uvmsc/reg/uvm_reg_cbs.h
    uvmsc/reg/uvm_reg_read_only_cbs.h
    uvmsc/reg/uvm_vreg_field.h
    uvmsc/reg/uvm_mem.h
    uvmsc/reg/uvm_mem_mam.h
    uvmsc/reg/uvm_reg_predictor.h
    uvmsc/reg/uvm_reg_item.h
    uvmsc/reg/uvm_reg_tlm_adapter.h
    uvmsc/reg/uvm_reg_file.h
    uvmsc/reg/uvm_reg_backdoor.h
    uvmsc/reg/uvm_hdl_path_concat.h
    uvmsc/reg/uvm_reg.h
    uvmsc/reg/uvm_reg_write_only_cbs.h
    uvmsc/reg/uvm_reg_bus_op.h
    uvmsc/reg/uvm_sc_reg.h
    uvmsc/reg/sequences/uvm_reg_mem_hdl_paths_seq.h
    uvmsc/reg/sequences/uvm_reg_bit_bash_seq.h
    uvmsc/reg/uvm_vreg_field_cbs.h
    uvmsc/reg/uvm_reg_layer.h
    uvmsc/reg/uvm_reg_field.h
    uvmsc/reg/uvm_reg_indirect_ftdr_seq.h
    uvmsc/reg/uvm_vreg_cbs.h
    uvmsc/reg/uvm_mem_mam_policy.h
    uvmsc/reg/uvm_mem_mam_cfg.h
    uvmsc/reg/uvm_reg_adapter.h
    uvmsc/seq/uvm_sequencer_param_base.h
    uvmsc/seq/uvm_sequence.h
    uvmsc/seq/uvm_sequencer_base.h
    uvmsc/seq/uvm_sequence_base.h
    uvmsc/seq/uvm_sequencer.h
    uvmsc/seq/uvm_seq.h
    uvmsc/seq/uvm_sequence_item.h
    uvmsc/seq/uvm_sequencer_ifs.h
    uvmsc/phasing/uvm_common_phases.h
    uvmsc/phasing/uvm_runtime_phases.h
    uvmsc/phasing/uvm_objection.h
    uvmsc/phasing/uvm_phase_queue.h
    uvmsc/phasing/uvm_domain.h
    uvmsc/phasing/uvm_phasing.h
    uvmsc/phasing/uvm_process_phase.h
    uvmsc/phasing/uvm_topdown_phase.h
    uvmsc/phasing/uvm_process.h
    uvmsc/phasing/uvm_phase.h
    uvmsc/phasing/uvm_bottomup_phase.h
    uvmsc/dpi/uvm_hdl.h
    uvmsc/print/uvm_printer.h
    uvmsc/print/uvm_table_printer.h
    uvmsc/print/uvm_line_printer.h
    uvmsc/print/uvm_printer_globals.h
    uvmsc/print/uvm_tree_printer.h
    uvmsc/print/uvm_printer_knobs.h
    uvmsc/print/uvm_print.h
    uvmsc/macros/uvm_callback_defines.h
    uvmsc/macros/uvm_string_defines.h
    uvmsc/macros/uvm_sequence_defines.h
    uvmsc/macros/uvm_macros.h
    uvmsc/macros/uvm_reg_defines.h
    uvmsc/macros/uvm_object_defines.h
    uvmsc/macros/uvm_message_defines.h
    uvmsc/macros/uvm_component_defines.h
    uvmsc/report/uvm_report_catcher.h
    uvmsc/report/uvm_report_object.h
    uvmsc/report/uvm_default_report_server.h
    uvmsc/report/uvm_report.h
    uvmsc/report/uvm_report_server.h
    uvmsc/report/uvm_report_handler.h
    uvmsc/report/uvm_report_catcher_data.h
    uvmsc/report/uvm_report_message.h
    uvmsc/comps/uvm_comps.h
    uvmsc/comps/uvm_scoreboard.h
    uvmsc/comps/uvm_subscriber.h
    uvmsc/comps/uvm_test.h
    uvmsc/comps/uvm_driver.h
    uvmsc/comps/uvm_env.h
    uvmsc/comps/uvm_monitor.h
    uvmsc/comps/uvm_agent.h
    uvmsc/tlm1/uvm_ports.h
    uvmsc/tlm1/uvm_exports.h
    uvmsc/tlm1/uvm_tlm1.h
    uvmsc/tlm1/uvm_sqr_connections.h
    uvmsc/tlm1/uvm_imps.h
    uvmsc/tlm1/uvm_analysis_port.h
    uvmsc/tlm1/uvm_analysis_imp.h
    uvmsc/tlm1/uvm_tlm_req_rsp_channel.h
    uvmsc/tlm1/uvm_analysis_export.h
    uvmsc/cb/uvm_typed_callbacks.h
    uvmsc/cb/uvm_callback.h
    uvmsc/cb/uvm_callback_iter.h
    uvmsc/cb/uvm_callbacks_base.h
    uvmsc/cb/uvm_derived_callbacks.h
    uvmsc/cb/uvm_cbs.h
    uvmsc/cb/uvm_callbacks.h
    uvmsc/cb/uvm_typeid.h
    uvmsc/conf/uvm_resource_options.h
    uvmsc/conf/uvm_resource_db.h
    uvmsc/conf/uvm_resource_types.h
    uvmsc/conf/uvm_resource.h
    uvmsc/conf/uvm_object_string_pool.h
    uvmsc/conf/uvm_config_db.h
    uvmsc/conf/uvm_resource_pool.h
    uvmsc/conf/uvm_conf.h
    uvmsc/conf/uvm_config_db_options.h
    uvmsc/conf/uvm_resource_base.h
    uvmsc/conf/uvm_queue.h
    uvmsc/conf/uvm_resource_converter.h
    uvmsc/conf/uvm_resource_db_options.h
    uvmsc/factory/uvm_factory_override.h
    uvmsc/factory/uvm_fact_reg.h
    uvmsc/factory/uvm_object_registry.h
    uvmsc/factory/uvm_component_registry.h
    uvmsc/factory/uvm_object_wrapper.h
    uvmsc/factory/uvm_factory.h
    uvmsc/factory/uvm_default_factory.h
    uvmsc/base/uvm_version.h
    uvmsc/base/uvm_void.h
    uvmsc/base/uvm_event_callback.h
    uvmsc/base/uvm_object.h
    uvmsc/base/uvm_globals.h
    uvmsc/base/uvm_event.h
    uvmsc/base/uvm_component.h
    uvmsc/base/uvm_port_base.h
    uvmsc/base/uvm_component_name.h
    uvmsc/base/uvm_default_coreservice_t.h
    uvmsc/base/uvm_coreservice_t.h
    uvmsc/base/uvm_base.h
    uvmsc/base/uvm_root.h
    uvmsc/base/uvm_object_globals.h
    uvmsc/base/uvm_export_base.h
    uvmsc/base/uvm_transaction.h
    uvmsc/kernel/uvmsc_ver.h
    uvmsc/policy/uvm_recorder.h
    uvmsc/policy/uvm_policy.h
    uvmsc/policy/uvm_packer.h
    uvmsc/policy/uvm_comparer.h
    )

add_library (UVMSC::uvm-systemc ALIAS uvm-systemc)

target_compile_definitions (
    uvm-systemc
    PUBLIC
    $<$<BOOL:${WIN32}>:WIN32>
    $<$<AND:$<BOOL:${BUILD_SHARED_LIBS}>,$<OR:$<BOOL:${WIN32}>,$<BOOL:${CYGWIN}>>>:UVM_WIN_DLL>
    PRIVATE
    UVM_BUILD
    UVM_INCLUDE_FX
    $<$<BOOL:${DEBUG_UVM}>:DEBUG_UVM>
    $<$<BOOL:${DISABLE_COPYRIGHT_MESSAGE}>:UVM_DISABLE_COPYRIGHT_MESSAGE>
    $<$<AND:$<BOOL:${WIN32}>,$<BOOL:${MSVC}>>:_LIB>)

target_compile_options(
    uvm-systemc
    PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/vmg /MP>
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable>
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /wd4244 /wd4267 /wd4996>)

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

set_target_properties (uvm-systemc
    PROPERTIES
    LINKER_LANGUAGE CXX
    VERSION ${UVM_VERSION}
    INSTALL_NAME_DIR ${CMAKE_INSTALL_FULL_LIBDIR})


###############################################################################
# Install rules for UVM-SystemC library
###############################################################################

install (TARGETS uvm-systemc EXPORT UVMSCTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT lib)

# Install the UVM-SystemC headers
install (FILES uvm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev)
install (DIRECTORY ./
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev
    FILES_MATCHING PATTERN "*.h")
install (DIRECTORY ./
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT dev
    FILES_MATCHING PATTERN "*.hpp")
