// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


//
// assert_close --
//   Returns 1 if the two real matrices computed and expected are close,
//   i.e. if the relative distance between computed and expected is lesser than epsilon.
// Arguments
//   computed, expected : the two matrices to compare
//   epsilon : a small number
//
function flag = assert_close ( computed, expected, epsilon )
  if expected==0.0 then
    shift = norm(computed-expected);
  else
    shift = norm(computed-expected)/norm(expected);
  end
  if shift < epsilon then
    flag = 1;
  else
    flag = 0;
  end
  if flag <> 1 then pause,end
endfunction
//
// assert_equal --
//   Returns 1 if the two real matrices computed and expected are equal.
// Arguments
//   computed, expected : the two matrices to compare
//   epsilon : a small number
//
function flag = assert_equal ( computed , expected )
  if computed==expected then
    flag = 1;
  else
    flag = 0;
  end
  if flag <> 1 then pause,end
endfunction
//
// gould.nonconvex --
//   The Gould test case with additionnal inequality constraints.
// Arguments
//    x : the point where to compute the cost
//    index : a flag which states what is to compute
//    * if index=1, or no index, returns the value of the cost 
//      function (default case)
//    * if index=2, returns the value of the nonlinear inequality 
//      constraints, as a row array
//    * if index=3, returns an array which contains
//      at index #0, the value of the cost function  
//      at index #1 to the end is the list of the values of the nonlinear 
//      constraints
//  Discussion:
//    The problem is to minimize a cost function with 4 non linear constraints.
//    This is Problem 4.1 in Subrahmanyam, extracted from Gould.
//    Non convex.
//    The constraint region is a narrow winding (half-moon shaped) valley.
//    Solution showed with tolerance 1.e-8.
//
//  Reference:
//    An extension of the simplex method to constrained
//    nonlinear optimization
//    M.B. Subrahmanyam
//    Journal of optimization theory and applications
//    Vol. 62, August 1989
//
//    Gould F.J.
//    Nonlinear Tolerance Programming
//    Numerical methods for Nonlinear optimization
//    Edited by F.A. Lootsma, pp 349-366, 1972
//
function result = gouldnonconvex ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index==1 | index==3 ) then
    f = (x(1) - 10.0 )^3 + ( x(2) - 20.0 ) ^ 3
  end
  if ( index==2 | index==3 ) then
    c1 = x(1) - 13.0
    c2 = ( x(1) - 5.0 )^2  + (x(2) - 5.0 )^2 - 100.0
    c3 = -( x(1) - 6.0 )^2 - (x(2) - 5.0 )^2 + 82.81
    c4 = x(2)
  end
  select index
  case 1 then
      result = f
      mprintf( "Computed f = %e\n", f);
  case 2
      result = [c1 c2 c3 c4]
      mprintf( "Computed constraints = %e %e %e %e\n", c1 , c2 , c3 , c4);
  case 3
      result = [f c1 c2 c3 c4]
      mprintf( "Computed f = %e and constraints = %e %e %e %e\n", f , c1 , c2 , c3 , c4);
  else
    errmsg = sprintf("Unknown index %d", index )
    error(errmsg)
  end
endfunction
//
// Test optimbase_checkx0 method
//
// Test without anything
opt = optimbase_new ();
opt = optimbase_configure ( opt , "-numberofvariables",2);
opt = optimbase_configure ( opt , "-verbose",1);
[ opt , isok ] = optimbase_checkx0 ( opt );
assert_equal ( isok , %T );
opt = optimbase_destroy(opt);
//
// Test with satisfied/unsatisfied bounds constraints
opt = optimbase_new ();
opt = optimbase_configure ( opt , "-numberofvariables",2);
opt = optimbase_configure ( opt , "-verbose",1);
opt = optimbase_configure ( opt , "-boundsmin" , [-5.0 -5.0] );
opt = optimbase_configure ( opt , "-boundsmax" , [5.0 5.0] );
opt = optimbase_configure ( opt , "-x0", [1.0 1.0]' );
[ opt , isok ] = optimbase_checkx0 ( opt );
assert_equal ( isok , %T );
opt = optimbase_configure ( opt , "-x0",[-6.0 1.0]');
[ opt , isok ] = optimbase_checkx0 ( opt );
assert_equal ( isok , %F );
opt = optimbase_destroy(opt);
//
// Test with satisfied/unsatisfied nonlinear inequality constraints
opt = optimbase_new ();
opt = optimbase_configure ( opt , "-numberofvariables",2);
opt = optimbase_configure ( opt , "-verbose",1);
opt = optimbase_configure ( opt , "-nbineqconst",4);
opt = optimbase_configure ( opt , "-function" , gouldnonconvex );
opt = optimbase_configure ( opt , "-x0" , [ 14.0950013 , 0.8429636 ]');
[ opt , isok ] = optimbase_checkx0 ( opt );
assert_equal ( isok , %T );
opt = optimbase_configure ( opt , "-x0" , [ 14.0950013 , 0.0 ]');
[ opt , isok ] = optimbase_checkx0 ( opt );
assert_equal ( isok , %F );
opt = optimbase_destroy(opt);
