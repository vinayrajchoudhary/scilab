/*
* Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
* Copyright (C) 2008 - INRIA - Jean-Baptiste Silvy
* 
* This file must be used under the terms of the CeCILL.
* This source file is licensed as described in the file COPYING, which
* you should have received as part of this distribution.  The terms
* are also available at    
* http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

/*------------------------------------------------------------------------*/
/* file: get_link_property.c                                              */
/* desc : function to retrieve in Scilab the  handles used by Legend      */
/*        to assign polyline styles                                       */
/*------------------------------------------------------------------------*/

#include "getHandleProperty.h"
#include "GetProperty.h"
#include "returnProperty.h"
#include "sciprint.h"
#include "localization.h"
#include "MALLOC.h"
/*------------------------------------------------------------------------*/
int get_links_property( sciPointObj * pobj )
{
  int nblegends=pLEGEND_FEATURE(pobj)->nblegends;
  int i;
  long *handles;
  int status;
  if (sciGetEntityType(pobj) != SCI_LEGEND)
  {
    sciprint(_("%s property does not exist for this handle.\n"), "links") ;
    return -1 ;
  }
  handles=(long *)MALLOC(nblegends*sizeof(long));
  if (handles==NULL) {
    sciprint(_("%s: No more memory.\n"),"get_links_property");
    return -1 ;
  }
  for (i=0; i<nblegends; i++) {
    handles[i]=sciGetHandle( pLEGEND_FEATURE(pobj)->pptabofpointobj[i]);
  }
  status = sciReturnRowHandleVector(handles, nblegends);
 
  FREE(handles);

  return status;
}
/*------------------------------------------------------------------------*/