# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2006 - INRIA - Sylvestre LEDRU
#
# This file is distributed under the same license as the Scilab package.


SPREADSHEET_C_SOURCES = src/c/xls.c

RIPOLE_SOURCES = src/c/ripole/olestream-unwrap.c \
src/c/ripole/pldstr.c \
src/c/ripole/ole.c \
src/c/ripole/bytedecoders.c \
src/c/ripole/logger.c \
src/c/ripole/ripole.c \
src/c/ripole/bt-int.c


GATEWAY_C_SOURCES = sci_gateway/c/gw_spreadsheet.c \
sci_gateway/c/sci_xls_read.c \
sci_gateway/c/sci_xls_open.c

libscispreadsheet_la_CFLAGS=  	-I$(srcdir)/includes/ \
				-I$(srcdir)/src/c/ \
				-I$(srcdir)/src/c/ripole \
				-I$(top_srcdir)/libs/MALLOC/includes/ \
				-I$(top_srcdir)/modules/output_stream/includes \
				-I$(top_srcdir)/modules/io/includes \
				-I$(top_srcdir)/modules/api_scilab/includes \
				-I$(top_srcdir)/modules/fileio/includes

pkglib_LTLIBRARIES = libscispreadsheet.la
noinst_LTLIBRARIES = libscispreadsheet-algo.la

libscispreadsheet_la_LDFLAGS = -version-number $(SCILAB_LIBRARY_VERSION)

libscispreadsheet_algo_la_SOURCES = $(SPREADSHEET_C_SOURCES) $(RIPOLE_SOURCES)
libscispreadsheet_la_SOURCES = $(GATEWAY_C_SOURCES)
libscispreadsheet_algo_la_CFLAGS = $(libscispreadsheet_la_CFLAGS)

# For the code check (splint)
CHECK_SRC= $(SPREADSHEET_C_SOURCES) $(GATEWAY_C_SOURCES) $(RIPOLE_SOURCES)
INCLUDE_FLAGS = $(libscispreadsheet_la_CFLAGS)

libscispreadsheet_la_LIBADD = libscispreadsheet-algo.la 

#### Target ######
modulename=spreadsheet


#### spreadsheet : Conf files ####
libscispreadsheet_la_rootdir = $(mydatadir)
libscispreadsheet_la_root_DATA =  license.txt 


####�spreadsheet : init scripts ####
libscispreadsheet_la_etcdir = $(mydatadir)/etc
libscispreadsheet_la_etc_DATA = etc/spreadsheet.quit etc/spreadsheet.start

####�spreadsheet : gateway declaration ####
libscispreadsheet_la_sci_gatewaydir = $(mydatadir)/sci_gateway
libscispreadsheet_la_sci_gateway_DATA = sci_gateway/spreadsheet_gateway.xml

include $(top_srcdir)/Makefile.incl.am
