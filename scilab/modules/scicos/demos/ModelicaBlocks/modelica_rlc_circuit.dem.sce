//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
//
// This file is distributed under the same license as the Scilab package.
//

thispath = get_absolute_file_path("modelica_rlc_circuit.dem.sce");
scicos(thispath+"/RLC_Modelica.cosf");
clear thispath;