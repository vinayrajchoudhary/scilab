// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA - Michael Baudin
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// optim.tst --
//   Test the optim command with the Rosenbrock test case
//   in the case where the cost function is provided as a Fortran 
//   routine and use the "in" option.
//
//   Note : the following source code was copied from optimization/sci_gateway/fortran/Ex-optim.f
//   Thus, the "genros" function from Ex-optim.f is not needed anymore.
//
// 
// Define a fortran source code and compile it (fortran compiler required)
//
fortransource=['      subroutine rosenf(ind,n,x,f,g,izs,rzs,dzs)'
'C     -------------------------------------------'
'c     Example of cost function given by a subroutine'
'c     if n<=2 returns ind=0'
'c     f.bonnans, oct 86'
'      implicit double precision (a-h,o-z)'
'      real rzs(1)'
'      double precision dzs(*)'
'      dimension x(n),g(n),izs(*)'
'      common/nird/nizs,nrzs,ndzs'
'      if (n.lt.3) then'
'        ind=0'
'        return'
'      endif'
'      if(ind.eq.10) then'
'         nizs=2'
'         nrzs=1'
'         ndzs=2'
'         return'
'      endif'
'      if(ind.eq.11) then'
'         izs(1)=5'
'         izs(2)=10'
'         dzs(2)=100.0d+0'
'         return'
'      endif'
'      if(ind.eq.2)go to 5'
'      if(ind.eq.3)go to 20'
'      if(ind.eq.4)go to 5'
'      ind=-1'
'      return'
'5     f=1.0d+0'
'      do 10 i=2,n'
'        im1=i-1'
'10      f=f + dzs(2)*(x(i)-x(im1)**2)**2 + (1.0d+0-x(i))**2'
'      if(ind.eq.2)return'
'20    g(1)=-4.0d+0*dzs(2)*(x(2)-x(1)**2)*x(1)'
'      nm1=n-1'
'      do 30 i=2,nm1'
'        im1=i-1'
'        ip1=i+1'
'        g(i)=2.0d+0*dzs(2)*(x(i)-x(im1)**2)'
'30      g(i)=g(i) -4.0d+0*dzs(2)*(x(ip1)-x(i)**2)*x(i) - '
'     &        2.0d+0*(1.0d+0-x(i))'
'      g(n)=2.0d+0*dzs(2)*(x(n)-x(nm1)**2) - 2.0d+0*(1.0d+0-x(n))'
'      return'
'      end'];
mputl(fortransource,TMPDIR+'/rosenf.f')
// compile the C code
libpath=ilib_for_link('rosenf','rosenf.o',[],'f',TMPDIR+'/Makefile');
// incremental linking
linkid=link(libpath,'rosenf','f');
//
// Define some constants
//
Leps=8.e-5;
bs=10.*ones(1,5);
bi=-bs;
x0=0.12*bs;
epsx=1.e-15*x0;
xopt=.1*bs;
//
// Solve the problem
//
[f,x,g]=optim('rosenf',x0,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'gc','in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
//

[f,x,g]=optim('rosenf',x0,'nd','in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end

[f,x,g]=optim('rosenf',x0,'qn',1,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'gc',1,50,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
//
[f,x,g]=optim('rosenf',x0,'nd',1,50,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end

[f,x1,g]  =optim('rosenf',x0,   'ar',100,6,'in');
[f,x,g,to]=optim('rosenf',x0,   'ar',100,3,'in');
[f,x,g,to]=optim('rosenf',x ,to,'ar',100,3,'in');
if norm(x-x1)/norm(x-xopt) > 0.1 then  pause,end
[f,x1,g]=optim('rosenf','b',bi,bs,x0,'ar',100,6,'in');
[f,x,g,to]=optim('rosenf','b',bi,bs,x0,'ar',100,3,'in');
[f,x,g]   =optim('rosenf','b',bi,bs,x,to,'ar',100,3,'in');
if norm(x-x1)/norm(x-xopt) > 0.1 then  pause,end
// 
// Test all possible stop criteria settings 
//
[f,x,g]=optim('rosenf',x0,'ar','in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'ar',100,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'ar',100,100,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'ar',100,100,%eps,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'ar',100,100,%eps,%eps,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'ar',100,100,10.*%eps,%eps,epsx,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',x0,'gc','ar',100,100,%eps,%eps,epsx,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
//
[f,x,g]=optim('rosenf','b',bi,bs,x0,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf','b',bi,bs,x0,'gc','in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x]=optim('rosenf','b',bi,bs,x0,'ar',100,100,1.d-8,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g]=optim('rosenf',..
   'b',bi,bs,x0,'gc','ar',100,100,%eps,%eps,epsx,'in');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,to,td]=optim('rosenf',x0,'in','sd');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,ti]=optim('rosenf',x0,'gc','in','si');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,to,ti,td]=optim('rosenf',x0,to,'in','si','sd');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,td]=optim('rosenf',..
   'b',bi,bs,x0,'gc','ar',100,100,%eps,%eps,epsx,'in','sd');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,ti]=optim('rosenf',x0,'gc','ar',100,100,%eps,'in','si');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,ti,td]=optim('rosenf',..
    x0,'gc','ar',100,100,%eps,'in','si','sd');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
[f,x,g,ti,td]=optim('rosenf',..
    x0,'gc','ar',100,100,%eps,'in','ti',ti,'td',td,'si','sd');
if abs(f-1+norm(x-xopt) ) > Leps then pause,end
// Clean-up
ulink(linkid)
