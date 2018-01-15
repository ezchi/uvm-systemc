include $(top_srcdir)/config/Make-rules

SUBDIRS = \
	base \
	cb \
	comps \
	conf \
	dpi \
	factory \
	macros \
	misc \
	phasing \
	policy \
	print \
	reg \
	report \
	seq \
	tlm1 
	
lib_LTLIBRARIES = libuvm-systemc.la

libuvm_systemc_ladir = 

libuvm_systemc_la_SOURCES = 

libuvm_systemc_la_LIBADD = \
	base/libbase.la \
	cb/libcb.la \
	comps/libcomps.la \
	conf/libconf.la \
	dpi/libdpi.la \
	factory/libfactory.la \
	misc/libmisc.la \
	phasing/libphasing.la \
	policy/libpolicy.la \
	print/libprint.la \
	reg/libreg.la \
	report/libreport.la \
	seq/libseq.la

libuvm_systemc_la_LDFLAGS = -release $(PACKAGE_VERSION) -L$(libdir)

# dummy C++ source file to force C++ linking
nodist_EXTRA_libuvm_systemc_la_SOURCES = dummy.cpp

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = uvm-systemc.pc

INCLUDE_DIR = $(prefix)/include/uvmsc

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(INCLUDE_DIR)

uninstall-local: uninstall-libLTLIBRARIES uninstall-pkgconfigDATA
	@$(NORMAL_UNINSTALL)
	-rmdir $(DESTDIR)$(INCLUDE_DIR)
	-rmdir $(DESTDIR)$(pkgconfigdir)
	-rmdir $(DESTDIR)$(libdir)

## Taf!
