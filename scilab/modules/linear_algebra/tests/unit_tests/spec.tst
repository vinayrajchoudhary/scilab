// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA Michael Baudin
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//define tools
function A=testmat1(a,n)
	//eigen values are given by a dilation of nth roots of 1
	A=diag(a*ones(1,n-1),1)+diag((1/a)*ones(1,n-1),-1)
	A(1,n)=1/a;A(n,1)=a
endfunction
function r=Err(x)
	r=norm(x,1)
endfunction
rand('normal')

//==========================================================================
//==============================     spec     ============================== 
//==========================================================================

function r=Checktestmat1(a,n)
   A=testmat1(a,n);S=spec(A);
   SR=real(S);SI=imag(S);
   dt=2*%i*%pi/n;Z=exp(dt*(1:n)');ZR=real(Z*((1+a*a')/a));
   ZI=-imag(Z*((a*a'-1)/a));
   r=max(norm(sort(SR)-sort(ZR)),norm(sort(SI)-sort(ZI)))
endfunction
function A=testmat2(a,n)
	//eigen values are given by a dilation of nth roots of 1
	A=testmat1(a,n);A=A+A'
endfunction
function r=Checktestmat2(a,n)
   A=testmat2(a,n);S=spec(A);
   SR=real(S);SI=imag(S);
   dt=2*%i*%pi/n;Z=exp(dt*(1:n)');
   ZR=2*real(Z*((1+a*a')/a));ZI=0*ZR;
   r=max(norm(sort(SR)-sort(ZR)),norm(sort(SI)-sort(ZI)))
endfunction



//Empty matrix
A=[];
S=spec(A);
if S<>[] then pause,end
//Matrix with Inf or Nan (test de la detection d'erreur
if execstr('spec([%inf 1;2 3])','errcatch')==0 then pause,end
if execstr('spec([1 %nan;2 3])','errcatch')==0 then pause,end

if execstr('spec([%inf %i;2 3])','errcatch')==0 then pause,end
if execstr('spec([%i %i;%nan 3])','errcatch')==0 then pause,end

//Small dimension
//---------------
//Real Case
//Unsymetric
if Checktestmat1(3,5)>200*%eps then pause,end
[U,S]=spec(testmat1(3,5));
if Err(U*S/U-testmat1(3,5))>200*%eps then pause,end 
//Symmetric
if Checktestmat2(3,5)>200*%eps then pause,end
[U,S]=spec(testmat2(3,5));
if Err(U*S/U-testmat2(3,5))>200*%eps then pause,end 

//Complex Case
//Unsymetric
if Checktestmat1(3+2*%i,5)>200*%eps then pause,end
[U,S]=spec(testmat1(3+2*%i,5));
if Err(U*S/U-testmat1(3+2*%i,5))>200*%eps then pause,end 

//Symmetric
if Checktestmat2(3+2*%i,5)>200*%eps then pause,end
[U,S]=spec(testmat2(3+2*%i,5));
if Err(U*S/U-testmat2(3+2*%i,5))>200*%eps then pause,end 

//Large dimension
//---------------
//Real Case
//Unsymetric
if Checktestmat1(3,50)>1000*%eps then pause,end
[U,S]=spec(testmat1(3,50));
if Err(U*S/U-testmat1(3,50))>1000*%eps then pause,end 

//Symmetric
if Checktestmat2(3,50)>1000*%eps then pause,end
[U,S]=spec(testmat2(3,50));
if Err(U*S/U-testmat2(3,50))>1000*%eps then pause,end 

//Complex Case
//Unsymetric
if Checktestmat1(3+2*%i,50)>1000*%eps then pause,end
[U,S]=spec(testmat1(3+2*%i,50));
if Err(U*S/U-testmat1(3+2*%i,50))>1000*%eps then pause,end 

//Symmetric
if Checktestmat2(3+2*%i,50)>1000*%eps then pause,end
[U,S]=spec(testmat2(3+2*%i,50));
if Err(U*S/U-testmat2(3+2*%i,50))>1000*%eps then pause,end 

