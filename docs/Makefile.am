include $(top_srcdir)/config/Make-rules

DOXYGEN = doxygen

DOC_FILES = \
	uvm-systemc-language-reference-manual.pdf \
	UVM_goes_Universal_-_Introducing_UVM_in_SystemC_-_DVCON_Europe_2015.pdf

## ****************************************************************************

## install documentation?
if SEPARATE_INSTALL_TREE

nobase_doc_DATA = \
    $(DOC_FILES)

## Install, but do not distribute Doxygen configuration
nobase_doc_DATA += \
				   uvmsc/doxygen/Doxyfile

DOCDIRS = \
		  uvmsc/doxygen \
		  uvmsc

uninstall-hook:
	test ! -d "$(docdir)" || ( set -e ; cd "$(docdir)" ; \
		for dir in $(DOCDIRS) ; do test ! -d $$dir || rmdir $$dir ; done ; \
		cd - ; rmdir --ignore-fail-on-non-empty "$(docdir)" )

endif # SEPARATE_INSTALL_TREE


## add documentation to distribution
EXTRA_DIST += \
	$(DOC_FILES)

doxygen: uvmsc/doxygen/Doxyfile
	@(cd uvmsc/doxygen && $(DOXYGEN))

%/Doxyfile: %/Doxyfile.in
	cd $(top_builddir) && $(SHELL) config.status docs/$@

## Taf!
