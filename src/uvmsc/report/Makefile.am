include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_default_report_server.h \
	uvm_report.h \
	uvm_report_catcher.h \
	uvm_report_catcher_data.h \
	uvm_report_handler.h \
	uvm_report_message.h \
	uvm_report_object.h \
	uvm_report_server.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_default_report_server.cpp \
	uvm_report_catcher.cpp \
	uvm_report_catcher_data.cpp \
	uvm_report_handler.cpp \
	uvm_report_message.cpp \
	uvm_report_object.cpp \
	uvm_report_server.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libreport.la

libreport_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/report

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
