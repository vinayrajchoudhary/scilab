//create fortran code a copy of the lapack dgesv routine
curdir=pwd();
mputl(['      subroutine dgesvtst( n,nrhs,a,lda,ipiv,b,ldb,info )'
       '      integer            info,lda,ldb,n,nrhs,ipiv( * )'
       '      double precision   a(lda,*),b(ldb,*)'
       '      external           dgetrf,dgetrs'
       '      info = 0'
       '      call dgetrf(n,n,a,lda,ipiv,info)'
       '      if(info.eq.0) then'
       '         call dgetrs(''no transpose'',n,nrhs,a,lda,ipiv,b,ldb,info)'
       '      end if'
       '      return'
       '      end'],TMPDIR+'/dgesvtst.f')

function [X, LU, IPIV, INFO] = msolve(A,B)
// Simplified From Mark code, solve AX = B for matrix X with DGESV from LAPACK
  [N, NCA]     = size(A);
  [LDB,NRHS]   = size(B);
  LDA          = N;
  INFO         = 0;
  [LU, IPIV, X, INFO]  =  call ('dgesvtst',...
				N   , 1, "i", ...
				NRHS, 2, "i", ...
				A   , 3, "d", ...
				LDA , 4, "i", ...
				B   , 6, "d", ...
				LDB , 7, "i", ...
				"out", ...
				3,...
				[N,1],5, "i", ...
				6,...
				[1,1],8, "i");
endfunction

chdir(TMPDIR);
libn=ilib_for_link('dgesvtst','dgesvtst.o',[],'f');
exec loader.sce;
chdir(curdir),
n=44;
A=eye(n,n);B=(1:n)';
[X, LU, IPIV, INFO] = msolve(A,B); 
if norm(A*X-B)>1d-15 then pause,end

 

