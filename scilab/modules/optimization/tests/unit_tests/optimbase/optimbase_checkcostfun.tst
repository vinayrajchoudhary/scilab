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
// Here, the cost function is OK
//
function y = rosenbrockOk (x)
  y = 100*(x(2)-x(1)^2)^2 + (1-x(1))^2;
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",2);
nm = optimbase_configure(nm,"-x0",[1.1 1.1]');
nm = optimbase_configure(nm,"-function",rosenbrockOk);
nm = optimbase_checkcostfun(nm);
nm = optimbase_destroy(nm);

//
// Here, the cost function is not callable
//
function y = rosenbrock2 (x)
  y = fdsmklqfjdsf;
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",2);
nm = optimbase_configure(nm,"-x0",[1.1 1.1]');
nm = optimbase_configure(nm,"-function",rosenbrock2);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: Cannot evaluate cost function at x0.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);

//
// Here, the cost function is callable, but returns a matrix,
// instead of a scalar.
//
function y = rosenbrock2 (x)
  y = ones(10,10);
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",2);
nm = optimbase_configure(nm,"-x0",[1.1 1.1]');
nm = optimbase_configure(nm,"-function",rosenbrock2);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: Call to cost function with x0 is not a scalar, but a 10 x 10 matrix.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);

//
// Test with good non linear constraints
//
function result = optimtestcase ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index == 1 | index == 3 ) then
    f = x(1)^2 + x(2)^2 + 2.0 * x(3)^2 + x(4)^2 ...
      - 5.0 * x(1) - 5.0 * x(2) - 21.0 * x(3) + 7.0 * x(4)
  end
  if ( index == 2 | index == 3 ) then
    c1 = - x(1)^2 - x(2)^2 - x(3)^2 - x(4)^2 ...
              - x(1) + x(2) - x(3) + x(4) + 8
    c2 = - x(1)^2 - 2.0 * x(2)^2 - x(3)^2 - 2.0 * x(4)^2 ...
              + x(1) + x(4) + 10.0
    c3 = - 2.0 * x(1)^2 - x(2)^2 - x(3)^2 - 2.0 * x(1) ...
              + x(2) + x(4) + 5.0
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3]
  case 3 then
    result = [f c1 c2 c3]
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",4);
nm = optimbase_configure(nm,"-function",optimtestcase);
nm = optimbase_configure(nm,"-x0",[0.0 0.0 0.0 0.0]');
nm = optimbase_configure(nm,"-nbineqconst",3);
nm = optimbase_checkcostfun(nm);
nm = optimbase_destroy(nm);

//
// Test with wrong  non linear constraints f(x0,2) is not a row vector
//
function result = optimtestcase2 ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index == 1 | index == 3 ) then
    f = x(1)^2 + x(2)^2 + 2.0 * x(3)^2 + x(4)^2 ...
      - 5.0 * x(1) - 5.0 * x(2) - 21.0 * x(3) + 7.0 * x(4)
  end
  if ( index == 2 | index == 3 ) then
    c1 = - x(1)^2 - x(2)^2 - x(3)^2 - x(4)^2 ...
              - x(1) + x(2) - x(3) + x(4) + 8
    c2 = - x(1)^2 - 2.0 * x(2)^2 - x(3)^2 - 2.0 * x(4)^2 ...
              + x(1) + x(4) + 10.0
    c3 = - 2.0 * x(1)^2 - x(2)^2 - x(3)^2 - 2.0 * x(1) ...
              + x(2) + x(4) + 5.0
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3].'
  case 3 then
    result = [f c1 c2 c3]
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",4);
nm = optimbase_configure(nm,"-function",optimtestcase2);
nm = optimbase_configure(nm,"-x0",[0.0 0.0 0.0 0.0]');
nm = optimbase_configure(nm,"-nbineqconst",3);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: The result of the cost function at (x0,index=2) has 3 rows, instead of only 1.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);

