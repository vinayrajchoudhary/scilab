# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2006 - INRIA - Sylvestre LEDRU
#
# This file is distributed under the same license as the Scilab package.


GATEWAY_C_SOURCES = sci_gateway/c/sci_zneupd \
sci_gateway/c/sci_dseupd.c \
sci_gateway/c/sci_zneupd.c \
sci_gateway/c/gw_arnoldi.c \
sci_gateway/c/sci_dnaupd.c \
sci_gateway/c/sci_dneupd.c \
sci_gateway/c/sci_dsaupd.c \
sci_gateway/c/sci_znaupd.c

libsciarnoldi_la_CFLAGS= 	-I$(top_srcdir)/libs/MALLOC/includes/ \
				-I$(srcdir)/includes/ \
				-I$(top_srcdir)/modules/api_scilab/includes \
				-I$(top_srcdir)/modules/output_stream/includes/

libsciarnoldi_la_FFLAGS= -I$(srcdir)/src/arpack/

pkglib_LTLIBRARIES = libsciarnoldi.la

libsciarnoldi_la_LDFLAGS = -version-number $(SCILAB_LIBRARY_VERSION) $(LAPACK_LIBS) $(ARPACK_LIBS)

libsciarnoldi_la_SOURCES = $(GATEWAY_C_SOURCES)

# For the code check (splint)
CHECK_SRC= $(GATEWAY_C_SOURCES)
INCLUDE_FLAGS = $(libsciarnoldi_la_CFLAGS)

#### Target ######
modulename=arnoldi


#### arnoldi : Conf files ####
libsciarnoldi_la_rootdir = $(mydatadir)
libsciarnoldi_la_root_DATA =  license.txt 


#### arnoldi : init scripts ####
libsciarnoldi_la_etcdir = $(mydatadir)/etc
libsciarnoldi_la_etc_DATA = etc/arnoldi.quit etc/arnoldi.start

#### arnoldi : gateway declaration ####
libsciarnoldi_la_sci_gatewaydir = $(mydatadir)/sci_gateway
libsciarnoldi_la_sci_gateway_DATA = sci_gateway/arnoldi_gateway.xml

include $(top_srcdir)/Makefile.incl.am
