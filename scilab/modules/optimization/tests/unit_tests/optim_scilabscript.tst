// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA - Michael Baudin
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// optim_script.tst --
//   Test the optim command with the Rosenbrock test case 
//   in the case where the cost function is a Scilab function.
//   The expected solution is x=(1,...,1) where f(x)=0
//
Leps=2.e-4;
bs=[5 5];
bi=-bs;
x0=1.05*[1 1];
xopt=[1 1];
function [f,g,ind]=rose(x,ind)
  a=x(2)-x(1)^2 
  b=1-x(2)
  f=50.*a^2 + b^2
  g(1)=-400.*x(1)*a
  g(2)=200.*a -2.*b
endfunction
// Compile the function for faster computation
comp(rose);
[f,x,g,tr]=optim(rose,x0,'qn','ar',50);
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g]=optim(rose,x0,tr,'ar',50);
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g]=optim(rose,x0,'gc','ar',50);
if abs(f+norm(x-xopt)) > Leps then pause,end
//
[f,x,g]=optim(rose,x0,'nd','ar',50);
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g]=optim(rose,'b',bi,bs,x0,'qn','ar',25);
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g]=optim(rose,'b',bi,bs,x0,'gc','ar',50);
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g,td]=optim(rose,x0,'gc','ar',50,'sd');
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g,ti]=optim(rose,x0,'gc','ar',50,'si');
if abs(f+norm(x-xopt)) > Leps then pause,end
[f,x,g,ti,td]=optim(rose,x0,'gc','ar',50,'si','sd');
if abs(f+norm(x-xopt)) > Leps then pause,end

