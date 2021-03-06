/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2004-2006 - INRIA - Fabrice Leray
 * Copyright (C) 2006 - INRIA - Allan Cornet
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
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
/* file: get_figure_style_property.c                                      */
/* desc : function to retrieve in Scilab the figure_style field of a      */
/*        handle                                                          */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "Scierror.h"
#include "localization.h"
#include "MALLOC.h"

/*------------------------------------------------------------------------*/
int get_figure_style_property(char *pobjUID)
{
  //
  // FIXME
  //
#if 0
  /* might be get("figure_style") or f.figure_style */
  if ( pobj != NULL && sciGetEntityType (pobj) != SCI_FIGURE )
  {
    Scierror(999, _("'%s' property does not exist for this handle.\n"),"figure_style");
    return -1;
  }
#endif
  /* no more old style */
  sciReturnString("new") ;
  return 0 ;
}
/*------------------------------------------------------------------------*/
