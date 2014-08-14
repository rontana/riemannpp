# For using custom m4 macros
ACLOCAL_AMFLAGS = -I m4

# Nonstandard package files for distribution
EXTRA_DIST = autogen.sh

# Compiler build flags
AM_CPPFLAGS = -I${top_srcdir}/src

# Build rules for riemannpp library
pkginclude_HEADERS = \
  src/riemannpp/riemannpp.hpp

lib_LTLIBRARIES = \
	src/riemannpp/libriemannpp.la

src_riemannpp_libriemannpp_la_SOURCES = \
	lib/riemannpp/client.hpp    \
	lib/riemannpp/client.cpp    \
	lib/riemannpp/event.hpp     \
	lib/riemannpp/event.cpp     \
	lib/riemannpp/message.hpp   \
	lib/riemannpp/message.cpp   \
	lib/riemannpp/attribute.hpp \
	lib/riemannpp/attribute.cpp \
	lib/riemannpp/query.hpp     \
	lib/riemannpp/query.cpp     \
	lib/riemannpp/exception.hpp
src_riemannpp_libriemannpp_la_CPPFLAGS = $(RIEMANNPP_CPPFLAGS)
src_riemannpp_libriemannpp_la_CXXFLAGS = $(RIEMANNPP_CXXFLAGS)
src_riemannpp_libriemannpp_la_LDFLAGS = $(RIEMANNPP_LDFLAGS)
src_riemannpp_libriemannpp_la_LIBADD = $(RIEMANNPP_LIBS)

# Build rules for pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = riemannpp.pc

# Build rules for tests.
# TESTS_ENVIRONMENT: Set environment variables for the test run
# TESTS: Define programs run automatically by "make check"
# UNIT_TESTS: Define programs run automatically by "make check-unit-tests"
# check_PROGRAMS: Define programs built by "make check" but not necessarily run
TESTS_ENVIRONMENT=
TESTS=
UNIT_TESTS=
check_PROGRAMS=

# Define unit tests with gtest
UNIT_TESTS += test/riemannpp_test
check_PROGRAMS += test/riemannpp_test
test_riemannpp_test_SOURCES = \
	test/riemannpp_test.cpp \
	test/attribute_test.cpp \
	test/client_test.cpp \
	test/event_test.cpp \
	test/message_test.cpp
test_riemannpp_test_CPPFLAGS = -I$(top_srcdir)/src $(RIEMANNPP_CPPFLAGS)
test_riemannpp_test_CXXFLAGS = $(RIEMANNPP_CXXFLAGS)
test_riemannpp_test_LDFLAGS = $(RIEMANNPP_LDFLAGS)
test_riemannpp_test_LDADD = $(top_builddir)/src/riemannpp/libriemannpp.la

TESTS += $(UNIT_TESTS)

TESTS_ENVIRONMENT_WITH_VALGRIND="libtool --mode=execute valgrind --leak-check=full"

.PHONY: check-with-valgrind
check-with-valgrind:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS_ENVIRONMENT=$(TESTS_ENVIRONMENT_WITH_VALGRIND)

.PHONY: check-unit-tests
check-unit-tests:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS=$(UNIT_TESTS)

.PHONY: check-unit-tests-with-valgrind
check-unit-tests-with-valgrind:
	$(MAKE) $(AM_MAKEFLAGS) check TESTS=$(UNIT_TESTS) TESTS_ENVIRONMENT=$(TESTS_ENVIRONMENT_WITH_VALGRIND)

include Makefile.am.coverage

# Extra files to distribute
EXTRA_DIST = README.md LICENSE          \
             riemannpp.pc               \
             ${check_libriemannpp_srcs} \
             m4/.placeholder            \
             ${src_riemannpp_EXTRA_DIST}
