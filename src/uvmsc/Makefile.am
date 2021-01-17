include $(top_srcdir)/config/Make-rules

SUBDIRS = 
H_FILES =
NO_H_FILES =
CXX_FILES =
INCDIRS =
LIBADD =

# include file lists for sub-directories
include base/files.am
include cb/files.am
include comps/files.am
include conf/files.am
include dap/files.am
include dpi/files.am
include factory/files.am
include macros/files.am
include misc/files.am
include phasing/files.am
include policy/files.am
include print/files.am
include reg/files.am
include report/files.am
include seq/files.am
include tlm1/files.am
	
localincludedir = $(includedir)/uvmsc
nobase_localinclude_HEADERS = $(H_FILES)

noinst_LTLIBRARIES = libuvm-systemc.la

libuvm_systemc_la_SOURCES = $(NO_H_FILES) $(CXX_FILES)

libuvm_systemc_la_LIBADD = $(LIBADD)

uninstall-hook:
	test ! -d "$(localincludedir)" || ( set -e ; cd "$(localincludedir)"; \
		for dir in $(INCDIRS) ; do test ! -d $$dir || rmdir $$dir ; done ; \
		cd - ; rmdir "$(localincludedir)" )

## Taf!
