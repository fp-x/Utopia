AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -D_ANSC_LITTLE_ENDIAN_
AM_LDFLAGS = -L/var/tmp/pc-rdkb/lib

AM_CPPFLAGS = -Wall -Werror
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu

bin_PROGRAMS = utctx_cmd
utctx_cmd_CPPFLAGS = -I$(top_srcdir)/source/include -I$(top_srcdir)/source/include/utctx $(CPPFLAGS)
utctx_cmd_LDFLAGS = -lpthread
utctx_cmd_SOURCES = utctx_cmd.c
utctx_cmd_LDADD = $(top_builddir)/source/utctx/lib/libutctx.la

