// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//
// optimbase_new --
//   Creates a new Optimization object.
//
function newobj = optimbase_new ()
  newobj = tlist(["T_OPTIMIZATION",...
    "verbose",...
    "x0","fx0",...
    "xopt","fopt",...
    "tolfunabsolute","tolfunrelative","tolfunmethod",...
    "tolxabsolute","tolxrelative","tolxmethod" ,...
    "funevals","maxfunevals",...
    "iterations","maxiter",...
    "fun","status", ...
    "historyfopt","historyxopt",...
    "verbosetermination",...
    "outputcommand",...
    "outputcommandarg","numberofvariables",...
    "storehistory","costfargument",...
    "boundsmin","boundsmax",...
    "nbineqconst"]);
  // The number of variables to optimize
  newobj.numberofvariables = 0
  // The verbose option, controlling the amount of messages
  newobj.verbose = 0;
  // The verbose option for termination criteria
  newobj.verbosetermination = 0;
  // The initial guess
  newobj.x0 = 0.0;
  // The value of the function for the initial guess
  newobj.fx0 = 0;
  // The maximum number of function evaluations
  newobj.maxfunevals = 100;
  // The maximum number of iterations
  newobj.maxiter = 100;
  // Possible values : "enabled", "disabled"
  // This criteria is suitable for functions which minimum is 
  // associated with a function value equal to 0.
  newobj.tolfunmethod = "disabled";
  // The absolute tolerance on function value
  newobj.tolfunabsolute = 0.0;
  // The relative tolerance on function value
  newobj.tolfunrelative = %eps;
  // The absolute tolerance on x
  newobj.tolxabsolute = 0.0;
  // The relative tolerance on x
  newobj.tolxrelative = %eps;
  // The number of function evaluations
  newobj.funevals = 0;
  // The number of iterations
  newobj.iterations = 0;
  // The optimum parameter
  newobj.xopt = 0;
  // The optimum function value
  newobj.fopt = 0;
  // Possible values : "enabled", "disabled"
  newobj.tolxmethod = "enabled";
  // The status of the optimization
  newobj.status = "";
  // The command called back for output
  newobj.outputcommand = "";
  // The outputcommand argument is initialized as a string.
  // If the user configure this option, it is expected
  // that a matrix of values or a list, tlist, mlist is 
  // passed so that the argument is appended to the name of the 
  // function.
  newobj.outputcommandarg = ""
  // The cost function
  newobj.fun = "";
  // The costf argument is initialized as a string.
  // If the user configure this option, it is expected
  // that a matrix of values or a list, tlist, mlist is 
  // passed so that the argument is appended to the name of the 
  // function.
  newobj.costfargument = "";
  // The flag which enables/disables the storing of the history
  newobj.storehistory = 0;
  // The array to store the history for xopt
  newobj.historyxopt = list();
  // The array to store the history for fopt
  newobj.historyfopt = [];
  // Maximum bounds for the parameters
  newobj.boundsmax = [];
  // Minimum bounds for the parameters
  newobj.boundsmin = [];
  // The number of nonlinear inequality constraints
  newobj.nbineqconst = 0;
endfunction