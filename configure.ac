AC_INIT(tmdbclt, 0.1.0.0, top4e@top4e.com)
AC_PREREQ([2.60])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_GNU_SOURCE
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE(1.6 dist-bzip2)
AM_CONFIG_HEADER(config.h)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])
define([AC_LIBTOOL_LANG_GCJ_CONFIG], [:])
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])
AC_PROG_LIBTOOL

VMAJ=`echo $PACKAGE_VERSION | awk -F. '{printf("%s", $1);}'`
VMIN=`echo $PACKAGE_VERSION | awk -F. '{printf("%s", $2);}'`
VMIC=`echo $PACKAGE_VERSION | awk -F. '{printf("%s", $3);}'`
SNAP=`echo $PACKAGE_VERSION | awk -F. '{printf("%s", $4);}'`
version_info=`expr $VMAJ + $VMIN`":$VMIC:$VMIN"
AC_SUBST(VMAJ)
AC_SUBST(version_info)

AC_C_BIGENDIAN
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_C_CONST
AC_FUNC_ALLOCA

PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([TMDB], [tmdb])

AC_OUTPUT([
Makefile
src/Makefile
src/bin/Makefile
])

cat << EOF

tmdbclt configured with:

Flags:
   CFLAGS.....(C): $CFLAGS
   LDFLAGS...(LD): $LDFLAGS

Installation:
   PREFIX..............: $prefix
EOF

cat << EOF2

Now type 'make' ('gmake' on some systems) to compile tmdbclt, if it
builds successfully then you can 'make install', acquiring required
permissions with 'su' or 'sudo'.

EOF2
