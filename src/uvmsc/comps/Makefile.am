include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_agent.h \
	uvm_comps.h \
	uvm_driver.h \
	uvm_env.h \
	uvm_monitor.h \
	uvm_scoreboard.h \
	uvm_subscriber.h \
	uvm_test.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_agent.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libcomps.la

libcomps_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/comps

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
