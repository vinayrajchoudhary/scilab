// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Michael Baudin
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// Test with 2 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
[xcomputed, flag, err, iter, res]=pcg(A,b);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
if flag<>0 then pause,end
if err>%eps then pause,end
if iter>2 then pause,end
// Test with 3 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
tol = 100*%eps;
[xcomputed, flag, err, iter, res]=pcg(A,b,tol);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
if (err > tol) then pause,end
// Test with 4 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
tol = 100*%eps;
maxit = 10;
[xcomputed, flag, err, iter, res]=pcg(A,b,tol,maxit);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
// Test with 5 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
tol = 100*%eps;
maxit = 10;
M1=[1,0;0,1];
[xcomputed, flag, err, iter, res]=pcg(A,b,tol,maxit,M1);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
// Test with 6 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
tol = 100*%eps;
maxit = 10;
M1=[1,0;0,1];
M2=[1,0;0,1];
[xcomputed, flag, err, iter, res]=pcg(A,b,tol,maxit,M1,M2);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
// Test with 7 input arguments and all output arguments
A=[10,1;1,10];
b=[11;11];
tol = 100*%eps;
maxit = 10;
M1=[1,0;0,1];
M2=[1,0;0,1];
x0=[1;1];
[xcomputed, flag, err, iter, res]=pcg(A,b,tol,maxit,M1,M2,x0);
xexpected=[1;1];
if norm(xcomputed-xexpected)>%eps then pause,end
// Test with non-positionnal input parameters so that 0 iteration can happen
A=[100,1;1,10];
b=[101;11];
[xcomputed, flag, err, iter, res]=pcg(A,b,maxIter=0);
if (iter <> 0) then pause,end
// Test with non-positionnal input parameters so that 1 iteration is sufficient
A=[100,1;1,10];
b=[101;11];
[xcomputed, flag, err, iter, res]=pcg(A,b,tol=0.1);
if (iter <> 1) then pause,end
// Test with non-positionnal input parameters so that pre-conditionning is necessary
A=[100,1;1,0.0101]
b=[101;11];
M=A**-1
[xcomputed, flag, err, iter, res]=pcg(A,b,%M=M,maxIter=3,tol=%eps);
if (flag <> 0) then pause,end
// Test with non-positionnal input parameters so that good initialization generates 0 iterations
A=[100,1;1,10.]
b=[101;11];
[xcomputed, flag, err, iter, res]=pcg(A,b,x0=[1.;1.]);
if (iter<>0) then pause,end
// Test the special case where b=0
A=[100,1;1,10.]
b=[0;0];
[xcomputed, flag, err, iter, res]=pcg(A,b);
xexpected=[0;0];
if norm(xcomputed-xexpected)>%eps then pause,end
if (flag<>0) then pause,end
if (err>%eps) then pause,end
if (iter<>0) then pause,end
