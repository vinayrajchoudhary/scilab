// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Sylvestre Ledru
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 10126 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10126
//
// <-- Short Description -->
// sparse matrix insertion was failing (segfault and/or wrong results)

A=sprand(5,5,1);
A(7,1)=1; //A is correctly reshaped and the insertion is ok
B=full(A);
assert_checkequal(B(7,1),1);
assert_checkequal(size(A),[7,5]);

A(10,1)=2; // Was either doing a segfault or producing a bad result
B=full(A);
assert_checkequal(B(10,1),2);
assert_checkequal(size(A),[10,5]);