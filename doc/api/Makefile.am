#
# Copyright (c) 2002, 2003, 2005,  Theodore A. Roth
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
# NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Author: Theodore A. Roth <troth@verinet.com>
#
# Contributors:
#
# $Id$
#
MAINTAINERCLEANFILES = Makefile.in stamp-vti

CLEANFILES           = *.html *.pdf *.ma *.mas \
                       malloc-std.png malloc-x1.png malloc-x2.png \
                       *.eps fix_png \
                       doxygen.config main_page.dox doxygen-pdf.config

EXTRA_DIST           = dox.css dox_html_header dox_html_footer \
                       doxygen.config.in \
                       main_page.dox.in \
                       assembler.dox \
                       inline_asm.dox \
                       interrupts.dox \
                       acknowledge.dox \
                       malloc.dox \
                       $(IMAGE_SRC) \
                       sections.dox \
                       sfr.dox \
                       tools-install.dox \
                       using-avrprog.dox \
                       using-tools.dox \
                       faq.dox \
                       bench.dox \
                       bench-libc.dox \
                       bench-libm.dox \
                       porting.dox \
                       optimize.dox \
                       overview.dox \
                       pgmspace.dox \
                       library.dox \
                       gen-vectortable-dox.sh \
                       isrs-to-dox.py \
                       mcus-to-isrs.sh \
                       vectortable.dox

SUFFIXES             = .pdf .fig .png .eps

DOC_INST_DIR         = @DOC_INST_DIR@

USER_MANUAL          = @AVR_LIBC_USER_MANUAL@

DEMO_LIBS            = $(abs_top_builddir)/avr/lib/avr4/exit.o
DEMO_LIBS            += $(abs_top_builddir)/avr/devices/atmega8/crtatmega8.o
# As avr-gcc must have been installed already, we can reference its
# library by a -l option.
DEMO_LIBS            += -lgcc
DEMO_INC             = -I$(abs_top_srcdir)/include

# All demo projects where we need to run "make dox" beforehand.
DEMOS                = demo largedemo stdiodemo

all-local: html pdf

# Before we can build the dox, we need to build the demo project so that some
# included files get generated.
demo:
	if test -n "$(DEMO_LIBS)" ; then \
		NODEFLIBS="-nostartfiles -nodefaultlibs" ; \
	fi; \
	cd $(top_srcdir)/doc/examples/demo && \
		${MAKE} DEFS="$(DEMO_INC)"  \
			LIBS="$$NODEFLIBS $(DEMO_LIBS)" all

# Generate EPS files from JPG for demos.
demodox:
	for demo in $(DEMOS); do \
	  ( cd $(top_srcdir)/doc/examples/$$demo && \
	  ${MAKE} dox ); \
	done

# images for inclusion in HTML and LaTeX documents

FIG2DEV= fig2dev

.fig.eps:
	$(FIG2DEV) -L eps $< $@

.fig.png:
	$(FIG2DEV) -L png $< $@

IMAGE_SRC=	malloc-std.fig malloc-x1.fig malloc-x2.fig \
		avr-libc-logo.png avr-libc-logo.png

IMAGE_PNG=	$(IMAGE_SRC:.fig=.png)

IMAGE_EPS=	$(IMAGE_SRC:.fig=.eps)

# Rule for generating html output.
html: demo demodox fix_png $(TARGET_DOX_HTML)

