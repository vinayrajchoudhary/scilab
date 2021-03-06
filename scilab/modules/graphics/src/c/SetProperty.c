/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2001 - 2002 - INRIA - Mathieu Philipe
 * Copyright (C) 2002 - 2004 - INRIA - Djalel Abdemouche
 * Copyright (C) 2004 - 2006 - INRIA - Fabrice Leray
 * Copyright (C) 2005 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2008 - INRIA - Vincent COUVERT
 * Copyright (C) 2010-2011 - DIGITEO - Manuel Juliachs
 * Copyright (C) 2010 - Paul Griffiths
 * Copyright (C) 2011 - DIGITEO - Bruno JOFRET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

/*------------------------------------------------------------------------
 *    Graphic library
 *    newGraph Library header
 *    Comment:
 *    -This file contains all functions used to SET the properties of graphics
 *    objects.
 *    - there are two kinds of functions : the sciInit*** which only set an object
 *      property and sciSet*** which do the same work but check before if it is
 *      necessary to do so.
 *    - The returning status of each functions is as follow :
 *      0 for correct execution, 1 if no change was made
 *      and -1 if an error occured.
 --------------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#include "strdup_Windows.h"
#endif

#include "SetProperty.h"
#include "GetProperty.h"
#include "GetJavaProperty.h"
#include "InitObjects.h"
#include "BuildObjects.h"
#include "math_graphics.h"
#include "Scierror.h"
#include "CurrentFigure.h"
#include "ObjectSelection.h"
#include "BasicAlgos.h"
#include "FigureList.h"
#include "localization.h"
#include "SetJavaProperty.h"
#include "HandleManagement.h"
#include "loadTextRenderingAPI.h"
#include "sciprint.h"

#include "MALLOC.h"

#include "CallFigure.h"

#include "getGraphicObjectProperty.h"
#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
#include "FigureModel.h"
#include "AxesModel.h"

#define MAX_MARK_STYLE 14

/*---------------------------------------------------------------------------*/
/* setSubWinAngles                                                                    */
/* Modify the viewing angles of a subwindow                                           */
/* for safer modifications prefer use Obj_RedrawNewAngle                              */
/*---------------------------------------------------------------------------*/
int setSubWinAngles( char *psubwin, double theta, double alpha )
{
    // FIXME
    abort();
#if 0
    /**dj20003***/
    sciSubWindow * ppSubWin = pSUBWIN_FEATURE (psubwin) ;

    ppSubWin->alpha = alpha ;
    ppSubWin->theta = theta ;

    if ((alpha == 0.0) && (theta == 270.0))
    {
        ppSubWin->is3d = FALSE ;
        ppSubWin->project[2]= 0; /* no z to display */
        return 0;
    }

    ppSubWin->is3d  = TRUE  ;
    if ((alpha == 0.0 ) || (alpha == 180.0 ) || (alpha == -180.0 ))  /* DJ.A 30/12 */
    {
        ppSubWin->project[2]= 0; /* no z to display */
    }
    else
    {
        ppSubWin->project[2]= 1; /* z must be displayed */
        if (    ((alpha == 90.0 ) || (alpha == 270.0 ) || (alpha == -90.0 ) || (alpha == -270.0 ))
                && ((theta == 90.0 ) || (theta == -90.0 ) || (theta == 270.0 ) || (theta == -270.0 )))
        {
            ppSubWin->project[1]= 0; /* no y to display */
        }
        else
        {
            ppSubWin->project[1]= 1;
            if (   ( (alpha == 90.0 ) || (alpha == 270.0 ) || (alpha == -90.0  ) || (alpha == -270.0 ))
                   && ( (theta == 0.0  ) || (theta == 180.0 ) || (alpha == -180.0 ) ))
            {
                ppSubWin->project[0]= 0; /* BUG evreywhere when theta == 0 */
            }
            else
            {
                ppSubWin->project[0]= 1;
            }
        }
    }
#endif
    return 0 ;
}

int sciInitNumColors( char * pobjUID, int numcolors)
{
    // FIXME
    abort();
#if 0
    /* modified jb Silvy 06/2006 */
	if (sciGetEntityType (pobjUID)==SCI_FIGURE)
    {
        pFIGURE_FEATURE(pobjUID)->numcolors = numcolors ;
        return 0 ;
    }else{
        return sciSetNumColors( sciGetParentFigure( pobjUID ), numcolors ) ;
    }
#endif
    return 0;
}

/**sciSetNumColors
 * This function sets the number of the color defined in colormap
 * param char * pobjUID: the pointer to the entity
 * param int numcolor: the number of the indexed color
 * return 0 if ok, -1 if not
 */
int
sciSetNumColors (char * pobjUID, int numcolors)
{
    if ( sciGetNumColors( pobjUID ) == numcolors )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitNumColors( pobjUID, numcolors ) ;

}


/*** Adding F.Leray 31.03.04 for supporting -1 and -2 indexes.*/
/* retrieve the realindex inside the colormap from the handle color property */
/* -1 is actually m+1 and -2, m+2 */
int sciSetGoodIndex(char * pobjUID, int colorindex) /* return colorindex or m (Default Black) or m+1 (Default White)*/
{
    int m = sciGetNumColors (pobjUID);	/* the number of the color*/

    if( colorindex == -1 ) /* Black */
        return m + 1 ; /* modif. ici*/
    else if( colorindex == -2 ) /* White */
        return m + 2 ; /* modif. ici*/
    else
        return colorindex;
}

int sciInitBackground( char * pobjUID, int colorindex )
{
    int m = sciGetNumColors(pobjUID);
    if(!sciCheckColorIndex(pobjUID, colorindex)) return 0;

    colorindex = sciSetGoodIndex(pobjUID,colorindex);

    if (sciGetGraphicContext((sciPointObj *)pobjUID) != NULL)
    {
        int newIndex = Max (0, Min (colorindex - 1, m + 1));
        sciGetGraphicContext((sciPointObj*) pobjUID)->backgroundcolor = newIndex;

        if (sciGetEntityType((sciPointObj*)pobjUID) == SCI_FIGURE && !isFigureModel(pobjUID))
        {
			/* disable protection since this function will call Java */
            //disableFigureSynchronization(pobjUID);
            sciSetJavaBackground((sciPointObj*)pobjUID, newIndex);
			//enableFigureSynchronization(pobjUID);
        }

        return 0;
    }

    /*printSetGetErrorMessage("background");*/ /* rewrite updatebaw to renable this message */
    return -1;
}

/**sciSetBackground
 * Sets the number of the Background
 */
int
sciSetBackground (char * pobjUID, int colorindex)
{
    if ( sciGetBackground((sciPointObj*) pobjUID ) == colorindex )
    {
        /* nothing to do */
        return 1 ;
    }

    return sciInitBackground( pobjUID, colorindex ) ;

}


int sciInitForeground( char * pobjUID, int colorindex )
{
    // FIXME
    abort();
#if 0
    int m = sciGetNumColors(pobjUID);
    if(!sciCheckColorIndex(pobjUID, colorindex)) return 0;

    colorindex = sciSetGoodIndex(pobjUID,colorindex);

    if (sciGetGraphicContext(pobjUID) != NULL)
    {
        sciGetGraphicContext(pobjUID)->foregroundcolor = Max (0, Min (colorindex - 1, m + 1));
        return 0;
    }

    /*printSetGetErrorMessage("foreground");*/ /* rewrite updatebaw to renable this message */
#endif
    return -1;
}

/**sciSetForeground
 * sets the number of the Foreground
 */
int
sciSetForeground (char * pobjUID, int colorindex)
{
    // FIXME
    abort();
    return 0;
}

int sciSetLineWidth( char * pobjUID, double linewidth )
{
/*
 * Deactivated: the property is set within the MVC regardless of its
 * currently stored value.
 */
#if 0
    if ( sciGetLineWidth( pobjUID ) == linewidth )
    {
        /* nothing to do */
        return 1 ;
    }
#endif

    return sciInitLineWidth( pobjUID, linewidth ) ;
}


/**sciSetLineWidth
 * Sets the line width
 */
int
sciInitLineWidth (char * pobjUID, double linewidth)
{
    BOOL status;

    if (linewidth < 0)
    {
        Scierror(999, _("Line width must be greater than %d.\n"),0);
        return -1;
    }
    else
    {
        status = setGraphicObjectProperty(pobjUID, __GO_LINE_THICKNESS__, &linewidth, jni_double, 1);

        if (status == TRUE)
        {
            return 0;
        }
    }
    printSetGetErrorMessage("thickness");
    return -1;
}


int sciSetLineStyle( char * pobjUID, int linestyle )
{
/*
 * Deactivated: the property is set within the MVC regardless of its
 * currently stored value.
 */
#if 0
    if ( sciGetLineStyle( pobjUID ) == linestyle )
    {
        /* nothing to do */
        return 1 ;
    }
#endif

    return sciInitLineStyle( pobjUID, linestyle ) ;
}

/**sciSetLineStyle
 * Sets the line style
 */
int
sciInitLineStyle (char * pobjUID, int linestyle)
{
    BOOL status;
    if (linestyle < 0)
    {
        Scierror(999, _("The line style must be greater than %d.\n"),0);
        return -1;
    }
    else
    {
        status = setGraphicObjectProperty(pobjUID, __GO_LINE_STYLE__, &linestyle, jni_int, 1);

        if (status == TRUE)
        {
            return 0;
        }
    }

    printSetGetErrorMessage("line_style");
    return -1;
}


int sciInitIsMark( char * pobjUID, BOOL ismark )
{

    if (sciGetGraphicContext((sciPointObj*)pobjUID) != NULL)
    {
        sciGetGraphicContext((sciPointObj*)pobjUID)->ismark = ismark;
        return 0;
    }

    printSetGetErrorMessage("mark_mode");
    return -1;

}

