//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Pierre MARECHAL <pierre.marechal@scilab.org>
//
// This file is distributed under the same license as the Scilab package.
//

thispath = get_absolute_file_path("bike2.dem.sce");

exec(thispath+"macros/show.sci");
exec(thispath+"macros/velod.sci");
exec(thispath+"macros/velo1.sci");

x = read(thispath+"data/xdemo.dat",46,401,"(e10.4)");

my_handle = scf(100001);
clf(my_handle,"reset");

show(x(:,1:340),1.6,1.47,velo1);

// Clear variable and functions
clear my_axe x;
clear show get_velo_rti velo1 velo4p poteau arbre velodp velod;