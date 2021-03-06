/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2004-2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Allan Cornet
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2010 - DIGITEO - Manuel Juliachs
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: set_labels_font_size_property.c                                  */
/* desc : function to modify in Scilab the tics_segment field of          */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "Scierror.h"
#include "localization.h"

#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"

/*
 * set_labels_font_size_property is apparently duplicate with
 * set_font_size_property
 */

/*------------------------------------------------------------------------*/
int set_labels_font_size_property(char* pobjUID, size_t stackPointer, int valueType, int nbRow, int nbCol )
{
    BOOL status;
    double fontSize;

    if ( !isParameterDoubleMatrix( valueType ) )
    {
        Scierror(999, _("Wrong type for '%s' property: Real expected.\n"), "labels_font_size");
        return SET_PROPERTY_ERROR;
    }

#if 0
  if (   sciGetEntityType (pobj) == SCI_SUBWIN || sciGetEntityType (pobj) == SCI_FIGURE
      || sciGetEntityType (pobj) == SCI_AXES)
  {
    return sciSetFontSize( pobj, getDoubleFromStack(stackPointer) ) ; /* F.Leray 08.04.04 */
  }
  else
  {
    Scierror(999, _("'%s' property does not exist for this handle.\n"),"labels_font_size") ;
    return SET_PROPERTY_ERROR ;
  }
#endif

    fontSize = getDoubleFromStack(stackPointer);

    status = setGraphicObjectProperty(pobjUID, __GO_FONT_SIZE__, &fontSize, jni_double, 1);

    if (status == TRUE)
    {
        return SET_PROPERTY_SUCCEED;
    }
    else
    {
        Scierror(999, _("'%s' property does not exist for this handle.\n"),"labels_font_size");
        return SET_PROPERTY_ERROR;
    }
}
/*------------------------------------------------------------------------*/
