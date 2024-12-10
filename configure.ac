dnl MODIFIED VERSION OF LIBRARY
dnl 
dnl This is a modified version of the original libmatheval library, which
dnl has had the test suite removed (for now), so that it no longer
dnl requires Guile in order to compile. This was done to make it easier to
dnl use libmatheval on systems where it may be difficult to install extra
dnl system-level packages, in particular various versions of such
dnl packages, such as on a university's High Performance Computing system.
dnl 
dnl [Michael Carley, 2024]
dnl 
dnl Copyright (C) 1999, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011,
dnl 2012, 2013 Free Software Foundation, Inc.
dnl
dnl This file is part of GNU libmatheval
dnl
dnl GNU libmatheval is free software: you can redistribute it and/or
dnl modify it under the terms of the GNU General Public License as
dnl published by the Free Software Foundation, either version 3 of the
dnl License, or (at your option) any later version.
dnl
dnl GNU libmatheval is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of 
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with GNU libmatheval.  If not, see
dnl <http://www.gnu.org/licenses/>.

dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.53)
AC_INIT([libmatheval],[1.1.11],[codes@paraffinalia.co.uk])
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST([ac_aux_dir])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([configure.ac])
AM_CONFIG_HEADER([config.h])

dnl Initialize the test suite.
#AC_CONFIG_TESTDIR([tests])
#AC_CONFIG_FILES([tests/matheval.sh], [chmod +x tests/matheval.sh])
#AC_CONFIG_FILES([tests/Makefile])

dnl Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
AC_PROG_CPP
AC_PROG_INSTALL
AM_PROG_LEX
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
AC_PROG_YACC
AM_MISSING_PROG([AUTOM4TE], [autom4te])

dnl Checks for libraries.

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([math.h strings.h stddef.h stdint.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_CHECK_FUNCS([bzero memset], [break])

dnl Additional Guile feature checks.
AC_CONFIG_FILES([Makefile lib/Makefile])
AC_OUTPUT(libmatheval.pc)
