/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - ENPC - Jean-Philipe Chancelier
 * Copyright (C) 2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2011 - DIGITEO - Bruno JOFRET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: sci_copy.h                                                       */
/* desc : interface for copy routine                                      */
/*------------------------------------------------------------------------*/

#include <stdlib.h>

#include "gw_graphics.h"
#include "stack-c.h"
#include "GetProperty.h"
#include "CloneObjects.h"
#include "localization.h"
#include "Scierror.h"
#include "HandleManagement.h"
#include "getGraphicObjectProperty.h"
#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
#include "createGraphicObject.h"
/*--------------------------------------------------------------------------*/
int sci_copy(char *fname,unsigned long fname_len)
{
    unsigned long hdl, hdlparent;
    char *pobjUID, *psubwinparenttargetUID, *pcopyobjUID;
    int m1, n1, l1,l2;
    int numrow, numcol, outindex,lw;
    char* pstType;

    CheckRhs(1,2);
    CheckLhs(0,1);

    /*  set or create a graphic window*/
    lw = 1 + Top - Rhs;
    GetRhsVar(1,GRAPHICAL_HANDLE_DATATYPE,&m1,&n1,&l1); /* Gets the Handle passed as argument*/
    if (m1!=1||n1!=1)
    {
        C2F(overload)(&lw,"copy",4);
        return 0;
    }

    hdl = (unsigned long)*hstk(l1); /* on recupere le pointeur d'objet par le handle*/
    pobjUID = getObjectFromHandle(hdl);
    if (pobjUID == NULL) {
        Scierror(999,_("%s: The handle is not or no more valid.\n"),fname);
        return 0;
    }

    getGraphicObjectProperty(pobjUID, __GO_TYPE__, jni_string, &pstType);

    if (strcmp(pstType, __GO_TEXT__) != 0 &&
        strcmp(pstType, __GO_ARC__) != 0 &&
        strcmp(pstType, __GO_POLYLINE__) != 0 &&
        strcmp(pstType, __GO_RECTANGLE__))
    {
        C2F(overload)(&lw,"copy",4);
        return 0;
    }
    //psubwinparenttarget = sciGetParentSubwin(sciGetPointerFromHandle(hdl));

    if (Rhs > 1)
    {
        GetRhsVar(2,GRAPHICAL_HANDLE_DATATYPE,&m1,&n1,&l2); /* Gets the command name */
        hdlparent = (unsigned long)*hstk(l2); /* on recupere le pointeur d'objet par le handle*/
        psubwinparenttargetUID = getObjectFromHandle(hdlparent);
        if ( psubwinparenttargetUID == NULL)
        {
            Scierror(999,_("%s: The handle is not or no more valid.\n"),fname);
            return 0;
        }
        // Check Parent is an of type Axes.
        getGraphicObjectProperty(psubwinparenttargetUID, __GO_TYPE__, jni_string, &pstType);

        if (strcmp(pstType, __GO_AXES__) != 0)
        {
            Scierror(999,_("%s: Parent entity for destination should be an axes.\n"),fname);
            return 0;
        }

    }

    numrow   = 1;
    numcol   = 1;
    CreateVar(Rhs+1,GRAPHICAL_HANDLE_DATATYPE,&numrow,&numcol,&outindex);
    //*hstk(outindex) = sciGetHandle(pcopyobj = sciCopyObj((sciPointObj *)pobj,(sciPointObj *)psubwinparenttarget));
    pcopyobjUID = cloneGraphicObject(pobjUID);
    *hstk(outindex) = getHandle(pcopyobjUID);
    if (Rhs > 1)
    {
        setGraphicObjectRelationship(psubwinparenttargetUID, pcopyobjUID);
    }
    //sciDrawObj((sciPointObj *)sciGetParentFigure(pcopyobj));

    LhsVar(1) = Rhs+1;
    PutLhsVar();

    return 0;
}

/*--------------------------------------------------------------------------*/
