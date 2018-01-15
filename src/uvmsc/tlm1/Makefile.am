include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_analysis_export.h \
	uvm_analysis_imp.h \
	uvm_analysis_port.h \
	uvm_exports.h \
	uvm_imps.h \
	uvm_ports.h \
	uvm_sqr_connections.h \
	uvm_tlm_req_rsp_channel.h \
	uvm_tlm1.h 

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = 

NO_CXX_FILES =

noinst_LTLIBRARIES = libtlm1.la

libtlm1_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/tlm1

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
