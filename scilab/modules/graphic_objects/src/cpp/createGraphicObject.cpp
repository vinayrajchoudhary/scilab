/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

extern "C"
{
#include "createGraphicObject.h"
#include "getScilabJavaVM.h"
}

#include "CallGraphicController.hxx"

#include "DataController.hxx"

using namespace org_scilab_modules_graphic_objects;

char *createGraphicObject(char const* _sType)
{
    return CallGraphicController::askGraphicObject(getScilabJavaVM(), _sType);
}

char *cloneGraphicObject(char const* _sId)
{
    return CallGraphicController::cloneGraphicObject(getScilabJavaVM(), _sId);
}

char const* createDataObject(char const* _sId, char const* _sType)
{
    return DataController::createDataObject(_sId, _sType);
}

void buildFigureMenuBar(char const* _sFigureId)
{
    CallGraphicController::buildFigureMenuBar(getScilabJavaVM(), _sFigureId);
}
