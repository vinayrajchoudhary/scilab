/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2004-2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Allan Cornet
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------*/
/* file: set_title_property.c                                             */
/* desc : function to modify in Scilab the title field of                 */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "setHandleProperty.h"
#include "SetProperty.h"
#include "getPropertyAssignedValue.h"
#include "Interaction.h"
#include "SetPropertyStatus.h"
#include "GetProperty.h"
#include "sciprint.h"
#include "localization.h"

/*------------------------------------------------------------------------*/
int set_links_property( sciPointObj * pobj, int stackPointer, int valueType, int nbRow, int nbCol )
{
  int nblegends=pLEGEND_FEATURE(pobj)->nblegends;
  int i;
  if ( sciGetEntityType(pobj) != SCI_LEGEND )
  {
    sciprint(_("%s property undefined for this object.\n"), "Legend") ;
    return SET_PROPERTY_ERROR ;
  }
  if (nbRow*nbCol != nblegends) {
    sciprint(_("%s Invalid dimension of the assigned handle, expected dimension is %d.\n"), "links",nblegends) ;
    return SET_PROPERTY_ERROR ;
  }

  sciGetPointerFromHandle( getHandleFromStack( stackPointer ) ) ;
  for (i=0; i<nblegends; i++) {
    pLEGEND_FEATURE(pobj)->pptabofpointobj[i]=sciGetPointerFromHandle(getHandleFromStack( stackPointer+i ) ) ;
  }
  return SET_PROPERTY_SUCCEED ;
}
/*------------------------------------------------------------------------*/