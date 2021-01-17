include $(top_srcdir)/config/Make-rules

SUBDIRS = \
	uvmsc \
	.

H_FILES = \
	uvm \
	uvm.h

nobase_include_HEADERS = $(H_FILES)

libarchdir = $(libdir)$(LIB_ARCH_SUFFIX)
libarch_LTLIBRARIES = libuvm-systemc.la

pkgconfigdir = $(libarchdir)/pkgconfig
pkgconfig_DATA = uvmsc/uvm-systemc.pc

# no own sources here
libuvm_systemc_la_SOURCES =

# dummy C++ source to cause C++ linking
nodist_EXTRA_libuvm_systemc_la_SOURCES = uvmsc_nonexistent.cpp

# add main library
libuvm_systemc_la_LIBADD = uvmsc/libuvm-systemc.la

libuvm_systemc_la_LDFLAGS = $(EXTRA_LDFLAGS) -release $(VERSION)

uninstall-hook:
	test ! -d "$(includedir)"   || rmdir --ignore-fail-on-non-empty "$(includedir)"
	test ! -d "$(pkgconfigdir)" || rmdir --ignore-fail-on-non-empty "$(pkgconfigdir)"
	test ! -d "$(libarchdir)"   || rmdir --ignore-fail-on-non-empty "$(libarchdir)"


## Taf!
