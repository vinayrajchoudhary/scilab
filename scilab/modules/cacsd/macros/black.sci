// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at    
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


function black(varargin)
//Black's diagram (Nichols chart) for a linear system sl.
//sl can be a continuous-time, discrete-time or sampled SIMO system
//Syntax:
//
//           black( sl,fmin,fmax [,pas] [,comments] )
//           black(frq,db,phi [,comments])
//           black(frq, repf  [,comments])
//  
//  sl       : SIMO linear system (see syslin). In case of multi-output
//             system the outputs are plotted with differents symbols.
//            
//  fmin     : minimal frequency (in Hz).
//  fmax     : maximal frequency (in Hz).
//  pas      : logarithmic discretization step. (see calfrq for the
//             choice of default value).
//  comments : character strings to comment the curves.
//
//  frq      : (row)-vector of frequencies (in Hz) or (SIMO case) matrix
//             of frequencies.
//  db       : matrix of modulus (in Db). One row for each response.
//  phi      : matrix of phases (in degrees). One row for each response.
//  repf     : matrix of complex numbers. One row for each response.

//To plot the grid of iso-gain and iso-phase of y/(1+y) use abaque()
//%Example
//  s=poly(0,'s')
//  h=syslin('c',(s**2+2*0.9*10*s+100)/(s**2+2*0.3*10.1*s+102.01))
//  abaque();
//  black(h,0.01,100,'(s**2+2*0.9*10*s+100)/(s**2+2*0.3*10.1*s+102.01)')
//  //
//  h1=h*syslin('c',(s**2+2*0.1*15.1*s+228.01)/(s**2+2*0.9*15*s+225))
//  black([h1;h],0.01,100,['h1';'h'])
//See also:
//  bode nyquist  abaque freq repfreq 
//!
    rhs=size(varargin)
  if type(varargin($))==10 then
    comments=varargin($),rhs=rhs-1;
  else
    comments=[];
  end
  fmax=[]
  if or(typeof(varargin(1))==['state-space' 'rational']) then 
    //sys,fmin,fmax [,pas] or sys,frq
    if rhs==1 then
      [frq,repf]=repfreq(varargin(1),1d-3,1d3)
    elseif rhs==2 then //sys,frq
      if size(varargin(2),2)<2 then
	error(msprintf(_("%s : Invalid argument #%d. It must be a row vector with length > %d"),..
		     "black",1,1))
      end
      [frq,repf]=repfreq(varargin(1:rhs))
    elseif or(rhs==(3:4)) then //sys,fmin,fmax [,pas]
      [frq,repf]=repfreq(varargin(1:rhs))
    else
      error(msprintf(_("%s : Invalid call: sys,fmin,fmax [,pas] [,com]'),"black"))
    end
    [phi,d]=phasemag(repf)
    if rhs>=3 then fmax=varargin(3),end
  elseif  type(varargin(1))==1 then 
    //frq,db,phi [,comments] or frq, repf [,comments]
    select rhs
    case 2 then //frq,repf
      frq=varargin(1);
      if size(frq,2)<2 then
	error(msprintf(_("%s : Invalid argument #%d. It must be a row vector with length > %d"),..
		     "black",1,1))
      end
      if size(frq,2)<>size(varargin(2),2) then
	error(msprintf(_("%s : Incompatible dimensions of arguments #%d and #%d."),..
			 "black",1,2))
      end
      [phi,d]=phasemag(varargin(2))
    case 3 then  //frq,db,phi
      [frq,d,phi]=varargin(1:rhs)
      if size(frq,2)<>size(d,2) then
	error(msprintf(_("%s : Incompatible dimensions of arguments #%d and #%d."),..
			 "black",1,2))
      end
      if size(frq,2)<>size(phi,2) then
	error(msprintf(_("%s : Incompatible dimensions of arguments #%d and #%d."),..
			 "black",1,3))
      end
    else 
      error(msprintf(_("%s : Invalid call: frq, db,phi [,com] or frq,repf [,com]'),"black"))
    end
  else
    error(msprintf(_("%s : Invalid argument #%d. It must be a linear"+..
		     " dynamical system (syslin) or a real array"),"black",1))
  end;
  
  if size(frq,1)==1 then
    ilf=0
  else
    ilf=1
  end
 
  [mn,n]=size(phi);
  if and(size(comments,'*')<>[0 mn]) then
    error(msprintf(_("%s : Invalid dimension for argument #%d"),"black",rhs+1))
  end

  //
  xmn=floor(min(phi)/90)*90
  xmx=ceil(max(phi)/90)*90
  ymn=min(d)
  ymx=max(d)


  kf=1
  phi1=phi+5*ones(phi);

  kk=1;p0=[phi(:,kk) d(:,kk)];ks=1;dst=0;
  dx=xmx-xmn
  dy=ymx-ymn
  dx2=dx^2;dy2=dy^2

  while kk<n
    kk=kk+1
    dst=dst+min(sqrt(((phi(:,kk-1)-phi(:,kk))^2)/dx2+((d(:,kk-1)-d(:,kk))^2)/dy2))
    if dst>0.1 then
      if mini(abs(frq(:,ks(prod(size(ks))))-frq(:,kk))./frq(:,kk))>0.2 then
	ks=[ks kk]
	dst=0
      end
    end
  end
  kf=1
  drawlater()
  ax=gca();
  if size(ax.children,'*')==0 then
    ax.data_bounds=[xmn ymn;xmx ymx];
  else
    ax.data_bounds=[min([xmn ymn],ax.data_bounds(1,:));
		    max([xmx ymx],ax.data_bounds(2,:))];
  end
  ax.axes_visible='on';
  ax.clip_state="clipgrf";
  E=[]
  if ks($)<size(phi,2) then last=$;else	last=$-1;end
  for k=1:mn
    xpoly(phi(k,:),d(k,:));e1=gce()
    e1.foreground=k;
    e2=[]
    if size(ks,'*') >1 then
      d_phi=phi(k,ks(1:last)+1)-phi(k,ks(1:last));
      d_d=d(k,ks(1:last)+1)-d(k,ks(1:last));
      dd=150*sqrt((d_phi/dx).^2+(d_d/dy).^2);
      if dd>0 then
	xarrows([phi(k,ks(1:last));phi(k,ks(1:last))+d_phi./dd],..
		[d(k,ks(1:last));d(k,ks(1:last))+d_d./dd],1.5)
	e2=gce();e2.foreground=k;
      end
    end
    //add frequency values
    ne=size(ax.children,'*')
    xnumb(phi(k,ks),d(k,ks),frq(kf,ks),0);
    nn=size(ax.children,'*')-ne
    if nn>1 then e3=glue(ax.children(nn:-1:1)),else e3=ax.children(1);end
    // glue entities relative to a single black curve
    E=[E glue([e3 e2 e1])]
    kf=kf+ilf
  end
 
  xtitle('h(2i.pi.f) ','phase','magnitude (Db)');
  //  2.3 db curve
  mbf=2.3;
  lmda=exp(log(10)/20*mbf);
  r=lmda/(lmda**2-1);
  npts=100;
  crcl=exp(%i*(-%pi:(2*%pi/npts):%pi));
  lgmt=log(-r*crcl+r*lmda*ones(crcl));
  xpoly([180*(imag(lgmt)/%pi-ones(lgmt))],[(20/log(10)*real(lgmt))])
  e=gce();e.foreground=2;e.line_style=3;
  if comments<>[] then
    c=[];for k=1:mn,c=[c E(k).children(1)];end
    legend([c e],[comments;'2.3Db'])
  end
  drawnow()
endfunction