include $(top_srcdir)/config/Make-rules.examples

SUBDIRS = \
	uvmsc

install-data-local:
	@$(NORMAL_INSTALL)
	if test "$(realpath $(srcdir))" != "$(realpath $(DESTDIR)$(examplesdir))"; then \
	  $(mkinstalldirs) $(DESTDIR)$(examplesdir); \
	fi

uninstall-local:
	@$(NORMAL_UNINSTALL)
	if test "$(realpath $(srcdir))" != "$(realpath $(DESTDIR)$(examplesdir))"; then \
	  rmdir $(DESTDIR)$(examplesdir); \
	fi

## Taf!
