MAINTAINERCLEANFILES = Makefile.in

INCLUDES = \
-I$(top_srcdir) \
-I$(top_srcdir)/src/bin \
@TMDB_CFLAGS@ \
@CURL_CFLAGS@

bin_PROGRAMS = tmdbclt

tmdbclt_LDADD = \
@TMDB_LIBS@ \
@CURL_LIBS@

tmdbclt_CFLAGS = -Wall -Werror

tmdbclt_SOURCES = main.c \
env.c \
env.h \
print_results.c \
print_results.h \
utils.c \
utils.h \
colors.h
