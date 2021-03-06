/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Jean-Baptiste Silvy 
 * desc : Several C++ functions that parform some basic operations
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef _RENDERER_BASIC_ALGOS_HXX_
#define _RENDERER_BASIC_ALGOS_HXX_

#ifdef __cplusplus
extern "C" {
#endif

#include "dynlib_renderer.h"
#include "callFunctionFromGateway.h"

/**
 * Destroy a character string allocated by c++ new.
 */
RENDERER_IMPEXP void destroyRendererString(char * string);

/**
 * Call gateway and retrieve all exceptions.
 */
RENDERER_IMPEXP void callFunctionFromGatewayWithExceptions(gw_generic_table * tab, int sizetab);

#ifdef __cplusplus
}
#endif

#endif /* _RENDERER_BASIC_ALGOS_HXX_ */
