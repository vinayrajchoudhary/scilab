//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) ENPC
//
// This file is distributed under the same license as the Scilab package.
//

mode(-1);

path=pathconvert(get_absolute_file_path('npend.dem.sce'),%t,%t)	

global LANGUAGE
if LANGUAGE=='fr' then
//  browsehelp(path+'demo_pendulum_fr.htm',' ')
else
//   browsehelp(path+'demo_pendulum_eng.htm',' ')
end
getf(path+'n_pendulum.sci');
demo_pendulum()