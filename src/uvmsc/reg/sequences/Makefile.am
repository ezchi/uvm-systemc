include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_reg_bit_bash_seq.h \
	uvm_reg_mem_hdl_paths_seq.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = 

NO_CXX_FILES =

noinst_LTLIBRARIES = libsequences.la

libsequences_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/reg/sequences

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
