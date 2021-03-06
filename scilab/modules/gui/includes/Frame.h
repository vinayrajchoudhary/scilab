/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Vincent COUVERT
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef __FRAME_H__
#define __FRAME_H__

#include "ObjectStructure.h"
#include "returnProperty.h"
#include "dynlib_gui.h"
/**
 * Create a new Frame in Scilab GUIs
 *
 * @param sciObj the corresponding Scilab object
 */
GUI_IMPEXP void createFrame(sciPointObj * sciObj);

#endif /* !__FRAME_H__ */
