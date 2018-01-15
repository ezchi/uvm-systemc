include $(top_srcdir)/config/Make-rules

H_FILES = \
	uvm_seq.h \
	uvm_sequence.h \
	uvm_sequence_base.h \
	uvm_sequence_item.h \
	uvm_sequencer.h \
	uvm_sequencer_base.h \
	uvm_sequencer_ifs.h \
	uvm_sequencer_param_base.h

NO_H_FILES = 

noinst_HEADERS = $(H_FILES)

CXX_FILES = \
	uvm_sequence_base.cpp \
	uvm_sequence_item.cpp \
	uvm_sequencer_base.cpp 

NO_CXX_FILES =

noinst_LTLIBRARIES = libseq.la

libseq_la_SOURCES = $(H_FILES) $(NO_H_FILES) $(CXX_FILES)

INCLUDE_DIR = $(prefix)/include/uvmsc/seq

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