//
// Test with wrong  non linear constraints f(x0,2) is a row vector with 5 components instead of 3
//
function result = optimtestcase3 ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index == 1 | index == 3 ) then
    f = x(1)^2 + x(2)^2 + 2.0 * x(3)^2 + x(4)^2 ...
      - 5.0 * x(1) - 5.0 * x(2) - 21.0 * x(3) + 7.0 * x(4)
  end
  if ( index == 2 | index == 3 ) then
    c1 = - x(1)^2 - x(2)^2 - x(3)^2 - x(4)^2 ...
              - x(1) + x(2) - x(3) + x(4) + 8
    c2 = - x(1)^2 - 2.0 * x(2)^2 - x(3)^2 - 2.0 * x(4)^2 ...
              + x(1) + x(4) + 10.0
    c3 = - 2.0 * x(1)^2 - x(2)^2 - x(3)^2 - 2.0 * x(1) ...
              + x(2) + x(4) + 5.0
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3 0.0 0.0]
  case 3 then
    result = [f c1 c2 c3]
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",4);
nm = optimbase_configure(nm,"-function",optimtestcase3);
nm = optimbase_configure(nm,"-x0",[0.0 0.0 0.0 0.0]');
nm = optimbase_configure(nm,"-nbineqconst",3);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: The result of the cost function at (x0,index=2) has 5 columns, instead of the number of constraints 3.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);

//
// Test with wrong  non linear constraints f(x0,3) is a column vector
//
function result = optimtestcase4 ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index == 1 | index == 3 ) then
    f = x(1)^2 + x(2)^2 + 2.0 * x(3)^2 + x(4)^2 ...
      - 5.0 * x(1) - 5.0 * x(2) - 21.0 * x(3) + 7.0 * x(4)
  end
  if ( index == 2 | index == 3 ) then
    c1 = - x(1)^2 - x(2)^2 - x(3)^2 - x(4)^2 ...
              - x(1) + x(2) - x(3) + x(4) + 8
    c2 = - x(1)^2 - 2.0 * x(2)^2 - x(3)^2 - 2.0 * x(4)^2 ...
              + x(1) + x(4) + 10.0
    c3 = - 2.0 * x(1)^2 - x(2)^2 - x(3)^2 - 2.0 * x(1) ...
              + x(2) + x(4) + 5.0
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3]
  case 3 then
    result = [f c1 c2 c3].'
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",4);
nm = optimbase_configure(nm,"-function",optimtestcase4);
nm = optimbase_configure(nm,"-x0",[0.0 0.0 0.0 0.0]');
nm = optimbase_configure(nm,"-nbineqconst",3);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: The result of the cost function at (x0,index=3) has 4 rows, instead of only 1.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);

//
// Test with wrong  non linear constraints f(x0,3) is a row vector with 5 columns instead of 4
//
function result = optimtestcase5 ( x , index )
  if (~isdef('index','local')) then
    index = 1
  end
  if ( index == 1 | index == 3 ) then
    f = x(1)^2 + x(2)^2 + 2.0 * x(3)^2 + x(4)^2 ...
      - 5.0 * x(1) - 5.0 * x(2) - 21.0 * x(3) + 7.0 * x(4)
  end
  if ( index == 2 | index == 3 ) then
    c1 = - x(1)^2 - x(2)^2 - x(3)^2 - x(4)^2 ...
              - x(1) + x(2) - x(3) + x(4) + 8
    c2 = - x(1)^2 - 2.0 * x(2)^2 - x(3)^2 - 2.0 * x(4)^2 ...
              + x(1) + x(4) + 10.0
    c3 = - 2.0 * x(1)^2 - x(2)^2 - x(3)^2 - 2.0 * x(1) ...
              + x(2) + x(4) + 5.0
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3]
  case 3 then
    result = [f c1 c2 c3 0.0]
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction
nm = optimbase_new ();
nm = optimbase_configure(nm,"-numberofvariables",4);
nm = optimbase_configure(nm,"-function",optimtestcase5);
nm = optimbase_configure(nm,"-x0",[0.0 0.0 0.0 0.0]');
nm = optimbase_configure(nm,"-nbineqconst",3);
cmd = "nm = optimbase_checkcostfun(nm);";
execstr(cmd,"errcatch");
computed = lasterror();
expected = "optimbase_checkcostfun: The result of the cost function at (x0,index=3) has 5 columns, instead of the number of constraints 3 + 1.";
assert_equal ( computed , expected );
nm = optimbase_destroy(nm);
