// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009-2010 - DIGITEO - Scilab Consortium Operational Team
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->
ilib_verbose(0);
mkdir(pathconvert(TMPDIR+"/booleanExample"));
cd(pathconvert(TMPDIR+"/booleanExample"));
copyfile(SCI+"/modules/api_scilab/tests/unit_tests/booleanExample.c",pathconvert(TMPDIR+"/booleanExample/booleanExample.c",%F));
cflags = "-I"+SCI+"/modules/localization/includes";
ilib_build("booleanExample",["booleanExample","booleanExample"],"booleanExample.c",[],"","",cflags);
exec("loader.sce");

a = %t;
b = %f;
c = [a,b;b,a;a,b;b,a];
d = c';
booleanExample(a) == a
booleanExample(b) == b
booleanExample(c) == c
booleanExample(d) == d