//
// Scilab ( http://www.scilab.org/ ) 
// This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2009 - DIGITEO
//
// This file is distributed under the same license as the Scilab package.
//

thispath = get_absolute_file_path("inverted_pendulum.dem.sce");

exec(thispath+"/setw.sci");

xcos(thispath+"/Inverted_pendulum.xcos");
clear thispath;