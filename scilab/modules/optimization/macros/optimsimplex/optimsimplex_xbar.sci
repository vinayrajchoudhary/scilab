// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// optimsimplex_xbar --
//   Returns the center of n vertices, by excluding the 
//   vertex with index iexcl.
//   The default value of iexcl is the number of vertices : in that case,
//   if the simplex is sorted in increasing function value 
//   order, the worst vertex is excluded.
// Arguments
//   iexcl : the index of the vertex to exclude in 
//     center computation.
//
function cen = optimsimplex_xbar ( this , iexcl )
   if (~isdef('iexcl','local')) then
    iexcl = this.nbve;
  end
  // Vectorize by making the sum of all, substracting only one vector
  cen = sum(this.x(1:this.n,1:this.nbve),'c')
  cen = cen - this.x(1:this.n,iexcl)
  cen = cen / ( this.nbve - 1)
endfunction
