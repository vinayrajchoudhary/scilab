// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - INRIA - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


//
// optimbase_terminate --
//   Returns 1 if the algorithm terminates.
//   Returns 0 if the algorithm must continue.
// Arguments, input
//   this : the current object
//   previousfopt : the previous value of the objective function
//   currentfopt : the current value of the objective function
//   previousxopt : the previous value of x
//   currentxopt : the current value of x
//   terminate : 1 if the algorithm terminates, 0 if the algorithm must continue.
// Arguments, output
//   status : termination status
//     status = "continue"
//     status = "maxiter"
//     status = "maxfuneval"
//     status = "tolf"
//     status = "tolx"
//
function [this , terminate , status] = optimbase_terminate (this , ...
  previousfopt , currentfopt , previousxopt , currentxopt )
  terminate = 0;
  status = "continue";
  this = optimbase_stoplog (this,sprintf("  > Termination ?"));
  //
  // Criteria #1 : maximum number of iterations
  //
  if (terminate == 0) then 
    this = optimbase_stoplog (this,sprintf("  > iterations=%d >= maxiter=%d",this.iterations, this.maxiter));
    if this.iterations >= this.maxiter then
      terminate = 1;
      status = "maxiter";
    end
  end
  //
  // Criteria #2 : maximum number of call to function
  //
  if (terminate == 0) then 
    this = optimbase_stoplog (this,sprintf("  > funevals=%d >= maxfunevals=%d",this.funevals, this.maxfunevals));
    if this.funevals >= this.maxfunevals then
      terminate = 1;
      status = "maxfuneval";
    end
  end
  //
  // Criteria #3 : tolerance on function
  // Note : 
  //   This termination criteria works well in the special case where the function
  //   value at optimum is several order of magnitude smaller 
  //   than the initial function value (ie f(x0)).
  //   This is the case when the function value at optimum is zero.
  //   When the function value at optimum is non-zero, or if the 
  //   initial function value is strictly positive (e.g. f(x0)=10)
  //   and the optimum function value is strictly negative (e.g. f(x*)=-10),
  //   that criteria fails miserably.
  //
  if (terminate == 0) then
    select this.tolfunmethod
    case "enabled" then
      this = optimbase_stoplog (this,sprintf("  > abs(currentfopt)=%e < tolfunrelative * abs(previousfopt) + tolfunabsolute=%e",...
        abs(currentfopt), this.tolfunrelative * abs(previousfopt) + this.tolfunabsolute));
      if abs(currentfopt) < this.tolfunrelative * abs(previousfopt) + this.tolfunabsolute then
        terminate = 1;
        status = "tolf";
      end
    case "disabled" then
      // Nothing to do.
    else
      errmsg = sprintf("Unknown tolf method %s",this.tolfunmethod);
      error(errmsg);
    end
  end
  //
  // Criteria #4 : tolerance on x
  //
  if (terminate == 0) then
    //
    // Note
    // What means a relative error on x ?
    // Notes: if xn and xn+1 are very close to xopt and xopt different from 0,
    // the relative error between xn and xn+1 is small.
    // But if xopt, xn and xn+1 are close to 0, the relative error may be a
    // completely wrong criteria. The absolute tolerance should be used in this case.
    //
    select this.tolxmethod
    case "enabled" then
      this = optimbase_stoplog (this,sprintf("  > e(x)=%e < tolxrelative = %e * %e + %e",...
        norm(currentxopt - previousxopt), this.tolxrelative , norm(currentxopt) , this.tolxabsolute ));
      if norm(currentxopt - previousxopt) < this.tolxrelative * norm(currentxopt) + this.tolxabsolute then
        terminate = 1;
        status = "tolx";
      end
   case "disabled" then
      // Nothing to do.
    else
      errmsg = sprintf("Unknown tolx method %s",this.tolxmethod);
      error(errmsg);
    end
  end
endfunction
  
