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
/* file: get_tics_direction_property.c                                    */
/* desc : function to retrieve in Scilab the tics_direction field of      */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "Scierror.h"
#include "localization.h"

#include "getGraphicObjectProperty.h"
#include "graphicObjectProperties.h"

/*------------------------------------------------------------------------*/
int get_tics_direction_property(char *pobjUID)
{
    int iTicksDirection = 0;
    int* piTicksDirection = &iTicksDirection;

#if 0
    if ( sciGetEntityType( pobj ) != SCI_AXES )
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"), "tics_direction");
        return -1;
    }
#endif

    getGraphicObjectProperty(pobjUID, __GO_TICKS_DIRECTION__, jni_int, &piTicksDirection);

    if (piTicksDirection == NULL)
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"), "tics_direction");
        return -1;
    }

    if (iTicksDirection == 0)
    {
        return sciReturnString("top");
    }
    else if (iTicksDirection == 1)
    {
        return sciReturnString("bottom");
    }
    else if (iTicksDirection == 2)
    {
        return sciReturnString("left");
    }
    else if (iTicksDirection == 3)
    {
        return sciReturnString("right");
    }
    else
    {
        Scierror(999, _("Wrong value for '%s' property.\n"),"tics_direction");
    }

    return -1;

}
/*------------------------------------------------------------------------*/
