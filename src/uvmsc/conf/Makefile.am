include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_conf.h \
	uvm_config_db.h \
	uvm_config_db_options.h \
	uvm_object_string_pool.h \
	uvm_queue.h \
	uvm_resource.h \
	uvm_resource_base.h \
	uvm_resource_converter.h \
	uvm_resource_db.h \
	uvm_resource_db_options.h \
	uvm_resource_options.h \
	uvm_resource_pool.h \
	uvm_resource_types.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_config_db_options.cpp \
	uvm_resource_base.cpp \
	uvm_resource_db_options.cpp \
	uvm_resource_options.cpp \
	uvm_resource_pool.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libconf.la

libconf_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/conf

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
