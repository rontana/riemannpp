# -*- Autoconf -*-

AC_INIT([riemannpp], [0.1.0], [christopher.john.gilbert@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz no-dist-gzip])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([no])])

AC_CONFIG_SRCDIR([src/client.cpp])
AC_CONFIG_HEADERS([include/riemannpp/client.hpp])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CXX

LT_INIT([shared])

AC_CHECK_HEADERS([arpa/inet.h netdb.h stdlib.h sys/socket.h])
AC_CHECK_FUNCS([memset socket strcasecmp strchr strdup strerror])
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_TYPE_INT64_T
AC_TYPE_SSIZE_T

# Check for pkg-config-enabled libraries
PKG_PROG_PKG_CONFIG

HAVE_RIEMANN_CLIENT=yes
PKG_CHECK_MODULES(RIEMANN_CLIENT, riemann-client >= 0.26,,[HAVE_RIEMANN_CLIENT="no"])

AM_CONDITIONAL([HAVE_RIEMANN_CLIENT], [test x$HAVE_RIEMANN_CLIENT != xno])

AC_DEFINE_UNQUOTED([HAVE_RIEMANN_CLIENT],
  `if test x$HAVE_RIEMANN_CLIENT != xno; then echo 1; else echo 0; fi`,
  [Define when riemann-client is available])

AC_CONFIG_FILES([Makefile riemannpp.pc])
AC_OUTPUT
