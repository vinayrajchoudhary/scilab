/*
* Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
* Copyright (C) 2009 - DIGITEO - Allan CORNET
* 
* This file must be used under the terms of the CeCILL.
* This source file is licensed as described in the file COPYING, which
* you should have received as part of this distribution.  The terms
* are also available at    
* http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/
/*--------------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#ifndef _MSC_VER
#include <sys/param.h>
#include <limits.h>
#endif
#include "fullpath.h"
#include "charEncoding.h"
#include "MALLOC.h"
/*--------------------------------------------------------------------------*/
char * get_full_path(char * _FullPath, const char * _Path, size_t _SizeInBytes)
{
#if defined(_MSC_VER)
	char *returnedFullPath = NULL;	

	wchar_t *wPath = to_wide_string((char*)_Path);
	wchar_t *wFullPath = (wchar_t *) MALLOC(sizeof(wchar_t)*_SizeInBytes);

	_wfullpath(wFullPath,wPath, _SizeInBytes );
	returnedFullPath = wide_string_to_UTF8(wFullPath);
	if (returnedFullPath)
	{
		strcpy(_FullPath,returnedFullPath);
		FREE(returnedFullPath);
		returnedFullPath = NULL;
	}

	if (wPath) {FREE(wPath);wPath=NULL;}
	if (wFullPath) {FREE(wFullPath);wFullPath=NULL;}

	return _FullPath;
#else
	char *rp = realpath(_Path,_FullPath);
	return _FullPath;
#endif

}
/*--------------------------------------------------------------------------*/