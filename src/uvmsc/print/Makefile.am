include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_line_printer.h \
	uvm_print.h \
	uvm_printer.h \
	uvm_printer_globals.h \
	uvm_printer_knobs.h \
	uvm_table_printer.h \
	uvm_tree_printer.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_printer.cpp \
	uvm_printer_globals.cpp \
	uvm_table_printer.cpp \
	uvm_tree_printer.cpp

NO_CXX_FILES =

noinst_LTLIBRARIES = libprint.la

libprint_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/print

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
