/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2004-2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Allan Cornet
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2010 - DIGITEO - Manuel Juliachs
 * Copyright (C) 2011 - DIGITEO - Vincent Couvert
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: get_labels_font_size_property.c                                  */
/* desc : function to retrieve in Scilab the labels_font_size field of    */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "Scierror.h"
#include "localization.h"

#include "getGraphicObjectProperty.h"
#include "graphicObjectProperties.h"

/*
 * get_labels_font_size_property is apparently duplicate with
 * get_font_size_property
 */

/*------------------------------------------------------------------------*/
int get_labels_font_size_property(char *pobjUID)
{
    double dblFontSize = 0.0;
    double* pdblFontSize = &dblFontSize;

#if 0
    if (   sciGetEntityType (pobj) == SCI_SUBWIN
           || sciGetEntityType (pobj) == SCI_FIGURE
           || sciGetEntityType (pobj) == SCI_AXES)
    {
        return sciReturnDouble( sciGetFontSize(pobj) ) ; /* F.Leray 08.04.04 */
    }
    else
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"),"labels_font_size");
        return -1;
    }
#endif

    getGraphicObjectProperty(pobjUID, __GO_FONT_SIZE__, jni_double, &pdblFontSize);

    if (pdblFontSize == NULL)
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"),"labels_font_size");
        return -1;
    }

    return sciReturnDouble(dblFontSize);
}
/*------------------------------------------------------------------------*/
