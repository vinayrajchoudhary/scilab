// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// optimset --
//   Configures and returns an optimization data structure.
// Usage:
//   options = optimset ()
//   options = optimset ( funname )
//   options = optimset ( key , value )
//   options = optimset ( key1 , value1 , key2 , value2 , ... )
//   options = optimset ( options , key , value )
//   options = optimset ( options , key1 , value1 , key2 , value2 , ... )
//
function options = optimset (varargin)
  [lhs,rhs]=argn();
  //mprintf("lhs\n");
  //disp(lhs);
  //mprintf("rhs\n");
  //disp(rhs);
  if rhs == 0 then
    options = optimset_new ();
    return
  elseif rhs==1 then
    //
    //   options = optimset ( funname )
    // If there is only one argument, it is expected to be the
    // name of a method.
    //
    method = varargin(1);
    options = optimset_method ( method );
    return
  end
  // Set the options variable
  if modulo(rhs,2)<>0 then
    //
    //   options = optimset ( options , key , value )
    //   options = optimset ( options , key1 , value1 , key2 , value2 , ... )
    // If the number of arguments is odd,
    // the first argument is expected to be a optimset struct.
    //
    options = varargin(1);
    t1 = typeof(options);
    if t1<>"st" then
      errmsg = msprintf(gettext("%s: Odd number of arguments : the first argument is expected to be a struct, but is a %s"), "optimset", t1);
      error(errmsg)
    end
  else
    //   options = optimset ( key , value )
    //   options = optimset ( key1 , value1 , key2 , value2 , ... )
    // Number of input argument is even.
    options = optimset_new ();
  end
  // Set ivar : index of input variable.
  // The variable ivar allows to make a loop over input arguments.
  if modulo(rhs,2)<>0 then
    ivar = 1;
  else
    ivar = 0;
  end
  //
  // Process key,values as pairs.
  //
  nbkeys = rhs/2;
  for i=1:nbkeys
    ivar = ivar + 1;
    key = varargin(ivar);
    ivar = ivar + 1;
    value = varargin(ivar);
    //mprintf("Argument #%d\n",ivar);
    //mprintf("key = %s\n",key);
    //mprintf("value = %s\n",string(value)); // One cannot display a function.
    options = optimset_configure (options,key,value);
  end
endfunction
//
// optimset_configure --
//   Configure the given key with the given value.
// Arguments
//   options : a optimset struct
//   key : a string, the key to configure
//   value : the value
//
function options = optimset_configure ( options , key , value )
    select key
    case "Display" then
      options.Display = value;
    case "FunValCheck" then
      options.FunValCheck = value;
    case "MaxFunEvals" then
      options.MaxFunEvals = value;
    case "MaxIter" then
      options.MaxIter = value;
    case "OutputFcn" then
      options.OutputFcn = value;
    case "PlotFcns" then
      options.PlotFcns = value;
    case "TolFun" then
      options.TolFun = value;
    case "TolX" then
      options.TolX = value;
    else
      errmsg = msprintf(gettext("%s: Unknown key %s"), "optimset", key)
      error(errmsg)
    end
endfunction
//
// optimset_new --
//   Returns an empty optimset struct
//
function options = optimset_new ()
    options = struct(...
      "Display" ,[],...
      "FunValCheck" ,[],...
      "MaxFunEvals" ,[],...
      "MaxIter" ,[],...
      "OutputFcn" ,[],...
      "PlotFcns" ,[],...
      "TolFun" ,[],...
      "TolX" ,[]...
      );
endfunction
//
// optimset_method --
//   Returns an optimset struct which content is the default 
//   settings for the given method.
// Arguments
//   method : a string, the name of the method
//
function options = optimset_method ( method )
    options = optimset_new ();
    select method
    case "fminsearch" then
      options = optimset_configure ( options , "Display" , "notify" );
      options = optimset_configure ( options , "MaxFunEvals" , "200*numberofvariables" );
      options = optimset_configure ( options , "MaxIter" , "200*numberofvariables" );
      options = optimset_configure ( options , "TolFun" , 1.e-4 );
      options = optimset_configure ( options , "TolX" , 1.e-4 );
    else
      errmsg = msprintf(gettext("%s: Unknown method %s"), "optimset", method)
      error(errmsg)
    end
endfunction