/**sciSetIsMark
 * Sets the line style
 */
int
sciSetIsMark (char * pobjUID, BOOL ismark)
{

    if ( sciGetIsMark((sciPointObj *)pobjUID) == ismark )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitIsMark( pobjUID, ismark ) ;

}


int sciInitMarkForeground( char * pobjUID, int colorindex )
{
    if(!sciCheckColorIndex(pobjUID, colorindex)) return 0;
    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    if (sciGetGraphicContext((sciPointObj *)pobjUID) != NULL)
    {
        sciGetGraphicContext((sciPointObj *)pobjUID)->markforeground =
            Max (-1, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        return 0;
    }

    printSetGetErrorMessage("mark_foreground");
    return -1;

}

/**sciSetMarkForeground
 * sets the number of the Marks'Foreground
 */
int
sciSetMarkForeground (char * pobjUID, int colorindex)
{

    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/
    if ( sciGetMarkForeground((sciPointObj *)pobjUID ) == colorindex )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitMarkForeground( pobjUID, colorindex ) ;

}

int sciInitMarkBackground( char * pobjUID, int colorindex )
{
    if(!sciCheckColorIndex(pobjUID, colorindex)) return 0;
    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    if (sciGetGraphicContext((sciPointObj *)pobjUID) != NULL)
    {
        sciGetGraphicContext((sciPointObj *)pobjUID)->markbackground =
            Max (-1, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        return 0;
    }

    printSetGetErrorMessage("mark_background");
    return -1;
}

/**sciSetMarkBackground
 * sets the number of the Marks'Background
 */
int
sciSetMarkBackground (char * pobjUID, int colorindex)
{

    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    if ( sciGetMarkBackground((sciPointObj *) pobjUID ) == colorindex )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitMarkBackground( pobjUID, colorindex ) ;

}



int sciInitMarkStyle( char * pobjUID, int markstyle )
{
    BOOL status;

    if (markstyle < 0 || markstyle > MAX_MARK_STYLE )
    {
        Scierror(999, _("Wrong value for '%s' property: Must be between %d and %d.\n"), "mark_style", 0, MAX_MARK_STYLE);
        return -1;
    }
    else
    {
        status = setGraphicObjectProperty(pobjUID, __GO_MARK_STYLE__, &markstyle, jni_int, 1);

        if (status == TRUE)
        {
            return 0;
        }
    }

    printSetGetErrorMessage("mark_style");
    return -1;
}


/**sciSetMarkStyle
 * Sets the mark style
 */
int
sciSetMarkStyle (char * pobjUID, int markstyle)
{
/*
 * Deactivated: the property is set within the MVC regardless of its
 * currently stored value.
 */
#if 0
    if ( sciGetMarkStyle( pobjUID ) == markstyle )
    {
        /* nothing to do */
        return 1 ;
    }
#endif

    return sciInitMarkStyle( pobjUID, markstyle ) ;
}

int sciInitMarkSize( char * pobjUID, int marksize )
{
    if (marksize < 0)
    {
        Scierror(999, _("The mark size must be greater or equal than %d.\n"),0);
        return -1;
    }
    else
    {
        BOOL status;

        status = setGraphicObjectProperty(pobjUID, __GO_MARK_SIZE__, &marksize, jni_int, 1);

        if (status == TRUE)
        {
            return 0;
        }
    }

    printSetGetErrorMessage("mark_size");
    return -1;
}

/**sciSetMarkSize
 * Sets the mark size
 */
int
sciSetMarkSize (char * pobjUID, int marksize)
{
/*
 * Deactivated: the property is set within the MVC regardless of its
 * currently stored value.
 */
#if 0
    if ( sciGetMarkSize( pobjUID ) == marksize )
    {
        /* nothing to do */
        return 1 ;
    }
#endif

    return sciInitMarkSize( pobjUID, marksize ) ;
}

int sciInitMarkSizeUnit( char * pobjUID, int marksizeunit )
{
    if (marksizeunit < 0)
    {
        Scierror(999, _("The mark size unit must be greater than %d.\n"),0);
        return -1;
    }
    else
    {
        if (sciGetGraphicContext((sciPointObj *)pobjUID) != NULL)
        {
            (sciGetGraphicContext((sciPointObj *)pobjUID))->marksizeunit = marksizeunit;
            return 0;
        }
    }

    printSetGetErrorMessage("mark_size_unit");
    return -1;
}

/**sciSetMarkSizeUnit
 * Sets the mark size unit
 * 1 : points, 2 : tabulated
 */
int
sciSetMarkSizeUnit (char * pobjUID, int marksizeunit)
{
/*
 * Deactivated: the property is set within the MVC regardless of its
 * currently stored value.
 */
#if 0
    if ( sciGetMarkSizeUnit( pobjUID ) == marksizeunit )
    {
        /* nothing to do */
        return 1 ;
    }
#endif

    return sciInitMarkSizeUnit( pobjUID, marksizeunit ) ;
}

/**sciInitPolylineStyle
 * Sets Polyline Style (plot)
 */
int sciInitPolylineStyle( char * pobjUID, int plot )
{
    // FIXME
    abort();
#if 0
    if (sciGetEntityType(pobjUID) == SCI_POLYLINE)
    {
        pPOLYLINE_FEATURE(pobjUID)->plot = 4;
        return 0;
    }

    printSetGetErrorMessage("polyline_style");
#endif
    return -1;

}
/**sciInitArrowSize
 * Sets Polyline arrow size (to be used with polyline_style=4)
 */
int sciInitArrowSize( char * pobjUID, double size )
{
    // FIXME
    abort();
#if 0
    if (sciGetEntityType(pobjUID) == SCI_POLYLINE)
    {
        pPOLYLINE_FEATURE(pobjUID)->arsize_factor = size;
        return 0;
    }

    printSetGetErrorMessage("arrow_size");
#endif
    return -1;

}


int sciInitFontSize( char * pobjUID, double fontSize )
{
    if (fontSize < 0)
    {
        Scierror(999, _("The font size must be greater than %d.\n"),0);
        return -1;
    }
    else
    {
        if (sciGetFontContext((sciPointObj *)pobjUID) != NULL)
        {
            (sciGetFontContext((sciPointObj *)pobjUID))->fontSize = fontSize;
            return 0;
        }
        else
        {
            printSetGetErrorMessage("font_size");
            return -1;
        }
    }
}

/**sciSetFontSize
 * Sets the font size
 */
int sciSetFontSize(char * pobjUID, double fontSize)
{

    if (sciGetFontSize( pobjUID ) == fontSize)
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitFontSize(pobjUID, fontSize) ;

}

int sciInitFontOrientation( char * pobjUID, double textorientation )
{
    if (sciGetFontContext((sciPointObj *)pobjUID) != NULL)
    {
        (sciGetFontContext((sciPointObj *)pobjUID))->textorientation = textorientation;
        return 0;
    }
    printSetGetErrorMessage("font_angle");
    return -1;
}



/**sciSetFontOrientation
 * Sets the font Orientation
 */
int
sciSetFontOrientation (char * pobjUID, double textorientation)
{

    if ( sciGetFontOrientation((sciPointObj *)pobjUID ) == textorientation )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitFontOrientation( pobjUID, textorientation ) ;

}

int sciSetStrings( char * pobjUIDDest, const StringMatrix * pStrings )
{
    // FIXME
    abort();
#if 0
    switch (sciGetEntityType (pobjUIDDest))
    {
    case SCI_TEXT:
        deleteMatrix( pTEXT_FEATURE (pobjUIDDest)->pStrings ) ;
        pTEXT_FEATURE (pobjUIDDest)->pStrings = copyStringMatrix( pStrings ) ;
        if ( pTEXT_FEATURE (pobjUIDDest)->pStrings == NULL )
        {
            return -1 ;
        }
        break;
    case SCI_LEGEND:
        deleteMatrix( pLEGEND_FEATURE (pobjUIDDest)->text.pStrings ) ;
        pLEGEND_FEATURE (pobjUIDDest)->text.pStrings = copyStringMatrix( pStrings ) ;
        if ( pLEGEND_FEATURE (pobjUIDDest)->text.pStrings == NULL )
        {
            return -1 ;
        }
        break;
    case SCI_LABEL: /* F.Leray 28.05.04 */
        return sciSetStrings( pLABEL_FEATURE(pobjUIDDest)->text, pStrings ) ;
        break;
    case SCI_UIMENU:
    case SCI_FIGURE:
    case SCI_SUBWIN:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_AGREG:
    default:
        printSetGetErrorMessage("text");
        return -1;
        break;
    }
#endif
    return 0;
}

/**sciSetText
 * Sets the Text in TEXT, TITLE or LEGEND
 * @param char * pobjUID: the pointer to the entity
 * @param char *text[] : the text which has to be put
 * @param int nbRow : the number of row of the text matrix
 * @param int nbCol : the number of col of the text matrix
 * @return  0 if OK, -1 if not
 */
int sciSetText (char * pobjUID, char ** text, int nbRow, int nbCol)
{
    int dimensions[2];
    BOOL status;

    /* Check if we should load LaTex / MathML Java libraries */
    loadTextRenderingAPI(text, nbRow, nbCol);

    dimensions[0] = nbRow;
    dimensions[1] = nbCol;

    status = setGraphicObjectProperty(pobjUID, __GO_TEXT_ARRAY_DIMENSIONS__, dimensions, jni_int_vector, 2);

    if (status != TRUE)
    {
        printSetGetErrorMessage("text");
        return -1;
    }

    status = setGraphicObjectProperty(pobjUID, __GO_TEXT_STRINGS__, text, jni_string_vector, dimensions[0]*dimensions[1]);

    if (status == TRUE)
    {
        return 0;
    }
    else
    {
        printSetGetErrorMessage("text");
        return -1;
    }
}


int sciInitFontBackground( char * pobjUID, int colorindex )
{
    // FIXME
    abort();
#if 0
    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/
    switch (sciGetEntityType (pobjUID))
    {
    case SCI_TEXT:
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_LEGEND:
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_AXES:
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_SUBWIN: /* F.Leray 08.04.04 */
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_FIGURE: /* F.Leray 08.04.04 */
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_LABEL: /* F.Leray 28.05.04 */
        (sciGetFontContext(pobjUID))->backgroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_UIMENU:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AGREG:
    default:
        printSetGetErrorMessage("font_background");
        return -1;
        break;
    }
#endif
    return 0;
}

/**sciSetFontBackground
 * Sets the background color
 * @param char * pobjUID: the pointer to the entity
 * @return  int 0 if OK, -1 if not
 */
int
sciSetFontBackground (char * pobjUID, int colorindex)
{
    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    if ( sciGetFontBackground((sciPointObj *)pobjUID ) == colorindex )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitFontBackground( pobjUID, colorindex ) ;

}

int sciInitFontForeground( char * pobjUID, int colorindex )
{
     // FIXME
    abort();
#if 0
   colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    switch (sciGetEntityType (pobjUID))
    {
    case SCI_TEXT:
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_LEGEND:
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_AXES:
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_SUBWIN: /* F.Leray 08.04.04 */
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_FIGURE: /* F.Leray 08.04.04 */
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_LABEL: /* F.Leray 08.04.04 */
        (sciGetFontContext(pobjUID))->foregroundcolor =
            Max (0, Min (colorindex - 1, sciGetNumColors (pobjUID) + 1));
        break;
    case SCI_UIMENU:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AGREG:
    default:
        printSetGetErrorMessage("font_foreground");
        return -1;
        break;
    }
#endif
    return 0;
}

/**sciSetFontForeground
 * Sets the foreground color
 * @param char * pobjUID: the pointer to the entity
 * @return  int 0 if OK, if not
 */
int
sciSetFontForeground (char * pobjUID, int colorindex)
{
    colorindex = sciSetGoodIndex(pobjUID,colorindex); /* Adding F.Leray 31.03.04*/

    if ( sciGetFontForeground((sciPointObj *)pobjUID ) == colorindex )
    {
        /* nothing to do */
        return 1 ;
    }

    return sciInitFontForeground( pobjUID, colorindex ) ;
}


int sciInitFontStyle( char * pobjUID, int iAttributes )
{
    // FIXME
    abort();
#if 0
    switch (sciGetEntityType (pobjUID))
    {
    case SCI_TEXT:
    case SCI_LEGEND:
    case SCI_SUBWIN:
    case SCI_FIGURE:
    case SCI_LABEL: /* F.Leray 10.06.04 */
        (sciGetFontContext(pobjUID))->fonttype =iAttributes;
        break;
    case SCI_UIMENU:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_AGREG:
    default:
        printSetGetErrorMessage("font_style");
        return -1;
        break;
    }
#endif
    return 0;
}

/**sciSetFontStyle
 * Sets the font style
 * @param char * pobjUID: the pointer to the entity
 * @param  int iAttributes (a logical mask with SCI_ATTR_BOLD|SCI_ATTR_ITALIC|SCI_ATTR_UNDERLINE|SCI_ATTR_STRIKEOUT)
 * @return  int 0 if OK, -1 if not
 */
int
sciSetFontStyle (char * pobjUID, int iAttributes )
{
    if ( sciGetFontStyle((sciPointObj *)pobjUID ) == iAttributes )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitFontStyle( pobjUID, iAttributes ) ;

}


int sciInitLegendPlace( char * pobjUID, sciLegendPlace place )
{
    // FIXME
    abort();
#if 0
    double position[2]={0.0,0.0};

    if (sciGetEntityType (pobjUID) == SCI_LEGEND)
    {
        pLEGEND_FEATURE (pobjUID)->place = place;
        /* calcul de l emplacement relatif du titre
         * en fonction de la taille de la police
         * de la fenetre...
         */
        return sciInitLegendPos (pobjUID, position );
    }

    Scierror(999, _("You are not using a legend object.\n"));
#endif
    return -1;
}

/**sciSetLegendPlace
 * Sets the Title Place  with SCI_TITLE_IN_TOP or SCI_TITLE_IN_BOTTOM and calculate the real position in the window
 * @param char * pobjUID: the pointer to the entity
 * @return 0 if ok, -1 if not
 */
int
sciSetLegendPlace (char * pobjUID, sciLegendPlace place)
{


    if ( sciGetLegendPlace((sciPointObj *)pobjUID ) == place )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitLegendPlace( pobjUID, place ) ;

}

int sciInitLegendPos( char * pobjUID, double position[] )
{
    // FIXME
    abort();
#if 0
    switch (sciGetEntityType (pobjUID))
    {
    case SCI_LEGEND:
        pLEGEND_FEATURE (pobjUID)->pos.x = position[0];
        pLEGEND_FEATURE (pobjUID)->pos.y = position[1];
        break;
    case SCI_FIGURE:
    case SCI_SUBWIN:
    case SCI_TEXT:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_AGREG:
    case SCI_LABEL:
    case SCI_UIMENU:
    default:
        Scierror(999, _("You are not using a legend object.\n"));
        return -1;
        break;
    }
#endif
    return 0;
}

/**sciSetLegendPos
 * Sets the Legend Position in the window
 * @param char * pobjUID: the pointer to the entity
 * @return 0 if ok, -1 if not
 */
int
sciSetLegendPos (char * pobjUID, double position[])
{
    double position_old[2] ;
    sciGetLegendPos((sciPointObj *) pobjUID ,position_old) ;
    if ( position[0] ==  position_old[0] && position[1] == position_old[1] )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitLegendPos( pobjUID, position ) ;
}

int sciInitIsClipping( char * pobjUID, int value )
{
    // FIXME
    abort();
#if 0
    switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE (pobjUID)->isclip = value;
        if(value>0) pSUBWIN_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_ARC:
        pARC_FEATURE (pobjUID)->isclip = value;
        if(value>0) pARC_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_POLYLINE:
        pPOLYLINE_FEATURE (pobjUID)->isclip = value;
        if(value>0) pPOLYLINE_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_RECTANGLE:
        pRECTANGLE_FEATURE (pobjUID)->isclip = value;
        if(value>0) pRECTANGLE_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_SEGS:
        pSEGS_FEATURE (pobjUID)->isclip = value;
        if(value>0) pSEGS_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_TEXT:
        pTEXT_FEATURE (pobjUID)->isclip = value;
        if(value>0) pTEXT_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_AXES:
        pAXES_FEATURE (pobjUID)->isclip = value;
        if(value>0) pAXES_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_SURFACE:
        pSURFACE_FEATURE (pobjUID)->isclip = value;
        if(value>0) pSURFACE_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_FEC:
        pFEC_FEATURE (pobjUID)->isclip = value;
        if(value>0) pFEC_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_GRAYPLOT:
        pGRAYPLOT_FEATURE (pobjUID)->isclip = value;
        if(value>0) pGRAYPLOT_FEATURE (pobjUID)->clip_region_set=1;
        break;
    case SCI_LEGEND:
        pLEGEND_FEATURE(pobjUID)->isclip = value;
        if(value>0) { pLEGEND_FEATURE (pobjUID)->clip_region_set=1;}
        break;
    case SCI_AGREG:
    case SCI_FIGURE:
    case SCI_LABEL: /* F.Leray 28.05.04 */
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("clip_state");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetIsClipping*/
int
sciSetIsClipping( char * pobjUID, int value )
{

    if ( sciGetIsClipping((sciPointObj *) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitIsClipping( pobjUID, value ) ;

}


/**sciSetClipping
 * Sets the clipping area
 * @author Djalel ABDEMOUCHE
 * 29/11/2002
 */
int
sciSetClipping (char * pobjUID, double pclip[4] )
{
    // FIXME
    abort();
#if 0
    int i;

    switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        for(i=0;i<4;i++) {pSUBWIN_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_ARC:
        for(i=0;i<4;i++) {pARC_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_POLYLINE:
        for(i=0;i<4;i++) {pPOLYLINE_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_RECTANGLE:
        for(i=0;i<4;i++) {pRECTANGLE_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_SEGS:
        for(i=0;i<4;i++) {pSEGS_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_TEXT:
        for(i=0;i<4;i++) {pTEXT_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_AXES:
        for(i=0;i<4;i++) {pAXES_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_SURFACE:
        for(i=0;i<4;i++) {pSURFACE_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_LEGEND:
        for(i=0;i<4;i++) {pLEGEND_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_FEC:
        for(i=0;i<4;i++) {pFEC_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_GRAYPLOT:
        for(i=0;i<4;i++) {pGRAYPLOT_FEATURE (pobjUID)->clip_region[i] = pclip[i];}
        break;
    case SCI_LABEL:
        return sciSetClipping( pLABEL_FEATURE (pobjUID)->text, pclip ) ;
        break;
    case SCI_AGREG:
    case SCI_FIGURE:
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("clip_box");
        return -1;
        break;
    }
#endif
    return 0;

}

int sciInitZooming( char * pobjUID, BOOL value )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_FIGURE:
        (sciGetGraphicMode (pobjUID))->zooming = value;
        break;
    case SCI_SUBWIN:
        (sciGetGraphicMode (pobjUID))->zooming = value;
        /* the value is inhirated by the parent */
        sciSetZooming (sciGetParentFigure (pobjUID), value);
        break;
    case SCI_TEXT:
    case SCI_LEGEND:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_AGREG:
    case SCI_LABEL: /* F.Leray 28.05.04 */
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("zoom");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetZooming
 * Sets the zooming state of the object. Is it or not zommed right now
 */
int
sciSetZooming (char * pobjUID, BOOL value)
{
    if ( sciGetZooming((sciPointObj *) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitZooming( pobjUID, value ) ;

}


/**sciSetDefaultValue
 * Sets the default values of figure properties
 * (graphics context, graphics mode, and graphics font)
 * @author Djalel ABDEMOUCHE
 */
int
sciSetDefaultValues (void)
{
// ???
#if 0
    if ((sciInitGraphicContext (sciGetCurrentFigure()) == -1) ||
        (sciInitGraphicMode (sciGetCurrentFigure()) == -1) ||
        (sciInitFontContext (sciGetCurrentFigure()) == -1)) /* Adding F.Leray 13.04.04 to have the completed init.*/
    {
        Scierror(999, _("Unable to load default values.\n"));
        return -1 ;
    }
#endif
    return 0;
}

int sciInitVisibility( char * pobjUID, BOOL value )
{
    // FIXME
    abort();
#if 0

    switch (sciGetEntityType (pobjUID))
    {
    case SCI_FIGURE:
        pFIGURE_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_SUBWIN:
        pSUBWIN_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_LEGEND:
        pLEGEND_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_ARC:
        pARC_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_POLYLINE:
        pPOLYLINE_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_RECTANGLE:
        pRECTANGLE_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_SURFACE:
        pSURFACE_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_SEGS:
        pSEGS_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_FEC:
        pFEC_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_GRAYPLOT:
        pGRAYPLOT_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_TEXT:
        pTEXT_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_AXES:
        pAXES_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_AGREG:
        pAGREG_FEATURE (pobjUID)->visible = value;
        break;
    case SCI_LABEL: /* F.Leray 28.05.04 */
        return sciInitVisibility( pLABEL_FEATURE(pobjUID)->text, value ) ;
        break;
    case SCI_UIMENU:
    case SCI_UICONTROL:
    default:
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetVisibility*/
int
sciSetVisibility (char * pobjUID, BOOL value)
{
    if ( sciGetVisibility((sciPointObj *) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitVisibility( pobjUID, value ) ;

}


int sciInitResize( char * pobjUID, BOOL value )
{
    // FIXME
    abort();
#if 0

    switch (sciGetEntityType (pobjUID))
    {
    case SCI_FIGURE:
        if (isFigureModel(pobjUID))
        {
            pFIGURE_FEATURE(pobjUID)->pModelData->autoResizeMode = value;
        }
        else
        {
            sciSetJavaAutoResizeMode(pobjUID, value);
        }
        break;
    case SCI_SUBWIN:
        sciInitResize(sciGetParentFigure(pobjUID), value);
        break;
    case SCI_TEXT:
    case SCI_LEGEND:
    case SCI_ARC:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_AGREG:
    case SCI_LABEL: /* F.Leray 28.05.04 */
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("auto_resize");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetResize
 * Tunrs ON or OFF the autoresizing mode (when the window is resized by user)
 * @param char * pobjUID: the pointer to the entity
 * @param BOOL value: the value of the switch
 */
int
sciSetResize (char * pobjUID, BOOL value)
{

    if ( sciGetResize((sciPointObj *) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitResize( pobjUID, value ) ;

}



int sciInitName(char * pobjUID, char * newName)
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_FIGURE:
    {
        int newNameLength;

        /* first case newName is NULL */
        if (newName == NULL)
        {
            /* Just set an empty title for the physical window if needed */
            if (!isFigureModel(pobjUID))
            {
                sciSetJavaTitle(pobjUID, "");
            }

            return 0;
        }

        /* newName is a valid string */
        newNameLength = (int) strlen(newName);

        /* Reallocate name */
        pFIGURE_FEATURE(pobjUID)->name = MALLOC( (newNameLength + 1) * sizeof(char) );

        /* copy the string */
        strcpy(pFIGURE_FEATURE(pobjUID)->name, newName) ;

        /* Update the name of the physical window if one exists */
        if (!isFigureModel(pobjUID))
        {
            /* In this case, we need to send the name to the physical window */
            if ( checkPercent(newName) == 0 )
            {
                /* no %d, set the java title directly */
                sciSetJavaTitle(pobjUID, pFIGURE_FEATURE(pobjUID)->name);
            }
            else
            {
                /* a %d inside */
                /* get the number digits of the window number */
                int figureNumber = sciGetNum( pobjUID ) ;
                int nbDigits = GET_NB_DIGITS( figureNumber ) ;
                int realTitleLength = newNameLength + nbDigits - 2 ; /* -2 for the %d which is replaced */
                char * realTitle = MALLOC( (realTitleLength + 1) * sizeof(char) ) ;
                if ( realTitle == NULL )
                {
                    Scierror(999, _("%s: No more memory.\n"),"sciSetName");
                    return -1 ;
                }
                sprintf( realTitle, newName, figureNumber ) ;
                sciSetJavaTitle(pobjUID, realTitle);
                FREE(realTitle) ;
            }


        }

        return 0 ;
    }
    default:
        printSetGetErrorMessage("figure_name");
        return -1 ;
        break;
    }
#endif
        return -1;
}

/**sciSetName
 * Sets the name of the Figure
 * @param char * pobjUID: the pointer to the entity
 * @param char newName: a pointer to the string contening name
 * @return
 */
int
sciSetName(char * pobjUID, char * newName)
{
    // FIXME
    abort();
#if 0
        if (   newName != NULL
           && sciGetName(pobjUID) != NULL
           && strcmp(sciGetName(pobjUID), newName) == 0)
	{
		// nothing to do
		return 1;
	}

	/* Check that the string contains at most one %d character */
	if (checkPercent(newName) < 0)
    {
        Scierror(999, _("Figure name may not contains any %% character, except a single %%d.\n")) ;
        return -1 ;
    }

	/* Free the current name if needed */
	if (sciGetName(pobjUID) != NULL)
	{
		FREE(pFIGURE_FEATURE(pobjUID)->name);
		pFIGURE_FEATURE(pobjUID)->name = NULL;
	}

	return sciInitName(pobjUID, newName);
#endif
    return 1;
}

int sciInitNum( char * pobjUID, int value )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_FIGURE:
        pFIGURE_FEATURE(pobjUID)->number = value;
        break;
    default:
        printSetGetErrorMessage("figure_id");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetNum
 * Sets the number of the Figure.
 * @param char * pobjUID: the pointer to the entity
 * @param int value: the value of the number of the windows
 */
int
sciSetNum (char * pobjUID, int value )
{

    if ( sciGetNum((sciPointObj *)pobjUID) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitNum( pobjUID, value ) ;

}

/*--------------------------------------------------------------------------*/
/* sciSelectFirstSubwin                                                              */
/* select under the first window found under the current figure                      */
/*--------------------------------------------------------------------------*/
void sciSelectFirstSubwin( char * parentFigure )
{
    // FIXME
    abort();
#if 0
        sciSons * figureSons = sciGetSons ( parentFigure ) ;
    if ( figureSons != (sciSons *) NULL )
    {
        /* look for the first subwindow */
        while (   (figureSons->pnext != (sciSons *) NULL)
                  && (sciGetEntityType (figureSons->pointobj) != SCI_SUBWIN))
        {
            figureSons = figureSons->pnext;
        }

        if( sciGetEntityType (figureSons->pointobj) == SCI_SUBWIN )
        {
            /* we found another valid subwindow */
            sciSetSelectedSubWin (figureSons->pointobj);
        }
        else
        {
            sciSetSelectedSubWin(NULL);
        }
    }
#endif
}


int sciInitSelectedSubWin( char * psubwinobj )
{
    // FIXME
    abort();
#if 0
    sciSubWindow * ppSubWin = pSUBWIN_FEATURE ( psubwinobj ) ;

    sciInitSelectedObject( psubwinobj ) ;
#endif
    return 0 ;
}

/**sciSetSelectedSubWin
 * Determines wich SubWin is selected or not. WARNING TO BE DEFINED.
 * It has been adapted to the MVC. Its should be implemented entirely
 * within the MVC (as the setGraphicObjectRelationship function).
 * @param char * psubwinobj: the pointer to the entity sub window
 * @return 0 if OK or -1 if NOT OK
 */
int
sciSetSelectedSubWin (char * psubwinobjUID)
{
    char* type;
    char* parent;

    getGraphicObjectProperty(psubwinobjUID, __GO_TYPE__, jni_string, &type);

    /* Check that the object is an AXES */
    if (strcmp(type, __GO_AXES__) != 0)
    {
        Scierror(999, _("Handle is not a SubWindow.\n"));
        return -1;
    }

    getGraphicObjectProperty(psubwinobjUID, __GO_PARENT__, jni_string, &parent);

    setGraphicObjectProperty(parent, __GO_SELECTED_CHILD__, psubwinobjUID, jni_string, 1);

    return 0;
}

/*-------------------------------------------------------------------------------*/
int sciInitSelectedObject( char * pobjUID )
{
    sciAddUniqueSelectedSon((sciPointObj *)sciGetParent(pobjUID), (sciPointObj *)pobjUID ) ;
    return 0 ;
}
/*-------------------------------------------------------------------------------*/

/**sciSetOriginalSubWin
 * DO NOT USE !!!
 * @param char * pfigure, the parent figure,
 * @param char * psubwin: the pointer to the entity subwindow
 * @return 0 if OK -1 if not
 */
int
sciSetOriginalSubWin (char * pfigure, char * psubwin)
{
    // FIXME
    abort();
#if 0
        pFIGURE_FEATURE(pfigure)->originalsubwin0011 = psubwin;
#endif
    return 0;
}

/**sciSetPoint
 * sets points of the entity, and a pointer to the number of points
 */
/** MAJ pour le 3D DJ.Abdemouche 2003**/
int
sciSetPoint(char * pthis, double *tab, int *numrow, int *numcol)
{
    char* type;
    int i,n1;
    double * pvx  = NULL ;
    double * pvy  = NULL ;
    double * pvz  = NULL ;
    double * pvfx = NULL ;
    double * pvfy = NULL ;
    double * pvfz = NULL ;
    int * pstyle = NULL;

    getGraphicObjectProperty(pthis, __GO_TYPE__, jni_string, &type);

    /*
     * switch over sciGetEntityType replaced by object type string comparisons
     * Still required as we have no better way to do this for the moment
     */
    if (strcmp(type, __GO_POLYLINE__) == 0)
    {
        BOOL result;
        int numElementsArray[2];
        int zCoordinatesSet;

        if ( (*numcol != 3) && (*numcol != 2) && (*numcol != 0) )
        {
            Scierror(999, _("Number of columns must be %d (%d if %s coordinate).\n"),2,3,"z");
            return -1;
        }

        /*
         * The coordinates array is re-allocated (if required) within the data model, testing whether
         * the new number of points is different in order to free/re-allocate is not needed anymore.
         * The 0-element array case is managed by the data model as well.
         */

        if (*numcol == 0)
        {
            n1 = 0;
        }
        else
        {
            n1 = *numrow;
        }

        /* The first element must be equal to 1 for a Polyline, the second is the polyline's number of vertices */
        numElementsArray[0] = 1;
        numElementsArray[1] = n1;

        /* Resizes the data coordinates array if required */
        result = setGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_ELEMENTS_ARRAY__, numElementsArray, jni_int_vector, 2);

        /*
         * For now, the FALSE return value corresponds to a failed memory allocation,
         * which does not allow to discriminate between the failed allocation and non-existing
         * property conditions.
         */
        if (result == FALSE)
        {
            Scierror(999, _("%s: No more memory.\n"), "sciSetPoint");
            return -1;
        }

        if ( *numcol > 0 )
        {
            setGraphicObjectProperty(pthis, __GO_DATA_MODEL_X__, tab, jni_double_vector, n1);
            setGraphicObjectProperty(pthis, __GO_DATA_MODEL_Y__, &tab[n1], jni_double_vector, n1);

            if (*numcol == 3)
            {
                setGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z__, &tab[2*n1], jni_double_vector, n1);
                zCoordinatesSet = 1;
            }
            else
            {
                zCoordinatesSet = 0;
            }

            /* Required for now to indicate that the z coordinates have been set or not */
            setGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z_COORDINATES_SET__, &zCoordinatesSet, jni_int, 1);
        }

        return 0;
    }
    else if (strcmp(type, __GO_RECTANGLE__) == 0)
    {
        double* currentUpperLeftPoint;
        double upperLeftPoint[3];
        int widthIndex = 2;
        int size = *numrow * *numcol;

        if ( size != 5 && size != 4 )
        {
            Scierror(999, _("Number of elements must be %d (%d if %s coordinate).\n"),4,5,"z");
            return -1;
        }

        upperLeftPoint[0] = tab[0];
        upperLeftPoint[1] = tab[1];

        if ( size == 5 )
        {
            upperLeftPoint[2] = tab[2];
            widthIndex = 3;
        }
        else
        {
            /*
             * Needed in order to set the z coordinate if size == 4
             * Being able to set only the point's x and y coordinates values would avoid doing this.
             */
            getGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, jni_double_vector, &currentUpperLeftPoint);
            upperLeftPoint[2] = currentUpperLeftPoint[2];
        }

        setGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, upperLeftPoint, jni_double_vector, 3);

        /* check that the height and width are positive */
        if ( tab[widthIndex] < 0.0 || tab[widthIndex + 1] < 0.0 )
        {
            Scierror(999,"Width and height must be positive.\n") ;
            return -1 ;
        }

        setGraphicObjectProperty(pthis, __GO_WIDTH__, &tab[widthIndex], jni_double, 1);
        setGraphicObjectProperty(pthis, __GO_HEIGHT__, &tab[widthIndex + 1], jni_double, 1);

        return 0;
    }
    else if (strcmp(type, __GO_ARC__) == 0)
    {
        double startAngle;
        double endAngle;
        double upperLeftPoint[3];
        double width;
        double height;
        double* currentUpperLeftPoint;
        int size;

        size = *numrow * *numcol;

        if ((size != 7) && (size != 6))
        {
            Scierror(999, _("Number of elements must be %d (%d if z coordinate )\n"),6,7);
            return -1;
        }

        upperLeftPoint[0] = tab[0];
        upperLeftPoint[1] = tab[1];

        /*
         * Setting the data has been made consistent with how it is done for the Rectangle:
         * it takes into account the size of the input array instead of the parent Axes'
         * view property. Using the latter led to incorrectly set values when size and view
         * were not corresponding (for example when size==7, and view==2d).
         */
        if (size == 7)
        {
            upperLeftPoint[2] = tab[2];
            width = tab[3];
            height = tab[4];
            startAngle = DEG2RAD(tab[5]);
            endAngle = DEG2RAD(tab[6]);
        }
        else
        {
            /* Needed in order to set the z coordinate if size == 6 */
            getGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, jni_double_vector, &currentUpperLeftPoint);

            upperLeftPoint[2] = currentUpperLeftPoint[2];
            width = tab[2];
            height = tab[3];
            startAngle = DEG2RAD(tab[4]);
            endAngle = DEG2RAD(tab[5]);
        }

        setGraphicObjectProperty(pthis, __GO_UPPER_LEFT_POINT__, upperLeftPoint, jni_double_vector, 3);

        setGraphicObjectProperty(pthis, __GO_WIDTH__, &width, jni_double, 1);
        setGraphicObjectProperty(pthis, __GO_HEIGHT__, &height, jni_double, 1);

        setGraphicObjectProperty(pthis, __GO_START_ANGLE__, &startAngle, jni_double, 1);
        setGraphicObjectProperty(pthis, __GO_END_ANGLE__, &endAngle, jni_double, 1);

        return 0;
    }
    else if (strcmp(type, __GO_TEXT__) == 0)
    {
        char* parentAxes;
        double position[3];
        int iView = 0;
        int* piView = &iView;

        if ((*numrow * *numcol != 2)&&(*numrow * *numcol != 3))
        {
            Scierror(999, _("Number of elements must be %d (%d if %s coordinate).\n"),2,3,"z");
            return -1;
        }

        getGraphicObjectProperty(pthis, __GO_PARENT_AXES__, jni_string, &parentAxes);
        getGraphicObjectProperty(parentAxes, __GO_VIEW__, jni_int, &piView);

        position[0] = tab[0];
        position[1] = tab[1];

        if (iView)
        {
            position[2] = tab[2];
        }
        else
        {
            /*
             * Required as the position has 3 coordinates, hence the z-coordinate
             * is set to its current value, which must be retrieved beforehand.
             * Avoiding doing this would require being able to set only the x and y
             * coordinates if required.
             */
            double* currentPosition;
            getGraphicObjectProperty(pthis, __GO_POSITION__, jni_double_vector, &currentPosition);
            position[2] = currentPosition[2];
        }

        setGraphicObjectProperty(pthis, __GO_POSITION__, position, jni_double_vector, 3);

        return 0;
    }
    else if (strcmp(type, __GO_SEGS__) == 0)
    {
        int numArrows;
        double* arrowPoints = NULL;

        if ((*numcol != 3)&&(*numcol != 2))
        {
            Scierror(999, _("Number of columns must be %d (%d if %s coordinate).\n"),2,3,"z");
            return -1;
        }

        if (*numrow % 2 != 0)
        {
            Scierror(999, _("Number of rows must be a multiple of 2.\n"));
            return -1;
        }


        numArrows = *numrow/2;

        arrowPoints = (double*) MALLOC(3*numArrows*sizeof(double));

        if (arrowPoints == NULL)
        {
            Scierror(999, _("%s: No more memory.\n"), "sciSetPoint");
            return -1;
        }

        /*
         * Interlacing ought to be done in the MVC's coordinates
         * set function to avoid the additional code below.
         */
        for (i = 0; i < numArrows; i++)
        {
            arrowPoints[3*i] = tab[2*i];
            arrowPoints[3*i+1] = tab[2*numArrows+2*i];

            if (*numcol == 3)
            {
                arrowPoints[3*i+2] = tab[4*numArrows+2*i];
            }
            else
            {
                arrowPoints[3*i+2] = 0.0;
            }
        }

        setGraphicObjectProperty(pthis, __GO_NUMBER_ARROWS__, &numArrows, jni_int, 1);

        setGraphicObjectProperty(pthis, __GO_BASE__, arrowPoints, jni_double_vector, 3*numArrows);

        for (i = 0; i < numArrows; i++)
        {
            arrowPoints[3*i] = tab[2*i+1];
            arrowPoints[3*i+1] = tab[2*numArrows+2*i+1];

            if (*numcol == 3)
            {
                arrowPoints[3*i+2] = tab[4*numArrows+2*i+1];
            }
            else
            {
                arrowPoints[3*i+2] = 0.0;
            }
        }

        setGraphicObjectProperty(pthis, __GO_DIRECTION__, arrowPoints, jni_double_vector, 3*numArrows);

        FREE(arrowPoints);

        return 0;
    }
    /* DJ.A 2003 */
    /* SCI_SURFACE has been replaced by the MVC's FAC3D and PLOT3D */
    else if (strcmp(type, __GO_FAC3D__) == 0)
    {
        Scierror(999, _("Unhandled data field\n"));
        return -1;
    }
    else if (strcmp(type, __GO_PLOT3D__) == 0)
    {
        Scierror(999, _("Unhandled data field\n"));
        return -1;
    }
    else if (strcmp(type, __GO_MATPLOT__) == 0)
    {
        int nx;
        int ny;
        int gridSize[4];
        int result;

        ny = *numrow;
        nx = *numcol;

        /*
         * The number of points along each dimension is equal to the z data matrix's
         * corresponding dimension plus 1
         */
        gridSize[0] = nx + 1;
        gridSize[1] = 1;
        gridSize[2] = ny + 1;
        gridSize[3] = 1;

        result = setGraphicObjectProperty(pthis, __GO_DATA_MODEL_GRID_SIZE__, gridSize, jni_int_vector, 4);

        if (result == FALSE)
        {
            Scierror(999, _("%s: No more memory.\n"), "sciSetPoint");
            return -1;
        }

        setGraphicObjectProperty(pthis, __GO_DATA_MODEL_Z__, tab, jni_double_vector, nx*ny);
    }
    else if (strcmp(type, __GO_FEC__) == 0)
    {
        BOOL result;
        int Nnode;
        if (*numcol != 3)
        {
            Scierror(999, _("Number of columns must be %d.\n"),3);
            return -1;
        }

        Nnode = *numrow;

        /* Resizes the data coordinates array if required */
        result = setGraphicObjectProperty(pthis, __GO_DATA_MODEL_NUM_VERTICES__, &Nnode, jni_int, 1);

        if (result == FALSE)
        {
            Scierror(999, _("%s: No more memory.\n"), "sciSetPoint");
            return -1;
        }

        setGraphicObjectProperty(pthis, __GO_DATA_MODEL_X__, tab, jni_double_vector, Nnode);
        setGraphicObjectProperty(pthis, __GO_DATA_MODEL_Y__, &tab[Nnode], jni_double_vector, Nnode);
        setGraphicObjectProperty(pthis, __GO_DATA_MODEL_VALUES__, &tab[2*Nnode], jni_double_vector, Nnode);
    }
    else if (strcmp(type, __GO_FIGURE__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    else if (strcmp(type, __GO_AXES__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    else if (strcmp(type, __GO_LEGEND__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    else if (strcmp(type, __GO_AXIS__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    else if (strcmp(type, __GO_COMPOUND__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    /* F.Leray 28.05.04 */
    else if (strcmp(type, __GO_LABEL__) == 0)
    {
        printSetGetErrorMessage("data");
        return -1;
    }
    /*
     * Deactivated for now
     * Same condition as the default one
     */
#if 0
case SCI_UIMENU:
#endif
    else
    {
        printSetGetErrorMessage("data");
        return -1;
    }

    return 0;
}

int sciInitdrawmode( BOOL mode )
{
#if 0
    static sciPointObj * pobj ;
    pobj = sciGetFirstTypedSelectedSon(sciGetCurrentFigure(), SCI_SUBWIN);
    pSUBWIN_FEATURE(pobj)->visible = mode ;
    sciDrawObj(sciGetCurrentFigure ());
#endif
    return 0;
}

/*----------------------------------------------------------------------------------*/
/**
 * In new graphic style, select a window and create one if not already done.
 */
int sciSetUsedWindow( int winNum )
{
    // FIXME
    abort();
#if 0
        return 1;
    /* select or create the window in the driver */
    if ( sciHasFigures() && sciGetNum( sciGetCurrentFigure() ) == winNum )
    {
        /* nothing to do */
        return 1 ;
    }

    return sciInitUsedWindow( winNum ) ;
#endif
    return 1;
}

/*----------------------------------------------------------------------------------*/



int sciInitIsFilled( char * pobjUID, BOOL isfilled )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_LABEL:
        /* isfilled correspond to several properties in text object */
        sciInitIsBoxed(  pLABEL_FEATURE(pobjUID)->text, isfilled ) ;
        sciInitIsLine(   pLABEL_FEATURE(pobjUID)->text, isfilled ) ;
        return sciInitIsFilled( pLABEL_FEATURE(pobjUID)->text, isfilled ) ;
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.filled = isfilled;
        return 0;
    default:
        if(sciGetGraphicContext(pobjUID) != NULL)
        {
            sciGetGraphicContext(pobjUID)->isfilled = isfilled;
            return 0;
        }
    }

    printSetGetErrorMessage("fill_mode");
#endif
    return -1;
}

/**sciSetIsFilled
 * Sets the filled line existence
 */
int
sciSetIsFilled (char * pobjUID, BOOL isfilled)
{

    if ( sciGetIsFilled((sciPointObj *) pobjUID ) == isfilled )
    {
        return 1 ;
    }
    return sciInitIsFilled( pobjUID, isfilled ) ;

}


int sciInitBoxType( char * pobjUID, EAxesBoxType type )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.rect = type ;
        /* redondant information in scilab :'( */
        switch ( type )
        {
        case BT_OFF:
            pSUBWIN_FEATURE(pobjUID)->axes.flag[2] = 0 ;
            break ;
        case BT_ON:
            pSUBWIN_FEATURE(pobjUID)->axes.flag[2] = 4 ;
            break ;
        case BT_HIDDEN_AXES:
            pSUBWIN_FEATURE(pobjUID)->axes.flag[2] = 2 ;
            break ;
        case BT_BACK_HALF:
            pSUBWIN_FEATURE(pobjUID)->axes.flag[2] = 3 ;
            break ;
        }
        return 0;
        break;
    default:
        printSetGetErrorMessage("box_type");
        return -1 ;
        break;
    }
#endif
        return -1 ;
}

/* set the property of the axes box  */
int sciSetBoxType( char * pobjUID, EAxesBoxType type )
{

    if ( sciGetBoxType((sciPointObj *) pobjUID ) == type )
    {
        return 1 ;
    }
    return sciInitBoxType( pobjUID, type ) ;

}


int sciInitIsBoxed( char * pobjUID, BOOL isboxed )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->isboxed = isboxed;
        return 0;
        break;
    case SCI_SUBWIN:
        Scierror(999, _("%s: please use %s instead.\n"),"sciSetIsBoxed","sciSetBoxType");
        if ( isboxed )
        {
            pSUBWIN_FEATURE(pobjUID)->axes.rect = BT_ON ;
        }
        else
        {
            pSUBWIN_FEATURE(pobjUID)->axes.rect = BT_OFF ;
        }
        return 0;
        break;
    case SCI_LABEL:
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_ARC:
    case SCI_FIGURE:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_LEGEND:
    case SCI_SEGS:
    case SCI_FEC:
    case SCI_GRAYPLOT:
    case SCI_AGREG:
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("box_type");
        return -1;
        break;
    }
#endif
        return -1 ;
}

/**sciSetIsBoxed
 * Sets the box existence
 */
int
sciSetIsBoxed (char * pobjUID, BOOL isboxed)
{

    if ( sciGetIsBoxed((sciPointObj *) pobjUID ) == isboxed )
    {
        return 1 ;
    }
    return sciInitIsBoxed( pobjUID, isboxed ) ;

}


int
sciInitNbXSubTics(char * pobjUID, int nbsubtics)
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.nbsubtics[0] = nbsubtics;
        break;
    default:
        printSetGetErrorMessage("subwin_type required");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetNbXSubTics
 * Sets the number of x subticks
 */
int
sciSetNbXSubTics(char * pobjUID, int nbsubtics)
{
    int curr_nbsubtics[3];

    sciGetNbSubTics((sciPointObj*) pobjUID,  curr_nbsubtics);

    if ( curr_nbsubtics[0] == nbsubtics )
    {
        return 1 ;
    }
    return sciInitNbXSubTics( pobjUID, nbsubtics ) ;
}

int
sciInitNbYSubTics(char * pobjUID, int nbsubtics)
{
// FIXME
    abort();
#if 0
    switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.nbsubtics[1] = nbsubtics;
        break;
    default:
        printSetGetErrorMessage("subwin_type required");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetNbYSubTics
 * Sets the number of y subticks
 */
int
sciSetNbYSubTics(char * pobjUID, int nbsubtics)
{
    int curr_nbsubtics[3];

    sciGetNbSubTics((sciPointObj*) pobjUID,  curr_nbsubtics);

    if ( curr_nbsubtics[1] == nbsubtics )
    {
        return 1 ;
    }
    return sciInitNbYSubTics( pobjUID, nbsubtics ) ;
}

int
sciInitNbZSubTics(char * pobjUID, int nbsubtics)
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.nbsubtics[2] = nbsubtics;
        break;
    default:
        printSetGetErrorMessage("subwin_type required");
        return -1 ;
        break;
    }
#endif
    return 0 ;
}

/**sciSetNbZSubTics
 * Sets the number of x subticks
 */
int
sciSetNbZSubTics(char * pobjUID, int nbsubtics)
{
    int curr_nbsubtics[3];

    sciGetNbSubTics((sciPointObj*) pobjUID,  curr_nbsubtics);

    if ( curr_nbsubtics[2] == nbsubtics )
    {
        return 1 ;
    }
    return sciInitNbZSubTics( pobjUID, nbsubtics ) ;
}


int
sciSetInterpVector(char * pobjUID, int size, int * value)
{
    // FIXME
    abort();
#if 0
        int i;

    FREE(pPOLYLINE_FEATURE(pobjUID)->scvector);

    if((pPOLYLINE_FEATURE(pobjUID)->scvector = MALLOC(size*sizeof(int)))==NULL){
        Scierror(999, _("%s: No more memory.\n"), "sciSetInterpVector") ;
        return -1;
    }

    for(i=0;i<size;i++)
        pPOLYLINE_FEATURE(pobjUID)->scvector[i] = value[i];
#endif
    return 0;
}

int sciInitAutoRotation( char * pobjUID, BOOL value )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_LABEL:
        pLABEL_FEATURE(pobjUID)->auto_rotation = value ;
        return 0;
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_ARC:
    case SCI_TEXT:
    case SCI_FIGURE:
    case SCI_SUBWIN:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_FEC:
    case SCI_SEGS:
    case SCI_LEGEND:
    case SCI_GRAYPLOT:
    case SCI_AGREG:
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("auto_rotation");
        return -1 ;
        break;
    }
#endif
        return -1;

}

/* set the auto_rotation property of an object */
int sciSetAutoRotation ( char * pobjUID, BOOL value )
{

    if ( sciGetAutoRotation((sciPointObj*) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitAutoRotation( pobjUID, value ) ;

}


int sciInitAutoPosition( char * pobjUID, BOOL value )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_LABEL:
        pLABEL_FEATURE(pobjUID)->auto_position = value ;
        return 0;
    case SCI_POLYLINE:
    case SCI_RECTANGLE:
    case SCI_ARC:
    case SCI_TEXT:
    case SCI_FIGURE:
    case SCI_SUBWIN:
    case SCI_SURFACE:
    case SCI_AXES:
    case SCI_FEC:
    case SCI_SEGS:
    case SCI_LEGEND:
    case SCI_GRAYPLOT:
    case SCI_AGREG:
    case SCI_UIMENU:
    default:
        printSetGetErrorMessage("auto_position");
        return -1 ;
        break;
    }
#endif
    return -1 ;
}

/* set the auto_position property of an object */
int sciSetAutoPosition ( char * pobjUID, BOOL value )
{

    if ( sciGetAutoPosition((sciPointObj*) pobjUID ) == value )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitAutoPosition( pobjUID, value ) ;

}

/*---------------------------------------------------------------------------*/
int checkPercent( char * string )
{
    /* check for the percent in the string */
    char * firstPercent  = strchr( string, '%' ) ;

    if ( firstPercent == NULL )
    {
        /* no % character found */
        return 0 ;
    }
    else if ( firstPercent[1] != 'd' )
    {
        /* a %something with something != d has been found */
        return -1 ;
    }
    else
    {
        /* here we have found a first %d, check if there is not any more % */
        firstPercent++ ;
        firstPercent = strchr( firstPercent, '%' ) ;
        if ( firstPercent == NULL )
        {
            /* no other % character found */
            return 1 ;
        }
        else
        {
            return -1 ;
        }
    }
}
/*---------------------------------------------------------------------------*/
int sciInitAutoSize( char * pobjUID, BOOL autoSize )
{
// FIXME
#if 0
    switch ( sciGetEntityType (pobjUID) )
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->autoSize = autoSize ;
        return 0 ;
    default:
        printSetGetErrorMessage("text_box_mode");
        return -1 ;
        break;
    }
#endif
    return -1;

}
/*---------------------------------------------------------------------------*/
int sciSetAutoSize( char * pobjUID, BOOL autoSize )
{
    if ( sciGetAutoSize((sciPointObj*) pobjUID ) == autoSize )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitAutoSize( pobjUID, autoSize ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitAlignment( char * pobjUID, sciTextAlignment align )
{
    // FIXME
    abort();
#if 0
        switch (sciGetEntityType (pobjUID))
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->stringsAlign = align ;
        return 0 ;
    default:
        printSetGetErrorMessage("alignment");
        return -1 ;
    }
#endif
    return -1 ;
}
/*-----------------------------------------------------------------------------------*/
int sciSetAlignment( char * pobjUID, sciTextAlignment align )
{
    if ( sciGetAlignment((sciPointObj*) pobjUID ) == align )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitAlignment( pobjUID, align ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitUserSize( char * pobjUID, double width, double height )
{
    // FIXME
    abort();
#if 0
        switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->userSize[0] = width ;
        pTEXT_FEATURE(pobjUID)->userSize[1] = height ;
        return 0 ;
    default:
        printSetGetErrorMessage("text_box");
        return -1 ;
    }
#endif
        return -1;
}
/*-----------------------------------------------------------------------------------*/
int sciSetUserSize( char * pobjUID, double width, double height )
{
    double curWidth  ;
    double curHeight ;
    sciGetUserSize((sciPointObj*) pobjUID, &curWidth, &curHeight ) ;
    if ( curWidth == width && curHeight == height )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitUserSize( pobjUID, width, height ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitCenterPos( char * pobjUID, BOOL newCP )
{
    // FIXME
    abort();
#if 0
        switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->centeredPos = newCP ;
        return 0 ;
    default:
        printSetGetErrorMessage("data");
        return -1 ;
    }
#endif
        return -1;

}
/*-----------------------------------------------------------------------------------*/
int sciSetCenterPos( char * pobjUID, BOOL newCP )
{
    if ( sciGetCenterPos((sciPointObj*) pobjUID ) == newCP )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitCenterPos( pobjUID, newCP ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitHiddenColor( char * pobjUID, int newColor )
{
    // FIXME
    abort();
#if 0
        if(!sciCheckColorIndex(pobjUID, newColor)) { return -1;}

    switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->hiddencolor = newColor;
        return 0 ;
    case SCI_SURFACE:
        pSURFACE_FEATURE(pobjUID)->hiddencolor = newColor;
        return 0;
    default:
        printSetGetErrorMessage("hidden_color");
        return -1 ;
    }
#endif
    return -1;
}
/*-----------------------------------------------------------------------------------*/
int sciSetHiddenColor( char * pobjUID, int newColor )
{
    if ( sciGetHiddenColor((sciPointObj*) pobjUID ) == newColor )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitHiddenColor( pobjUID, newColor ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitHiddenAxisColor( char * pobjUID, int newColor )
{
    // FIXME
    abort();
#if 0
        int m = sciGetNumColors(pobjUID);
    if(newColor < -2 || newColor > m + 2) return 0;

    newColor = sciSetGoodIndex(pobjUID,newColor);

    switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.hiddenAxisColor = Max (0, Min (newColor - 1, m + 1));
        return 0 ;
    default:
        printSetGetErrorMessage("hidden_axis_color");
        return -1 ;
    }
#endif
    return -1;
}
/*-----------------------------------------------------------------------------------*/
int sciSetHiddenAxisColor( char * pobjUID, int newColor )
{
    if ( sciGetHiddenAxisColor((sciPointObj*) pobjUID ) == newColor )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitHiddenAxisColor( pobjUID, newColor ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitGridStyle( char * pobjUID, int xStyle, int yStyle, int zStyle )
{
    // FIXME
    abort();
#if 0
        if (    !sciCheckColorIndex(pobjUID, xStyle)
            || !sciCheckColorIndex(pobjUID, yStyle)
            || !sciCheckColorIndex(pobjUID, zStyle))
    {
        return -1;
    }

    switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->grid[0] = xStyle ;
        pSUBWIN_FEATURE(pobjUID)->grid[1] = yStyle ;
        pSUBWIN_FEATURE(pobjUID)->grid[2] = zStyle ;
        return 0 ;
    default:
        printSetGetErrorMessage("grid");
        return -1 ;
    }
#endif
    return -1;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Set the grid of an axes object
 */
int sciSetGridStyle( char * pobjUID, int xStyle, int yStyle, int zStyle )
{
    int curX ;
    int curY ;
    int curZ ;
    sciGetGridStyle((sciPointObj*) pobjUID, &curX, &curY, &curZ ) ;
    if ( curX == xStyle && curY == yStyle && curZ == zStyle )
    {
        /* nothing to do */
        return 1 ;
    }
    return sciInitGridStyle( pobjUID, xStyle, yStyle, zStyle ) ;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Set the viewport property of a figure.
 * Effective only if the auto_resize property is enable
 */
int sciSetViewport( char * pobjUID, const int viewport[4] )
{
    // FIXME
    abort();
#if 0
        switch( sciGetEntityType( pobjUID ) )
    {
    case SCI_FIGURE:
        if (isFigureModel(pobjUID))
        {
            pFIGURE_FEATURE(pobjUID)->pModelData->viewport[0] = viewport[0];
            pFIGURE_FEATURE(pobjUID)->pModelData->viewport[1] = viewport[1];
            pFIGURE_FEATURE(pobjUID)->pModelData->viewport[2] = viewport[2];
            pFIGURE_FEATURE(pobjUID)->pModelData->viewport[3] = viewport[3];
        }
        else
        {
            sciSetJavaViewport(pobjUID, viewport);
        }
        return 0;
    default:
        printSetGetErrorMessage("viewport");
        return -1 ;
    }
#endif
        return -1;
}

/*-----------------------------------------------------------------------------------*/
int sciInitEventHandler( char * pobjUID, char * name )
{
    // FIXME
    abort();
#if 0
        if( sciGetEntityType( pobjUID ) == SCI_FIGURE)
    {
        sciFigure * ppFigure = pFIGURE_FEATURE(pobjUID) ;

        if ( ppFigure == NULL )
        {
            Scierror(999, _("%s: No more memory.\n"), "sciInitEventHandler") ;
            return -1 ;
        }

        if ( ppFigure->eventHandler != NULL )
        {
            FREE(ppFigure->eventHandler);
        }

        ppFigure->eventHandler = strdup(name);

        /* Java is called to set the listener */
        if (!isFigureModel(pobjUID))
        {
            setFigureEventHandler(sciGetNum(pobjUID), name);
        }

        if ( strcmp( name, "" ) == 0 )
        {
            sciInitIsEventHandlerEnable( pobjUID, FALSE ) ;
        }

        return 0 ;
    }
    else
    {
        printSetGetErrorMessage("event_handler");
        return -1 ;
    }
#endif
        return -1;
}
/*-----------------------------------------------------------------------------------*/
int sciSetEventHandler( char * pobjUID, char * name )
{
    if ( strcmp( sciGetEventHandler((sciPointObj*)pobjUID), name ) == 0 )
    {
        /* nothing to do */
        return 1 ;
    }

    return sciInitEventHandler( pobjUID, name ) ;
}
/*-----------------------------------------------------------------------------------*/
int sciInitIsEventHandlerEnable( char * pobjUID, BOOL enable )
{
    // FIXME
    abort();
#if 0
        if(sciGetEntityType( pobjUID ) == SCI_FIGURE)
    {
        sciFigure * ppFigure = pFIGURE_FEATURE(pobjUID) ;
        /*
        ** If we try to enable an empty Event Handler
        ** raise a Warning.
        */
        if (ppFigure != NULL
            && ppFigure->eventHandler != NULL
            && (strcmp(ppFigure->eventHandler, "") != 0 || enable == FALSE))
        {
            pFIGURE_FEATURE(pobjUID)->isEventHandlerEnable = enable ;

            /* Java is called to enable or disable the listener */
            if (!isFigureModel(pobjUID))
            {
                setFigureEventHandlerEnabled(sciGetNum(pobjUID), enable);
            }
        }
        else
        {
            Scierror(999, _("%s: Can't enable a void event handler.\n"), "sciInitEventHandler") ;
        }
        return 0 ;
    }
    else
    {
        printSetGetErrorMessage("event_handler");
        return -1 ;
    }
#endif
        return -1;
}
/*-----------------------------------------------------------------------------------*/
int sciSetIsEventHandlerEnable( char * pobjUID, BOOL enable )
{
    if ( sciGetIsEventHandlerEnable((sciPointObj*)pobjUID) == enable )
    {
        /* nothing to do */
        return 1 ;
    }

    return sciInitIsEventHandlerEnable( pobjUID, enable ) ;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Set data-bounds defined by the user.
 * @param bounds [Xmin,Xmax,Ymain,Ymax,Zmin,Zmax] vector.
 */
int sciSetDataBounds( char * pobjUID, double bounds[6] )
{
    // FIXME
    abort();
#if 0
        int i;
    switch( sciGetEntityType(pobjUID) )
    {
    case SCI_SUBWIN:
        for ( i = 0 ; i < 6 ; i++ )
        {
            pSUBWIN_FEATURE(pobjUID)->SRect[i] = bounds[i] ;
        }
        return 0;
    case SCI_SURFACE:
        for ( i = 0 ; i < 6 ; i++ )
        {
            pSURFACE_FEATURE(pobjUID)->ebox[i] = bounds[i] ;
        }
        return 0;
    default:
        printSetGetErrorMessage("data_bounds");
        return -1 ;

    }
#endif
    return -1;
}
/*-----------------------------------------------------------------------------------*/
/**
 * Set the displayed data bounds of a subwin object.
 */
int sciSetRealDataBounds(char * pobjUID, const double bounds[6])
{
     // FIXME
    abort();
#if 0
       int i;
    switch( sciGetEntityType(pobjUID) )
    {
    case SCI_SUBWIN:
        for ( i = 0 ; i < 6 ; i++ )
        {
            pSUBWIN_FEATURE(pobjUID)->FRect[i] = bounds[i] ;
        }
        return 0;
    default:
        printSetGetErrorMessage("data_bounds");
        return -1 ;

    }
#endif
    return -1;
}
/*-----------------------------------------------------------------------------------*/
/**
 * To set the pixmap mode of a figure to on or off
 */
int sciInitPixmapMode(char * pobjUID, BOOL onOrOff)
{
     // FIXME
    abort();
#if 0
       switch(sciGetEntityType(pobjUID))
    {
    case SCI_FIGURE:
        pFIGURE_FEATURE(pobjUID)->pixmapMode = onOrOff;
        return 0;
    default:
        printSetGetErrorMessage("pixmap");
        return -1;
    }
#endif
       return -1;
}
/*----------------------------------------------------------------------------------*/
/**
 * To set the pixmap mode of a figure to on or off
 */
int sciSetPixmapMode(char * pobjUID, BOOL onOrOff)
{
    if (sciGetPixmapMode((sciPointObj*)pobjUID) == onOrOff)
    {
        /* Nothing to do */
        return 1;
    }
    return sciInitPixmapMode(pobjUID, onOrOff);
}
/*----------------------------------------------------------------------------------*/
int sciInitTextPos( char * pobjUID, double posX, double posY, double posZ)
{
    // FIXME
    abort();
#if 0
        switch(sciGetEntityType(pobjUID))
    {
    case SCI_TEXT:
        pTEXT_FEATURE(pobjUID)->x = posX;
        pTEXT_FEATURE(pobjUID)->y = posY;
        pTEXT_FEATURE(pobjUID)->z = posZ;
        return 0;
    case SCI_LABEL:
        return sciInitTextPos(pLABEL_FEATURE(pobjUID)->text, posX, posY, posZ);
    default:
        printSetGetErrorMessage("data");
        return -1;
    }
#endif
        return -1;
}
/*----------------------------------------------------------------------------------*/
/**
 * Set the position of a label or text object.
 */
int sciSetTextPos( char * pobjUID, double posX, double posY, double posZ)
{
    double curPos[3];
    sciGetTextPos((sciPointObj*)pobjUID, curPos);
    if ( curPos[0] == posX && curPos[1] == posY && curPos[2] == posZ )
    {
        /* nothing to do */
        return 1;
    }
    return sciInitTextPos(pobjUID, posX, posY, posZ);
}
/*----------------------------------------------------------------------------------*/
int sciInitAutoTicks(char * pobjUID, BOOL autoTicksX, BOOL autoTicksY, BOOL autoTicksZ)
{
    // FIXME
    abort();
#if 0
        switch(sciGetEntityType(pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->axes.auto_ticks[0] = autoTicksX;
        pSUBWIN_FEATURE(pobjUID)->axes.auto_ticks[1] = autoTicksY;
        pSUBWIN_FEATURE(pobjUID)->axes.auto_ticks[2] = autoTicksZ;
        return 0;
    default:
        printSetGetErrorMessage("auto_ticks");
        return -1;
    }
#endif
        return -1;
}
/*----------------------------------------------------------------------------------*/
int sciSetAutoTicks(char * pobjUID, BOOL autoTicksX, BOOL autoTicksY, BOOL autoTicksZ)
{
    BOOL curAutoTicks[3];
    sciGetAutoTicks((sciPointObj*)pobjUID, curAutoTicks);

    if (curAutoTicks[0] == autoTicksX && curAutoTicks[1] == autoTicksY && curAutoTicks[2] == autoTicksZ)
    {
        // nothing to do
        return 1;
    }

    return sciInitAutoTicks(pobjUID, autoTicksX, autoTicksY, autoTicksZ);

}
/*----------------------------------------------------------------------------------*/
/**
 * Specify a new zoom box for a subwin object.
 * @param zoomBox [xMin, xMax, yMin, yMax, zMin, zMax] vector.
 */
int sciSetZoomBox(char * pobjUID, const double zoomBox[6])
{
    // FIXME
    abort();
#if 0
        switch(sciGetEntityType(pobjUID))
    {
    case SCI_SUBWIN:
        pSUBWIN_FEATURE(pobjUID)->ZRect[0] = zoomBox[0];
        pSUBWIN_FEATURE(pobjUID)->ZRect[1] = zoomBox[1];
        pSUBWIN_FEATURE(pobjUID)->ZRect[2] = zoomBox[2];
        pSUBWIN_FEATURE(pobjUID)->ZRect[3] = zoomBox[3];
        pSUBWIN_FEATURE(pobjUID)->ZRect[4] = zoomBox[4];
        pSUBWIN_FEATURE(pobjUID)->ZRect[5] = zoomBox[5];
        return 0;
    default:
        printSetGetErrorMessage("zoom_box");
        return -1;
    }
#endif
        return -1;
}
/*----------------------------------------------------------------------------------*/
int sciInitImmediateDrawingMode(char * pobjUID, BOOL autoRedraw)
{
     // FIXME
    abort();
#if 0
       switch(sciGetEntityType(pobjUID))
    {
    case SCI_FIGURE:
        pFIGURE_FEATURE(pobjUID)->auto_redraw = autoRedraw;
        return 0;
    default:
        printSetGetErrorMessage("immediate_drawing");
        return -1;
    }
#endif
       return -1;
}
/*----------------------------------------------------------------------------------*/
int sciSetImmediateDrawingMode(char * pobjUID, BOOL autoRedraw)
{
    // FIXME
    abort();
#if 0
        if (sciGetImmediateDrawingMode(pobjUID) == autoRedraw)
    {
        // nothing to do
        return 1;
    }
    return sciInitImmediateDrawingMode(pobjUID, autoRedraw);
#endif
    return -1;
}
/*----------------------------------------------------------------------------------*/
/**
 * Check that a color index is within the colormap range or not
 * @param pobjUID object conatining the color
 */
BOOL sciCheckColorIndex(char * pobjUID, int colorIndex)
{
    return (colorIndex >= -2) && (colorIndex <= sciGetNumColors(pobjUID) + 2);
}
/*----------------------------------------------------------------------------------*/
