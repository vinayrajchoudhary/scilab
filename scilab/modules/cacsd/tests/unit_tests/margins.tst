//gain margin
//-----------
//discrete time case
h = syslin(0.1,0.04798*%z+0.0464,%z^2-1.81*%z+0.9048);//pk
[g ,f]=g_margin(h);
if norm(g - 6.2423793565916954)>1d-5  then pause,end
if norm(f - 0.86539118158628991)>1d-5  then pause,end


h=syslin(0.1,0.086-0.161*%z+0.078*%z^2,-0.67+2.286*%z-2.61*%z^2+%z^3);//ok
[g ,f]=g_margin(h);
if norm(g- 12.3470513198133762)>1d-5  then pause,end
if norm(f-0.26109869168929700)>1d-5  then pause,end

h=syslin(0.1,3*(0.086-0.161*%z+0.078*%z^2),-0.67+2.286*%z-2.61*%z^2+%z^3);//ok
[g ,f]=g_margin(h);
if norm(g-2.80462622542011131)>1d-5  then pause,end
if norm(f-0.26109869168929828)>1d-5  then pause,end


//continuuous time case
h=syslin('c',-1+%s,3+2*%s+%s^2);//ok
[g,f]=g_margin(h);
if norm(g-20*log(3)/log(10))>1d-5  then pause,end
if norm(f)>1d-5  then pause,end


 h = syslin('c',0.2+0.8*%s+0.3*%s^3,0.0409+0.1827*%s+1.28225*%s^2+3.1909*%s^3+2.56*%s^4+%s^5);
[g,f]=g_margin(h);
if norm(g + 4.91687406933815385)>1d-5  then pause,end
if norm(f-0.07145552582020068)>1d-5  then pause,end

//phase margin
//-----------
//discrete time case
h = syslin(0.1,0.04798*%z+0.0464,%z^2-1.81*%z+0.9048);//ok
[p ,f]=p_margin(h);
if norm(p-13.5711556361199754)>1d-5  then pause,end
if norm(f-0.69301660031536083)>1d-5  then pause,end


h=syslin(0.1,0.086-0.161*%z+0.078*%z^2,-0.67+2.286*%z-2.61*%z^2+%z^3);//ok
[p ,f]=p_margin(h);
if p<>%inf  then pause,end
if f<>[]  then pause,end

h=syslin(0.1,3*(0.086-0.161*%z+0.078*%z^2),-0.67+2.286*%z-2.61*%z^2+%z^3);//ok
[p ,f]=p_margin(h);
if norm(p-52.9496741629204308 )>1d-5  then pause,end
if norm(f-0.21233648894721618)>1d-5  then pause,end


//continuous case
h=syslin('c',1.1+2.4*%s+0.7*%s^2,3+2*%s+%s^2);
[p,f]=p_margin(h);
if norm(p-(-148.547076202317413))>1d-5  then pause,end
if norm(f-0.18945852512301298)>1d-5  then pause,end

 h = syslin('c',0.2+0.8*%s+0.3*%s^3,0.0409+0.1827*%s+1.28225*%s^2+3.1909*%s^3+2.56*%s^4+%s^5);
[p,f]=p_margin(h);
if norm(p + 13.1128497150069734 )>1d-5  then pause,end
if norm(f-0.09144216563554157  )>1d-5  then pause,end