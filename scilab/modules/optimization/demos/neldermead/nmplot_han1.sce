// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


//
// han1 --
//   Compute the cost function from the Han Phd Thesis
//   which exhibits a failure of the NM method.
// Reference 
//   Algorithms in Unconstrained Optimization
//   Han, Lixing
//   2000
//   Ph.D., The University of Connecticut
//
function f = han1 ( x )
  f = x(1)^2 + x(2) * (x(2) + 2.0) * (x(2) - 0.5) * (x(2) - 2.0);
endfunction


coords0 = [
0.0 0.0 1.0
-1.0 1.0 0.0
]


nm = nmplot_new ();
nm = nmplot_configure(nm,"-numberofvariables",2);
nm = nmplot_configure(nm,"-function",han1);
nm = nmplot_configure(nm,"-x0",[1.0 1.0]');
nm = nmplot_configure(nm,"-maxiter",50);
nm = nmplot_configure(nm,"-maxfunevals",300);
nm = nmplot_configure(nm,"-tolfunrelative",10*%eps);
nm = nmplot_configure(nm,"-tolxrelative",10*%eps);
nm = nmplot_configure(nm,"-simplex0method","given");
nm = nmplot_configure(nm,"-coords0",coords0);
nm = nmplot_configure(nm,"-simplex0length",1.0);
nm = nmplot_configure(nm,"-method","variable");
//nm = nmplot_configure(nm,"-verbose",1);
nm = nmplot_configure(nm,"-verbosetermination",1);
//
// Setup output files
//
nm = nmplot_configure(nm,"-simplexfn","han1-history-simplex.txt");
nm = nmplot_configure(nm,"-fbarfn","han1-history-fbar.txt");
nm = nmplot_configure(nm,"-foptfn","han1-history-fopt.txt");
nm = nmplot_configure(nm,"-sigmafn","han1-history-sigma.txt");
//
// Perform optimization
//
nm = nmplot_search(nm);
//
// Plot
//
[nm , xdata , ydata , zdata ] = nmplot_contour ( nm , xmin = -0.2 , xmax = 1.2 , ymin = -2.0 , ymax = 2.0 , nx = 50 , ny = 50 );
//[nm , xdata , ydata , zdata ] = nmplot_contour ( nm , xmin = -0.2 , xmax = 1.2 , ymin = -1.2 , ymax = 1.2 , nx = 50 , ny = 50 );
f = scf();
xset("fpf"," ")
contour ( xdata , ydata , zdata , 40 )
nmplot_simplexhistory ( nm );
xs2png(0,"han1-history-simplex.png");
deletefile("han1-history-simplex.txt");
deletefile("han1-history-fbar.txt");
deletefile("han1-history-fopt.txt");
deletefile("han1-history-sigma.txt");
nm = nmplot_destroy(nm);

