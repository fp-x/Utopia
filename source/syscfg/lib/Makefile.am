AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -D_ANSC_LITTLE_ENDIAN_
AM_CFLAGS += -fPIC
AM_CFLAGS += -DSC_POSIX_SEM
AM_LDFLAGS = -L/var/tmp/pc-rdkb/lib
AM_LDFLAGS += -lpthread
AM_LDFLAGS += -lz

AM_CPPFLAGS = -Wall -Werror -fPIC
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu

lib_LTLIBRARIES = libsyscfg.la
libsyscfg_la_CPPFLAGS = -I$(top_srcdir)/source/include $(CPPFLAGS)
libsyscfg_la_SOURCES = syscfg_lib.c syscfg_mtd.c
libsyscfg_la_LDFLAGS =  -L/var/tmp/pc-rdkb/lib -lpthread -lz
