//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
//
// This file is distributed under the same license as the Scilab package.
//

funcprot(0);

my_demo_path = get_absolute_file_path("cylinder.dem.sce");

exec(my_demo_path+"cylinder.sci");
exec(my_demo_path+"cylinder_interface.sci");
execylinder();

clear my_demo_path;