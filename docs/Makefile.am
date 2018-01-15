include $(top_srcdir)/config/Make-rules

DOXYGEN = doxygen

DOXYFILE = uvmsc/doxygen/Doxyfile

DOC_FILES = \
	uvm-systemc-language-reference-manual.pdf \
	UVM_goes_Universal_-_Introducing_UVM_in_SystemC_-_DVCON_Europe_2015.pdf

## add documentation to distribution
EXTRA_DIST += \
	$(DOC_FILES)


%/Doxyfile: %/Doxyfile.in
	cd $(top_builddir) && $(SHELL) config.status docs/$@

install-data-local: $(DOXYFILE)
	@$(NORMAL_INSTALL)
	if test "$(realpath $(srcdir))" != "$(realpath $(DESTDIR)$(docdir))"; then \
	  $(mkinstalldirs) $(DESTDIR)$(docdir); \
	  for file in $(DOC_FILES); do \
	    $(INSTALL_DATA) -D $(srcdir)/$$file $(DESTDIR)$(docdir)/$$file; \
	  done; \
	fi
if HAVE_DOXYGEN
	$(mkinstalldirs) $(DESTDIR)$(docdir)/uvmsc/doxygen
	$(INSTALL_DATA) -D $(DOXYFILE) $(DESTDIR)$(docdir)/$(DOXYFILE)
	cd $(DESTDIR)$(docdir)/uvmsc/doxygen && $(DOXYGEN)
endif

uninstall-local:
	@$(NORMAL_UNINSTALL)
if HAVE_DOXYGEN
	rm -rf $(DESTDIR)$(docdir)/uvmsc/doxygen/html
	rm -rf $(DESTDIR)$(docdir)/uvmsc/doxygen/*tag
	rm -rf $(DESTDIR)$(docdir)/$(DOXYFILE)
endif
	if test "$(realpath $(srcdir))" != "$(realpath $(DESTDIR)$(docdir))"; then \
	  for file in $(DOC_FILES); do \
	    rm -f $(DESTDIR)$(docdir)/$$file; \
	  done; \
	  rm -rf $(DESTDIR)$(docdir); \
	fi

## Taf!
