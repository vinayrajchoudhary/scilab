//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
//
// This file is distributed under the same license as the Scilab package.
//


mode(-1)
deff("[]=demoexc(fil)","exec(""SCI/modules/others/demos/simulation/demos/dae/""+fil)")

while %t do
  n=x_choose(["Spherical pendulum";"Sliding pendulum"],..
      "Examples of DAE");
  select n
  case 0
    return
  case 1
    demoexc("dae1.dem");
  case 2
    demoexc("dae2.dem");
  end
end
