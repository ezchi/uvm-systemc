include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_callback_defines.h\
	uvm_component_defines.h \
	uvm_macros.h \
	uvm_message_defines.h \
	uvm_object_defines.h \
	uvm_reg_defines.h \
	uvm_sequence_defines.h \
	uvm_string_defines.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = 

NO_CXX_FILES =

noinst_LTLIBRARIES = libmacros.la

libmacros_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/macros

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
