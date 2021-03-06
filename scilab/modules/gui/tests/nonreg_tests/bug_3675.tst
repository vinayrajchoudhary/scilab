// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Vincent COUVERT
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->

//
// <-- Non-regression test for bug 3675 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3675
//
// <-- Short Description -->
//    Scilab 5.0.2 has issues when saving/loading gui (uicontrols,figure...)

warning("off");

f=figure();

h = uicontrol(f,"style","listbox", ..
    "position", [10 10 150 160],..
    "tag", "listbox_bug_3675");

h2 = uicontrol(...
    "parent", f,...
    "relief", "groove",...
    "style", "frame",...
    "position", [200 50 150 200],...
    "tag", "unnom");

// fill the list
set(h, "string", "un|mot|accentué");
// select item 1 and 3 in the list
set(h, "value", [1 3]);

// save
save(TMPDIR + filesep() + "bug_3675.bin")

// close the figure
delete(f);

// load and redisplay
load(TMPDIR + filesep() + "bug_3675.bin");

listbox = findobj("tag", "listbox_bug_3675");
if or(get(listbox, "string") <> ["un","mot","accentué"]) then pause; end




