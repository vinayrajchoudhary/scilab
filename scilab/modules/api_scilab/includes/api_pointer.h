/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 */

#ifndef __POINTER_API__
#define __POINTER_API__

#ifdef __cplusplus
extern "C" {
#endif

#include "dynlib_api_scilab.h"

/**
 * Get pointer variable
 * @param[in] _piAddress variable address
 * @param[out] _pvPtr return pointer
 * @return if the operation successed (0) or not ( !0 )
 */
API_SCILAB_IMPEXP int getPointer(int* _piAddress, void** _pvPtr);


/**
 * Alloc pointer variable
 * @param[in] _iVar variable number
 * @param[out] _pvPtr return pointer on pointer
 * @return if the operation successed (0) or not ( !0 )
 */
API_SCILAB_IMPEXP int allocPointer(int _iVar, void** _pvPtr);

/**
 * @todo
 * @param[in] _piAddress variable address
 * @param[out] _pvPtr return pointer on pointer
 * @return if the operation successed (0) or not ( !0 )
 */
API_SCILAB_IMPEXP int fillPointer(int *_piAddress, void** _pvPtr);

/**
 * Create pointer variable
 * @param[in] _iVar variable number
 * @param[in] _pvPtr pointer on pointer
 * @return if the operation successed (0) or not ( !0 )
 */
API_SCILAB_IMPEXP int createPointer(int _iVar, void* _pvPtr);

#ifdef __cplusplus
}
#endif
#endif /* __POINTER_API__ */