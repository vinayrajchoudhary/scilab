// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 3306 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3306
//
// <-- Short Description -->
// Wildcards should not be interpreted as such in completion, but as literal text.

// <-- JVM NOT MANDATORY -->

ilib_verbose(0);

exec('SCI/modules/completion/tests/utilities/build_primitives.sce',-1);
exec('SCI/modules/completion/tests/utilities/loader.sce',-1);

// get*<TAB>
currentline = 'get*';

r = getpartlevel(currentline);
if r <> '' then pause,end

r = getfilepartlevel(currentline);
if r <> '' then pause,end

r = completeline(currentline,'',getpartlevel(currentline),getfilepartlevel(currentline),%f);
if r <> currentline then pause,end;
