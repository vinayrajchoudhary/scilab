// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA - Serge Steer
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
a = [0.8604043 , 0.0070020 , 0.6223373 , -1.356213 , -4.2301775
     0.159714 ,  0.0857791 , -0.2367751 , 0.4958580 , 0.6398817
     -4.3054931 , -0.0365878 , 2.1784911 , 0.0314793 , 2.3728994
     -3.7115779 , -0.5370809 , 2.4291716 , -0.6352663 , 2.6972781
     6.3580966 , 0.1377712 , -4.0461243 , -0.5192899 , -4.0394083];
b = [-0.0532544 , -0.1494083 , -0.0098619
     -0.0355030 , -0.0162722 , 0.1045365
     -0.1301775 , 0.1736686 , -0.0611440
     0.1834320 , 0.1757396 , -0.5956607
     0.1775148 , -0.1186391 , 0.1439842];
c = [2 , 7 , -2 , 5 , 1
     0 , -1 , 3 , 0 , 2];
d = [1 , 0 , 0
     0 , 0 , 0];

if contr(a,b)<>4 then pause,end
[n,U]=contr(a,b);a1=U'*a*U;
if abs(spec(a1(n+1:$,n+1:$)))>1d-7 then pause,end
[n,U,ind,V,Ac,Bc]=contr(a,b);
if n<>4|norm(U'*U-eye())>1d-14|norm(V'*V-eye())>1d-14|or(ind<>[3 1]) then pause,end
if norm(Ac(n+1:$,:),1)>1d-7 then pause,end
if norm(U'*a*U-Ac,1)>1d-6 then pause,end
if norm(U'*b*V-Bc)>1d-10 then pause,end


if contr(a',c',0.0001)<>3 then pause,end
if execstr('contr(a)','errcatch')<>77 then pause,end
if execstr('contr(a,1)','errcatch')<>999 then pause,end
if execstr('contr(a,b,''ee'')','errcatch')<>246 then pause,end
if execstr('contr(a+%s,b)','errcatch')<>246 then pause,end