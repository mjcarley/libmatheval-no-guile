# Copyright (C) 1999, 2002, 2003  Free Software Foundation, Inc.
#
# This file is part of GNU libmatheval
#
# GNU libmatheval is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2, or (at
# your option) any later version.
#
# GNU libmatheval is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with program; see the file COPYING. If not, write to the Free
# Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

AUX_DIST = $(ac_aux_dir)/compile $(ac_aux_dir)/config.guess		\
$(ac_aux_dir)/config.sub $(ac_aux_dir)/depcomp $(ac_aux_dir)/install-sh	\
$(ac_aux_dir)/ltmain.sh $(ac_aux_dir)/mdate-sh $(ac_aux_dir)/missing	\
$(ac_aux_dir)/mkinstalldirs $(ac_aux_dir)/texinfo.tex

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure config.h.in	\
config.log config.status stamp-h.in $(AUX_DIST)

SUBDIRS = doc lib tests

.PHONY: beauty dist-hook

beauty:
	-for dir in lib tests; do cd $$dir; $(MAKE) $@; cd ..; done

dist-hook:
	for file in $(AUX_DIST); do \
	  cp $$file $(distdir)/$$file; \
	done
