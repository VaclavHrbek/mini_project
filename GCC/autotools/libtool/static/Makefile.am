ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libmy_lib.la
libmy_lib_la_SOURCES = s_library.c s_library.h

bin_PROGRAMS = run
run_SOURCES = main.c
run_LDADD = libmy_lib.la s_library.h

clean-local: distclean
	rm -rf aclocal.m4 ar-lib autom4te.cache/ compile config.* configure depcomp .deps/ install-sh ltmain.sh m4/ Makefile.in missing build-aux/
