include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_bottomup_phase.h \
	uvm_common_phases.h \
	uvm_domain.h \
	uvm_objection.h \
	uvm_phase.h \
	uvm_phase_queue.h \
	uvm_phasing.h \
	uvm_process.h \
	uvm_process_phase.h \
	uvm_runtime_phases.h \
	uvm_topdown_phase.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_bottomup_phase.cpp \
	uvm_common_phases.cpp \
	uvm_domain.cpp \
	uvm_objection.cpp \
	uvm_phase.cpp \
	uvm_process_phase.cpp \
	uvm_runtime_phases.cpp \
	uvm_topdown_phase.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libphasing.la

libphasing_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/phasing

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
