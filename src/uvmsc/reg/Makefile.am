include $(top_srcdir)/config/Make-rules

SUBDIRS = \
	sequences

H_FILES = \
	uvm_hdl_path_concat.h \
	uvm_mem.h \
	uvm_mem_mam.h \
	uvm_mem_mam_cfg.h \
	uvm_mem_mam_policy.h \
	uvm_mem_region.h \
	uvm_reg.h \
	uvm_reg_adapter.h \
	uvm_reg_backdoor.h \
	uvm_reg_block.h \
	uvm_reg_bus_op.h \
	uvm_reg_cbs.h \
	uvm_reg_cbs_types.h \
	uvm_reg_field.h \
	uvm_reg_fifo.h \
	uvm_reg_file.h \
	uvm_reg_frontdoor.h \
	uvm_reg_indirect_data.h \
	uvm_reg_indirect_ftdr_seq.h \
	uvm_reg_item.h \
	uvm_reg_layer.h \
	uvm_reg_map.h \
	uvm_reg_model.h \
	uvm_reg_predictor.h \
	uvm_reg_read_only_cbs.h \
	uvm_reg_sequence.h \
	uvm_reg_tlm_adapter.h \
	uvm_reg_write_only_cbs.h \
	uvm_sc_reg.h \
	uvm_vreg.h \
	uvm_vreg_cbs.h \
	uvm_vreg_field.h \
	uvm_vreg_field_cbs.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_mem.cpp \
	uvm_mem_mam.cpp \
	uvm_mem_region.cpp \
	uvm_reg.cpp \
	uvm_reg_adapter.cpp \
	uvm_reg_backdoor.cpp \
	uvm_reg_block.cpp \
	uvm_reg_field.cpp \
	uvm_reg_fifo.cpp \
	uvm_reg_file.cpp \
	uvm_reg_indirect_data.cpp \
	uvm_reg_indirect_ftdr_seq.cpp \
	uvm_reg_item.cpp \
	uvm_reg_map.cpp \
	uvm_reg_model.cpp \
	uvm_reg_read_only_cbs.cpp \
	uvm_reg_tlm_adapter.cpp \
	uvm_reg_write_only_cbs.cpp \
	uvm_vreg.cpp \
	uvm_vreg_field.cpp \
	uvm_vreg_field_cbs.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libreg.la

libreg_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/reg

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(INCLUDE_DIR)
	for file in $(noinst_HEADERS); do \
	  $(INSTALL_DATA) $(srcdir)/$$file $(DESTDIR)$(INCLUDE_DIR)/$$file; \
	done

uninstall-local:
	@$(NORMAL_UNINSTALL)
	for file in $(noinst_HEADERS); do \
	  rm -f $(DESTDIR)$(INCLUDE_DIR)/$$file; \
	done
	-rmdir $(DESTDIR)$(INCLUDE_DIR)

## Taf!
