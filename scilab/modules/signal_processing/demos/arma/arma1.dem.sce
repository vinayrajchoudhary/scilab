//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) - ENPC
//
// This file is distributed under the same license as the Scilab package.
//

mode(1)
// An example of arma simulation and identification 
// form ( K.J. Astrom)
// The armax process with the following characteristics 
//    a=[1,-2.851,2.717,-0.865]
//    b=[0,1,1,1]
//    d=[1,0.7,0.2]
// is simulated with an input u of a pseudo random binary type
//
// We use the simulated trajectory zd
// as an input to the armax identification macro 
// The noise in the armax is coloured and armax 
// will give a biaised estimator

a=[1,-2.851,2.717,-0.865]
b=[0,1,1,1]
d=[1,0.7,0.2]
ar=armac(a,b,d,1,1,1);
write(%io(2),"Simulation of an ARMAX process:");
ar
// The input
n=300;
u=-prbs_a(n,1,int([2.5,5,10,17.5,20,22,27,35]*100/12));
// simulation 
zd=narsimul(ar,u);

my_handle = scf(100001);
clf(my_handle,"reset"); 
plot2d(1:n,[zd',1000*u'],style=[1,3],leg="Simulated output@Input [scaled]") ;
comp = gce() ;
comp.children(2:3).polyline_style = 2 ;
halt();
write(%io(2),"Identification ARX (least square):");
[arc,la,lb,sig,resid]=armax(3,3,zd,u,1,1);
arc
halt();
// using now armax1 : coloured noise idsentification 
// you can test the same example with 
// n=1000; u=rand(1,n,'g') zd=narsimul(ar,u);
[arc1,resid]=armax1(3,3,2,zd(1:n),u,1);
arc1

halt();
delete(my_handle);