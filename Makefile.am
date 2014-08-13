# -- Global settings --
AM_MAKEFLAGS		= --no-print-directory
AM_CFLAGS			= -I${top_srcdir}/lib -I${top_builddir}/lib
ACLOCAL_AMFLAGS		= -Im4

LDADD				= lib/libriemannpp.la

includedir			= ${prefix}/include/riemann
protodir			= ${includedir}/proto

VERSION				= @VERSION@${SNAPSHOT_VERSION}

# -- Libraries --
lib_LTLIBRARIES		= lib/libriemannpp.la

lib_libriemannpp_la_CFLAGS	= ${AM_CFLAGS}
lib_libriemannpp_la_LDFLAGS	= 
lib_libriemannpp_la_LIBADD	= -lprotobuf-c
lib_libriemannpp_ladir		= ${includedir}
lib_libriemannpp_la_HEADERS	=       \
	include/riemannpp/client.hpp    \
	include/riemannpp/event.hpp	    \
	include/riemannpp/message.hpp   \
	include/riemannpp/attribute.hpp	\
	include/riemannpp/query.hpp     \
	include/riemannpp/riemannpp.h
lib_libriemannpp_la_SOURCES =       \
	src/client.cpp                  \
	src/event.cpp                   \
	src/message.cpp                 \
	src/attribute.cpp               \
	src/query.cpp

pkgconfigdir			= $(libdir)/pkgconfig
pkgconfig_DATA			= riemannpp.pc

# -- Testcases --
if HAVE_CHECK
	UNIT_TESTS				= test/attribute_test test/client_test test/event_test test/message_test
	TESTS					= ${UNIT_TESTS}

	test/%_test: CFLAGS  += ${CHECK_CFLAGS}
	test/%_test: LDADD   += ${CHECK_LIBS} -ldl
	test/%_test: LDFLAGS += -no-install

	check_PROGRAMS			= ${TESTS}
endif

check_libriemannpp_srcs		= \
	test/catch.hpp		      \
	test/attribute_test.cpp	  \
	test/client_test.cpp	  \
	test/event_test.cpp	      \
	test/message_test.cpp

# -- Extra files to distribute --
EXTRA_DIST = README.md LICENSE          \
             riemannpp.pc               \
             ${check_libriemannpp_srcs} \
             m4/.placeholder            \
             ${src_riemannpp_EXTRA_DIST}