# Make the background color of the png's transparent.
fix_png: $(wildcard $(USER_MANUAL)/*.png) latex_src/refman.tex
	cd $(USER_MANUAL) || exit 0; \
	for png in *.png; do \
		echo "Fixing transparency for $$png"; \
		$(PNGTOPNM) $$png > tmp.pnm; \
		$(PNMTOPNG) -transparent rgb:ff/ff/ff tmp.pnm > $$png && rm tmp.pnm; \
	done
	echo timestamp > fix_png

# Rule for generating PDF output
pdf: demo demodox $(TARGET_DOX_PDF)

# General rule for installing documentation
install-data-local: $(INSTALL_DOX_HTML) $(INSTALL_DOX_PDF) \
	$(INSTALL_DOX_MAN)

uninstall-local:
	rm -rf $(DOC_INST_DIR)

clean-local:
	rm -rf $(USER_MANUAL) latex_src man
	for demo in $(DEMOS); do \
	  ( cd $(top_srcdir)/doc/examples/$$demo && \
	  ${MAKE} clean ) ; \
	done

#
# Rules for generating documentation with doxygen
#

#
# The sed magic below does the following:
#
# It bumps the subsection level that is to be displayed in the TOC.
# For Postscript output, only \page and \section headings will be
# displayed, while the PDF document will also show \subsection so the
# browsable index in the PDF file will provide a good help to the
# user.
#
# The magic around TabularC replaces doxygen's own tabular environment
# (named TabularC) by an explicit call to longtable in the document
# that describes the vector names, so the rather long table can be
# split across multiple pages.  Note that there are some nasty things
# going on here: the string "Vector Name" in the table heading is used
# as a magic string in order to replace the \\ at the end of the table
# heading by \endhead so longtable will know what heading to repeat in
# table continuations.
#
# The last sed command replaces the \renewcommand for \cftchapfont and
# \cftchappagefont, respectively, by a \newcommand, to fix a LaTeX
# error.

latex_src/refman.tex: doxygen.config $(IMAGE_EPS) $(IMAGE_PNG) main_page.dox
	doxygen doxygen.config
	cp $(top_srcdir)/doc/api/avr-libc-logo.png $(AVR_LIBC_USER_MANUAL)/
	cp $(top_srcdir)/doc/api/avr-libc-logo-large.png latex_src/

# Add contents of toplevel LICENSE to main page
main_page.dox: main_page.dox.in
	cat $(srcdir)/main_page.dox.in > main_page.dox
	cat $(top_srcdir)/LICENSE >> main_page.dox
	echo '\endverbatim' >> main_page.dox
	echo '*/' >> main_page.dox

#doxygen.config: doxygen.config.in $(top_srcdir)/stamp-h1
doxygen.config: doxygen.config.in
	sed \
	-e 's,[@]VERSION[@],$(VERSION),g' \
	-e 's,[@]top_srcdir[@],$(top_srcdir),g' \
	-e 's,[@]top_builddir[@],$(top_builddir),g' \
	-e 's,[@]AVR_LIBC_USER_MANUAL[@],$(AVR_LIBC_USER_MANUAL),g' \
	-e 's,[@]srcdir[@],$(srcdir),g' \
	< $(srcdir)/doxygen.config.in > doxygen.config ||\
	{ rm -f doxygen.config; exit 1; }

# XXX currently, HTML and LaTeX documentation will always be built
# together.  HTML doesn't need any postprocessing, while latex is only
# a prerequisite for ps.
dox-html: demo demodox fix_png $(USER_MANUAL)/index.html

$(USER_MANUAL)/index.html: latex_src/refman.tex

dox-pdf: $(USER_MANUAL).pdf

$(USER_MANUAL).pdf: latex_src/refman.tex
	cd latex_src && ${MAKE} refman.pdf
	cp latex_src/refman.pdf $(USER_MANUAL).pdf

# Install rules for the various documentation parts.  The actual
# access to those rules is from the install-data-local target above,
# where the toplevel configure decides which of them will become a
# prerequisite of install-data-local.
install-dox-html: dox-html
	$(mkinstalldirs) $(DOC_INST_DIR)/$(USER_MANUAL)
	@list='$(wildcard $(USER_MANUAL)/*.html $(USER_MANUAL)/*.css \
	                  $(USER_MANUAL)/*.jpg $(USER_MANUAL)/*.png)'; \
	for file in $$list ; do \
	  echo " $(INSTALL_DATA) $$file $(DOC_INST_DIR)/$$file"; \
	  $(INSTALL_DATA) $$file $(DOC_INST_DIR)/$$file; \
	done

install-dox-pdf: dox-pdf
	$(mkinstalldirs) $(DOC_INST_DIR)
	$(INSTALL_DATA) $(USER_MANUAL).pdf $(DOC_INST_DIR)/$(USER_MANUAL).pdf

install-dox-man: dox-html
	$(mkinstalldirs) $(DESTDIR)$(mandir)/man3
	$(INSTALL_DATA) man/man3/*.3 $(DESTDIR)$(mandir)/man3

.PHONY: html latex pdf demo demodox \
	dox-html dox-pdf install-pdf install-html \
	install-dox-html install-dox-pdf \
	install-dox-man
