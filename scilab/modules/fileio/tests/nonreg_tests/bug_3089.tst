// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 3089 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3089
//
// <-- Short Description -->
// chdir seems to have problems with directory names containing nordic characters like � � and �.

newdir = TMPDIR + filesep() +'���_dir';
r = removedir(newdir);
if r <> %f then pause,end

r = mkdir(newdir);
if r <> 1 then pause,end

r = cd(newdir);
if r == [] then pause,end

r = chdir(newdir);
if r <> %t then pause,end

r = chdir(TMPDIR);
if r <> %t then pause,end

r = removedir(newdir);
if r <> %t then pause,end

