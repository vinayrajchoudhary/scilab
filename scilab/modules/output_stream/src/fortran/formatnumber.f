c Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
c Copyright (C) INRIA
c 
c This file must be used under the terms of the CeCILL.
c This source file is licensed as described in the file COPYING, which
c you should have received as part of this distribution.  The terms
c are also available at    
c http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

      subroutine formatnumber(a,ifmt,maxc,str,fl)
c maxc: Maximun character authorized
      double precision a
      integer n1,n2,fl
      character str*(*)
      character*10 form
      if (ifmt .eq. 1) then
         fl = maxc
         n2 = 1
         write(form,130) maxc,maxc-7
         write (str,form) a
       elseif (ifmt .ge. 0) then
          n1 = ifmt / 32
          n2 = ifmt - 32*n1
          fl = n1
          if(a.lt.0.0d0) fl=fl+1
          write(form,120) n1,n2
          write(str(1:n1),form) a
C     workaround to fix gfortran4.0 bug: 0.999999999--> 0
C     See: http://bugzilla.scilab.org/show_bug.cgi?id=1985
C     See: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=28354
           if (str(1:n1).eq.' 0.'.and.a.gt.0.9999d0) str(2:2)='1'
C     workaround to fix gfortran 4.2.1 & 4.3.2 bug: 0.999999999--> 2
C     See: http://bugzilla.scilab.org/show_bug.cgi?id=2647
C     See: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=37863
          if (str(1:n1).eq.' 2.'.and.a.lt.1.0d0) str(2:2)='1'
       elseif (ifmt .eq. -1) then
C     Inf
          fl = 3
          str = 'Inf'
       elseif (ifmt .eq. -2) then
C     Nan
          fl = 3
          str = 'Nan'
       endif

      return

  120 format('(f',i2,'.',i2,')')
  130 format('(1pd',i2,'.',i2,')')
      end