// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Vincent COUVERT
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

//
// <-- Non-regression test for bug 3389 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3389
//
// <-- Short Description -->
//    if figure() is called with non-existing properties, Scilab crashes

// try to set uicontrol/uimenu properties to a figure ...
figure("enable", "on",...
    "label", "toto",...
    "string", "toto",...
    "backgroundcolor", [0.5 0.5 0.5],...
    "foregroundcolor", [0.5 0.5 0.5],...
    "fontweight", "bold",...
    "fontunits", "pixels",...
    "fontsize", 12,...
    "fontangle", "italic",...
    "min", 10,...
    "max", 20,...
    "tag", "toto",...
    "listboxtop", 1,...
    "value", 1,...
    "units", "pixels",...
    "relief", "raised",...
    "horizontalalignment", "right",...
    "verticalalignment", "left",...
    "fontname", "arial",...
    "sliderstep", [1 2]);