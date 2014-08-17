# For using custom m4 macros
ACLOCAL_AMFLAGS = -I m4

# Compiler build flags
AM_CPPFLAGS = -I${top_srcdir}/src ${RIEMANN_CLIENT_CFLAGS}

# Build rules for riemannpp library
pkginclude_HEADERS = \
	src/riemannpp/riemannpp.hpp

lib_LTLIBRARIES = \
	src/riemannpp/libriemannpp.la

src_riemannpp_libriemannpp_la_SOURCES = \
	src/riemannpp/client.hpp    \
	src/riemannpp/client.cpp    \
	src/riemannpp/event.hpp     \
	src/riemannpp/event.cpp     \
	src/riemannpp/message.hpp   \
	src/riemannpp/message.cpp   \
	src/riemannpp/attribute.hpp \
	src/riemannpp/attribute.cpp \
	src/riemannpp/query.hpp     \
	src/riemannpp/query.cpp     \
	src/riemannpp/exception.hpp
src_riemannpp_libriemannpp_la_LDFLAGS = -version-info 0:0:0
src_riemannpp_libriemannpp_la_LIBADD = $(RIEMANN_CLIENT_LIBS)

# Build rules for pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = riemannpp.pc

# Build rules for client program
bin_PROGRAMS = \
	src/client/riemannpp

src_client_riemannpp_SOURCES = \
	src/client/options.hpp \
	src/client/options.cpp \
	src/client/riemannpp.cpp
src_client_riemannpp_CPPFLAGS = -I${top_srcdir}/src ${RIEMANN_CLIENT_CFLAGS} $(BOOST_CPPFLAGS)
src_client_riemannpp_LDFLAGS = $(BOOST_LDFLAGS)
src_client_riemannpp_LDADD = $(top_builddir)/src/riemannpp/libriemannpp.la $(RIEMANN_CLIENT_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(LDADD)

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
test_riemannpp_test_CFLAGS = -I$(top_srcdir)/src $(RIEMANN_CLIENT_CFLAGS)
test_riemannpp_test_LDADD = $(top_builddir)/src/riemannpp/libriemannpp.la $(LDADD)

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

# Nonstandard package files for distribution
EXTRA_DIST = \
	README.md \
	LICENSE \
	autogen.sh \
	riemannpp.pc

include Makefile.am.coverage
