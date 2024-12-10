# MODIFIED VERSION OF LIBRARY
# 
# This is a modified version of the original libmatheval library, which
# has had the test suite removed (for now), so that it no longer
# requires Guile in order to compile. This was done to make it easier to
# use libmatheval on systems where it may be difficult to install extra
# system-level packages, in particular various versions of such
# packages, such as on a university's High Performance Computing system.
# 
# [Michael Carley, 2024]
# 
# Copyright (C) 1999, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011,
# 2012, 2013 Free Software Foundation, Inc.
#
# This file is part of GNU libmatheval
#
# GNU libmatheval is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# GNU libmatheval is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU libmatheval.  If not, see
# <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = -I m4

AUX_DIST = $(ac_aux_dir)/compile $(ac_aux_dir)/config.guess		\
$(ac_aux_dir)/config.sub $(ac_aux_dir)/depcomp $(ac_aux_dir)/install-sh	\
$(ac_aux_dir)/ltmain.sh $(ac_aux_dir)/mdate-sh $(ac_aux_dir)/missing	\
$(ac_aux_dir)/mkinstalldirs $(ac_aux_dir)/texinfo.tex

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure config.h.in	\
config.log config.status stamp-h.in $(AUX_DIST)

SUBDIRS = lib

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libmatheval.pc

.PHONY: beauty dist-hook

beauty:
	-for dir in lib ; do cd $$dir; $(MAKE) $@; cd ..; done

dist-hook:
	for file in $(AUX_DIST); do \
	  cp $$file $(distdir)/$$file; \
	done
