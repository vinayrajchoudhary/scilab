// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

java_file_to_test = "bug_3673.java";

my_test_path = pathconvert(SCI+"/modules/javasci/tests/nonreg_tests",%f,%f);
my_file_path = pathconvert(my_test_path+"/"+java_file_to_test,%f,%f);
exec (my_test_path+"/test_java.sci",-1);
if test_java(my_file_path) <> %T then pause,end;