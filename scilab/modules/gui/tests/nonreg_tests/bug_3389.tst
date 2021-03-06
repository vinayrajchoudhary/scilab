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
f = figure();

execstr("f.enable = ""on""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "Enable") then pause; end

execstr("f.label = ""toto""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "Label") then pause; end

execstr("f.string = ""toto""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "String") then pause; end

execstr("f.backgroundcolor = [0.5 0.5 0.5]", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "BackgroundColor") then pause; end

execstr("f.foregroundcolor = [0.5 0.5 0.5]", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "ForegroundColor") then pause; end

execstr("f.fontweight = ""bold""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "FontWeight") then pause; end

f.fontunits = "pixels";

execstr("f.fontsize = 12", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "FontSize") then pause; end

execstr("f.fontangle = ""italic""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "FontAngle") then pause; end

f.min = 10;

f.max = 20;

f.tag = "toto";

f.listboxtop = 1;

f.value = 1;

execstr("f.relief = ""raised""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "Relief") then pause; end

execstr("f.horizontalalignment = ""right""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "HorizontalAlignment") then pause; end

execstr("f.verticalalignment = ""left""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "VerticalAlignment") then pause; end

execstr("f.fontname = ""arial""", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "FontName") then pause; end

execstr("f.sliderstep = [1 2]", "errcatch");
if lasterror()<>msprintf(gettext("No ''%s'' property for this object.\n"), "SliderStep") then pause; end
