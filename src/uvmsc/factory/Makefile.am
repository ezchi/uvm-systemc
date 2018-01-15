include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_component_registry.h \
	uvm_default_factory.h \
	uvm_fact_reg.h \
	uvm_factory.h \
	uvm_factory_override.h \
	uvm_object_registry.h \
	uvm_object_wrapper.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_default_factory.cpp \
	uvm_factory_override.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libfactory.la

libfactory_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/factory

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
