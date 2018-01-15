include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_callback.h \
	uvm_callback_iter.h \
	uvm_callbacks.h \
	uvm_callbacks_base.h \
	uvm_cbs.h \
	uvm_derived_callbacks.h \
	uvm_typed_callbacks.h \
	uvm_typeid.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_callback.cpp \
	uvm_callbacks_base.cpp \
	uvm_typeid.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libcb.la

libcb_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/cb

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
