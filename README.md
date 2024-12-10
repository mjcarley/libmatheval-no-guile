# Lightweight libmatheval without Guile

This is a fork of the original GNU libmatheval library (see original
copyright below) which has had the test code removed so that Guile is
no longer needed for compilation. The requirement for Guile was an
inconvenience in using the library on systems where Guile had to be
especially requested and/or where only the more recent version was
available, and not the older implementation which libmatheval used for
its test code. I may at some point implement a test suite which does
not use Guile. 

# Installation

Installation requires the autoconf suite and has been updated to use
the current standards:

`. autogen.sh`

followed by 

`./configure ...`

should configure the code. `make` and `make install` will then install
the library.

# Original GNU copyright notice

Copyright (C) 1999, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011,
2012, 2013 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification, are
permitted in any medium without royalty provided the copyright notice
and this notice are preserved.


# WHAT IS IT?

GNU libmatheval is a library which contains several procedures that make
it possible to create an in-memory tree from the string representation
of a mathematical function over single or multiple variables. This tree
can be used later to evaluate a function for specified variable values,
to create a corresponding tree for the function derivative over a
specified variable, or to write a textual tree representation to a
specified string. The library exposes C and Fortran 77 interfaces.


# REQUIREMENTS

GNU autotools are employed for this project, so library should be
compilable on any UNIX variant.  Still, compilation is verified on
NetBSD 1.6 and Slackware GNU/Linux 9.1 only.  Library (actually, test
suite) requires Guile to be present.


# INSTALLATION

For detailed GNU libmatheval installation instructions, see INSTALL
document.  For impatient, simple sequence of:

`./configure`

`make`

`make install`

will do the job.


# DOCUMENTATION

Documentation for GNU libmatheval is available as a Texinfo manual.
After installation, issue command:
  `info libmatheval`
to access this document.


# BUGS

Please report bugs and eventually send patches to
<bug-libmatheval@gnu.org> mailing list.
