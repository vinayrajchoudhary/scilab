/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Calixte DENIZET
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
#include "getScilabJavaVM.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "localization.h"

#include "gw_graphic_export.h"
}

#include "ScilabView.hxx"
#include "SwingView.hxx"
#include "Driver.hxx"

/*--------------------------------------------------------------------------*/
int sci_xend(char * fname, unsigned long fname_len )
{
    CheckRhs(0, 0);

    org_scilab_modules_graphic_export::Driver::end(getScilabJavaVM(), ScilabView::getCurrentFigure());
    ScilabView::deleteObject(ScilabView::getCurrentFigure());
    org_scilab_modules_gui::SwingView::setHeadless(getScilabJavaVM(), false);

    LhsVar(1) = 0;
    PutLhsVar();
    return 0;
}
/*--------------------------------------------------------------------------*/
