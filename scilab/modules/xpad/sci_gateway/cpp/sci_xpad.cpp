/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2009 - DIGITEO - Vincent COUVERT
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

extern "C"
{
#include <wchar.h>
#include "callxpad.h"
#include "gw_xpad.h"
#include "stack-c.h"
#include "api_common.h"
#include "api_string.h"
#include "localization.h"
#include "Scierror.h"
#include "MALLOC.h"
#include "freeArrayOfString.h"
}

/*--------------------------------------------------------------------------*/
int sci_xpad(char *fname,unsigned long fname_len)
{
	CheckRhs(0,1);
	CheckLhs(0,1);

	if (Rhs == 0)
	{
		callXpad(NULL, 0);
	}
	else
	{
		int m1 = 0, n1 = 0;
		int *piAddressVarOne = NULL;
		wchar_t **pStVarOne = NULL;
		int *lenStVarOne = NULL;
		int i = 0;

		getVarAddressFromPosition(1, &piAddressVarOne);

		if ( getVarType(piAddressVarOne) != sci_strings )
		{
			Scierror(999,_("%s: Wrong type for input argument #%d: A string expected.\n"),fname,1);
			return 0;
		}

		/* get dimensions */
		getMatrixOfWideString(piAddressVarOne, &m1, &n1, lenStVarOne, pStVarOne);

		lenStVarOne = (int*)MALLOC(sizeof(int)*(m1 * n1));
		if (lenStVarOne == NULL)
		{
			Scierror(999,_("%s: No more memory.\n"), fname);
			return 0;
		}

		/* get lengths */
		getMatrixOfWideString(piAddressVarOne, &m1, &n1, lenStVarOne, pStVarOne);

		pStVarOne = (wchar_t  **)MALLOC(sizeof(wchar_t *)*(m1*n1));
		if (pStVarOne == NULL)
		{
			Scierror(999,_("%s: No more memory.\n"), fname);
			return 0;
		}

		for(i = 0; i < m1 * n1; i++)
		{
			pStVarOne[i] = (wchar_t *)MALLOC(sizeof(wchar_t *) * (lenStVarOne[i] + 1));
		}
  
		/* get strings */
		getMatrixOfWideString(piAddressVarOne, &m1, &n1, lenStVarOne, pStVarOne);

		callXpadW(pStVarOne,m1 * n1);
		freeArrayOfWideString(pStVarOne,m1 * n1);
	}

	LhsVar(1) = 0;
	PutLhsVar();
	return 0;
}
/*--------------------------------------------------------------------------*/