
/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - DIGITEO - Allan CORNET
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*--------------------------------------------------------------------------*/
#include "XlFontManager.hxx"

extern "C" {
#include <stdlib.h>
#include "getScilabJavaVM.h"
#include "RendererFontManager.h"
#include "MALLOC.h"
#ifdef _MSC_VER
#include "strdup_windows.h"
#endif
}
/*--------------------------------------------------------------------------*/
using namespace org_scilab_modules_renderer_utils_textRendering;

char **getInstalledFontsName(int *sizeArray) 
{
	char **returnedinstalledfontsname = NULL;
	*sizeArray = 0;

	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		char **installedfontsname = NULL;

		*sizeArray = fntmgr->getSizeInstalledFontsName();
		installedfontsname = fntmgr->getInstalledFontsName();
		if (installedfontsname)
		{
			int i = 0;
			returnedinstalledfontsname = (char**)MALLOC(sizeof(char*)*(*sizeArray));
			for( i = 0; i < *sizeArray; i++)
			{
				returnedinstalledfontsname[i] = strdup(installedfontsname[i]);
				free(installedfontsname[i]); /* free because giws uses malloc */ 
				installedfontsname[i] = NULL;

			}
			free(installedfontsname);
			installedfontsname = NULL;
		}
		delete fntmgr;
	}

	return returnedinstalledfontsname;
}
/*--------------------------------------------------------------------------*/
char **getAvailableFontsName(int *sizeArray)
{
	char **returnedavailablefontsname = NULL;
	*sizeArray = 0;

	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		char **availablefontsname = NULL;

		*sizeArray = fntmgr->getSizeAvailableFontsName();
		availablefontsname = fntmgr->getAvailableFontsName();
		if (availablefontsname)
		{
			int i = 0;
			returnedavailablefontsname = (char**)MALLOC(sizeof(char*)*(*sizeArray));
			for( i = 0; i < *sizeArray; i++)
			{
				returnedavailablefontsname[i] = strdup(availablefontsname[i]);
				free(availablefontsname[i]); /* free because giws uses malloc */ 
				availablefontsname[i] = NULL;

			}
			free(availablefontsname);
			availablefontsname = NULL;
		}
		delete fntmgr;
	}

	return returnedavailablefontsname;
}
/*--------------------------------------------------------------------------*/
BOOL isAvailableFontsName(char *fontname)
{
	BOOL bOK = FALSE;
	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		bOK = booltoBOOL(fntmgr->isAvailableFontName(fontname));
		delete fntmgr;
	}
	return bOK;
}
/*--------------------------------------------------------------------------*/
int addFont(char *fontname)
{
	int fontID = 0;

	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		fontID = (int)fntmgr->addFont(fontname);
		delete fntmgr;
	}

	return fontID;
}
/*--------------------------------------------------------------------------*/
int changeFont(int index, char * fontName)
{
	int fontID = 0;
	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		fontID = (int)fntmgr->changeFont((long)index,fontName);
		delete fntmgr;
	}

	return fontID;
}
/*--------------------------------------------------------------------------*/
int changeFontWithProperty(int index, char * fontName, BOOL isBold, BOOL isItalic)
{
	int fontID = 0;
	org_scilab_modules_renderer_utils_textRendering::XlFontManager *fntmgr = new org_scilab_modules_renderer_utils_textRendering::XlFontManager(getScilabJavaVM());
	if (fntmgr)
	{
		fontID = (int)fntmgr->changeFontWithProperty((long)index,fontName,BOOLtobool(isBold),BOOLtobool(isItalic));
		delete fntmgr;
	}
	return fontID;
}
/*--------------------------------------------------------------------------*/