// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// nmplot_boxproblemA.sce --
//   Show that the Box algorithm is able to reproduce the 
//   numerical experiment presented in Box's paper.
//

//
// boxproblemA --
//   Computes the Box problem A cost function and 
//   inequality constraints.
//
// Arguments
//   x: the point where to compute the function
//   index : the stuff to compute
//   data : the parameters of Box cost function
// Note
//  The following protocol is used
//  * if index=1, or no index, returns the value of the cost 
//    function (default case)
//  * if index=2, returns the value of the nonlinear inequality 
//    constraints, as a row array
//  * if index=3, returns an array which contains
//    at index #0, the value of the cost function  
//    at index #1 to the end is the list of the values of the nonlinear 
//    constraints
//  The inequality constraints are expected to be positive.
//
function f = boxproblemA ( x , index , data )
  if (~isdef('index','local')) then
    index = 1
  end
  b = x(2) + 0.01 * x(3)
  x6 = (data.k1 + data.k2 * x(2) ...
            + data.k3 * x(3) + data.k4 * x(4) + data.k5 * x(5)) * x(1)
  y1 = data.k6 + data.k7 * x(2) + data.k8 * x(3) ...
            + data.k9 * x(4) + data.k10 * x(5)
  y2 = data.k11 + data.k12 * x(2) + data.k13 * x(3) ...
            + data.k14 * x(4) + data.k15 * x(5)
  y3 = data.k16 + data.k17 * x(2) + data.k18 * x(3) ...
            + data.k19 * x(4) + data.k20 * x(5)
  y4 = data.k21 + data.k22 * x(2) + data.k23 * x(3) ...
            + data.k24 * x(4) + data.k25 * x(5)
  x7 = ( y1 + y2 + y3 ) * x(1)
  x8 = (data.k26 + data.k27 * x(2) + data.k28 * x(3) ...
            + data.k29 * x(4) ...
            + data.k30 * x(5) ) * x(1) + x6 + x7
  if ( index==1 | index==3 ) then
    f = (data.a2 * y1 + data.a3 * y2 + data.a4 * y3 + data.a5 * y4 ...
             + 7840 * data.a6 - 100000 * data.a0 ...
             - 50800 * $b * data.a7 + data.k31 + data.k32 * x(2) + data.k33 * x(3) ...
             + data.k34 * x(4) + data.k35 * x(5)) * x(1) ...
             - 24345 + data.a1 * x6
    f = -f
  end
  if ( index==2 | index==3 ) then
      c1 = x6
      c2 = 294000 - x6
      c3 = x7
      c4 = 294000 - x7
      c5 = x8
      c6 = 277200 - x8
  end
  select index
  case 1 then
    result = f
  case 2 then
    result = [c1 c2 c3 c4 c5 c6]
  case 3 then
    result = [f c1 c2 c3 c4 c5 c6]
  else
    errmsg = sprintf("Unexpected index %d" , index);
    error(errmsg);
  end
endfunction

boxparams = struct()
boxparams.a0 = 9
boxparams.a1 = 15
boxparams.a2 = 50
boxparams.a3 = 9.583
boxparams.a4 = 20
boxparams.a5 = 15
boxparams.a6 = 6
boxparams.a7 = 0.75
boxparams.k1 = -145421.402
boxparams.k2 = 2931.1506
boxparams.k3 = -40.427932
boxparams.k4 = 5106.192
boxparams.k5 = 15711.36
boxparams.k6 = -161622.577
boxparams.k7 = 4176.15328
boxparams.k8 = 2.8260078
boxparams.k9 = 9200.476
boxparams.k10 = 13160.295
boxparams.k11 = -21686.9194
boxparams.k12 = 123.56928
boxparams.k13 = -21.1188894
boxparams.k14 = 706.834
boxparams.k15 = 2898.573
boxparams.k16 = 28298.388
boxparams.k17 = 60.81096
boxparams.k18 = 31.242116
boxparams.k19 = 329.574
boxparams.k20 = -2882.082
boxparams.k21 = 74095.3845
boxparams.k22 = -306.262544
boxparams.k23 = 16.243649
boxparams.k24 = -3094.252
boxparams.k25 = -5566.2628
boxparams.k26 = -26237.0
boxparams.k27 = 99.0
boxparams.k28 = -0.42
boxparams.k29 = 1300.0
boxparams.k30 = 2100.0
boxparams.k31 = 925548.252
boxparams.k32 = -61968.8432
boxparams.k33 = 23.3088196
boxparams.k34 = -27097.648
boxparams.k35 = -50843.766




nm = nmplot_new ();
nm = nmplot_configure(nm,"-numberofvariables",2);
nm = nmplot_configure(nm,"-function",boxproblemA);
nm = nmplot_configure(nm,"-costfargument",boxparams);
nm = nmplot_configure(nm,"-x0",[1.0 1.0]');
nm = nmplot_configure(nm,"-maxiter",200);
nm = nmplot_configure(nm,"-maxfunevals",300);
nm = nmplot_configure(nm,"-simplex0method","given");
nm = nmplot_configure(nm,"-tolsimplexizerelative",1.e-3);
nm = nmplot_configure(nm,"-coords0",coords0);
nm = nmplot_configure(nm,"-simplex0length",1.0);
nm = nmplot_configure(nm,"-method","box");
nm = nmplot_configure(nm,"-verbose",1);
nm = nmplot_configure(nm,"-verbosetermination",1);
// Configure like Box
nm = neldermead_configure(nm,"-boundsmin",[0.0 1.2 20.0 9.0 6.0]);
nm = neldermead_configure(nm,"-boundsmax",[5.0 2.5 60.0 9.3 7.0]);
nm = neldermead_configure(nm,"-simplex0method","randbounds");
nm = neldermead_configure(nm,"-nbineqconst",6);
//
// Perform optimization
//
nm = nmplot_search(nm);
nm = nmplot_destroy(nm);

