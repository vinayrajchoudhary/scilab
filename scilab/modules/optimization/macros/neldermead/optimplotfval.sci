// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// optimplotfval --
//   Emulate the optimplotfval command of Matlab.
//   Plot the function value during an optimization process.
// Arguments, input
//   x : the current point
//   optimValues : a tlist which contains the following fields
//     funcCount" : the number of function evaluations
//     fval : the current function value
//     iteration : the current iteration
//     procedure : a string containing the current type of step
//  state : the current state of the algorithm
//    "init", "iter", "done"
// Notes:
//   The algorithm is the following.
//   At initialization of the algorithm, create an empty 
//   graphic plot, retrieve the handle, and store a special
//   key "optimplotfval" in the user_data field of the handle.
//   When the plot is to update, this key is searched so that the 
//   correct plot can be update (and not another).
//
function optimplotfval ( x , optimValues , state )
  if ( state == "init" ) then
    opfvh = scf();
    plot ( 0 , optimValues.fval );
    opfvh.user_data = "optimplotfval";
    opfvh.children.x_label.text = "Iteration";
    opfvh.children.y_label.text = "Function value";
    opfvh.children.title.text = msprintf ( "Current Function Value: %e", optimValues.fval )
    opfvh.children.children.children.mark_mode = "on";
    opfvh.children.children.children.mark_style = 5;
    opfvh.children.children.children.mark_size = 10;
    opfvh.children.children.children.mark_background = 6;
  else
    opfvh = findobj ( "user_data" , "optimplotfval" );
    scf(opfvh);
    gg = gce();
    // Update data
    gg.children.data($+1,1:2) = [optimValues.iteration optimValues.fval];
    // Compute new bounds
    itermin = 0;
    itermax = optimValues.iteration;
    fmin = min(gg.children.data(:,2));
    fmax = max(gg.children.data(:,2));
    // Update bounds
    hh = gcf();
    hh.children.data_bounds = [
      itermin fmin
      itermax fmax
    ];
    // Update title
    opfvh.children.title.text = msprintf ( "Current Function Value: %e", optimValues.fval )
  end
endfunction
