AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -D_ANSC_LITTLE_ENDIAN_
AM_LDFLAGS = -lpthread
AM_LDFLAGS += -lz

AM_CPPFLAGS = -Wall -Werror
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu
bin_PROGRAMS = GenFWLog
GenFWLog_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/source/include $(CPPFLAGS)
GenFWLog_SOURCES = GenFWLog.c
GenFWLog_LDFLAGS =  -L/var/tmp/pc-rdkb/lib -lpthread -lz
GenFWLog_LDADD = $(top_builddir)/source/syscfg/lib/libsyscfg.la \
                 $(top_builddir)/source/sysevent/lib/libsysevent.la \
                 $(top_builddir)/source/ulog/libulog.la
