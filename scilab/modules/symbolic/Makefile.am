# Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
# Copyright (C) 2006 - INRIA - Sylvestre LEDRU
# 
# This file must be used under the terms of the CeCILL.
# This source file is licensed as described in the file COPYING, which
# you should have received as part of this distribution.  The terms
# are also available at    
# http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


GATEWAY_C_SOURCES = sci_gateway/c/gw_symbolic.c \
sci_gateway/c/sci_mulf.c \
sci_gateway/c/sci_ldivf.c \
sci_gateway/c/sci_addsubf.c \
sci_gateway/c/sci_rdivf.c

GATEWAY_FORTRAN_SOURCES =  sci_gateway/fortran/sci_f_addsubf.f \
sci_gateway/fortran/sci_f_mulf.f \
sci_gateway/fortran/sci_f_ldivf.f \
sci_gateway/fortran/sci_f_rdivf.f

libscisymbolic_la_CFLAGS=  	-I$(srcdir)/includes/ \
				-I$(top_srcdir)/modules/api_scilab/includes \
				-I$(top_srcdir)/modules/output_stream/includes
#-Isrc/c/
pkglib_LTLIBRARIES = libscisymbolic.la
noinst_LTLIBRARIES = libscisymbolic-algo.la

libscisymbolic_la_LDFLAGS = -version-number $(SCILAB_LIBRARY_VERSION)

libscisymbolic_algo_la_SOURCES = $(GATEWAY_FORTRAN_SOURCES)
libscisymbolic_la_SOURCES = $(GATEWAY_C_SOURCES)
libscisymbolic_algo_la_CFLAGS = $(libscisymbolic_la_CFLAGS)
# For the code check (splint)
CHECK_SRC= $(GATEWAY_C_SOURCES)
INCLUDE_FLAGS = $(libscisymbolic_la_CFLAGS)

libscisymbolic_la_LIBADD = libscisymbolic-algo.la



#### Target ######
modulename=symbolic


#### symbolic : Conf files ####
libscisymbolic_la_rootdir = $(mydatadir)
libscisymbolic_la_root_DATA =  license.txt 


#### symbolic : init scripts ####
libscisymbolic_la_etcdir = $(mydatadir)/etc
libscisymbolic_la_etc_DATA = etc/symbolic.quit etc/symbolic.start

#### symbolic : gateway declaration ####
libscisymbolic_la_sci_gatewaydir = $(mydatadir)/sci_gateway
libscisymbolic_la_sci_gateway_DATA = sci_gateway/symbolic_gateway.xml

include $(top_srcdir)/Makefile.incl.am
