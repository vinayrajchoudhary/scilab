// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 3294 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3294
//
// <-- Short Description -->
// g = m6loadg(pathconvert(SCI+"\modules\metanet\tests\unit_tests\mesh100.graph",%f,%t)) fails 

ierr = execstr("g=m6loadg(pathconvert(SCI+""\modules\metanet\tests\unit_tests\mesh100.graph"",%f,%t));","errcatch");
if ierr <> 0 then pause,end                    