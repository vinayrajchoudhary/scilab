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
/* file: get_legend_location_property.c                                        */
/* desc : function to retrieve in Scilab the legend_location (place) field of          */
/*        a handle                                                        */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"
#include "localization.h"

/*------------------------------------------------------------------------*/
int get_legend_location_property( sciPointObj * pobj )
{
  if (sciGetEntityType (pobj) != SCI_LEGEND)
  {
    sciprint(_("%s property undefined for this handle.\n"), "legend_location") ;
    return -1 ;
  }

  switch ( pLEGEND_FEATURE (pobj)->place )
  {
   case SCI_LEGEND_IN_UPPER_RIGHT: 
    return sciReturnString( "in_upper_right" ) ;
    break;
  case SCI_LEGEND_IN_UPPER_LEFT: 
    return sciReturnString( "in_upper_left" ) ;
    break;
  case SCI_LEGEND_IN_LOWER_RIGHT: 
    return sciReturnString( "in_lower_right" ) ;
    break;
  case SCI_LEGEND_IN_LOWER_LEFT: 
    return sciReturnString( "in_lower_left" ) ;
    break;
  case SCI_LEGEND_OUT_UPPER_RIGHT: 
    return sciReturnString( "out_upper_right" ) ;
    break;
  case SCI_LEGEND_OUT_UPPER_LEFT: 
    return sciReturnString( "out_upper_left" ) ;
    break;
  case SCI_LEGEND_OUT_LOWER_RIGHT: 
    return sciReturnString( "out_lower_right" ) ;
    break;
  case SCI_LEGEND_OUT_LOWER_LEFT: 
    return sciReturnString( "out_lower_left" ) ;
    break;
  case SCI_LEGEND_UPPER_CAPTION: 
    return sciReturnString( "upper_caption" ) ;
    break;
  case SCI_LEGEND_LOWER_CAPTION: 
    return sciReturnString( "lower_caption" ) ;
    break;
  default : 
    sciprint(_("%s is not correctly defined.\n"), "legend_location") ;
    break;
  }
  return -1 ;
}
/*------------------------------------------------------------------------*/