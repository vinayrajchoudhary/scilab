//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
//
// This file is distributed under the same license as the Scilab package.
//

thispath = get_absolute_file_path("modelica_chaos.dem.sce");
scicos(thispath+"/Chaos_Modelica.cosf");
clear thispath;