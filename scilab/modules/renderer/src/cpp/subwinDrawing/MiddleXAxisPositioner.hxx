/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Jean-Baptiste Silvy 
 * desc : Class specialized in drawing ticks  
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef _MIDDLE_X_AXIS_POSITIONER_HXX_
#define _MIDDLE_X_AXIS_POSITIONER_HXX_

#include "XAxisPositioner.hxx"

namespace sciGraphics
{

/**
 * Interface for determining on which edge of axes box an axe will be
 */
class MiddleXAxisPositioner : public XAxisPositioner
{
public:

  MiddleXAxisPositioner(DrawableSubwin * subwin);

  virtual ~MiddleXAxisPositioner(void);

  /**
   * Get the two bounds of this axis.
   */
  virtual void getAxisBounds(double startBound[3], double endBound[3]);

protected:

  /**
   * Compute the Y coordinate of the X axis segment
   * Select the one which on the back of the screen
   * @param zCoordinate Z coordinate of the X axis segment alredy computed by findZCoordinate
   * @return Y coordinate of the segment to draw
   */
  double findMiddleYCoordinate(double zCoordinate);

};

}

#endif