// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// optimbase_isinnonlincons --
//   Returns %t if the given point satisfies inequality constraints.
//   Returns %f if the given point does not satisfies inequality constraints.
// Arguments
//   x : the point to analyse
//   isfeasible : = %t or %f
//
function [ this , isfeasible ] = optimbase_isinnonlincons ( this , x )
    isfeasible = %t
      if ( this.nbineqconst > 0) then
        [ this , const ] = optimbase_function ( this , x , 2 );
        index = 0
        for ic = 1 : this.nbineqconst
          if ( const ( ic ) < 0.0 ) then
            optimbase_log ( this , sprintf ( "Inequality constraint #%d/%d is not satisfied for x", ...
              ic , this.nbineqconst ) )
            isfeasible = %f
            break
          end
        end
      end
endfunction
