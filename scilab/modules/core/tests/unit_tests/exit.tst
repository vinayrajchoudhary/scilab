// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

for i = 1:10

 if MSDOS then
   [outputs,status,exitcode] = dos(SCI + '/bin/scilex.exe -nwni -e exit(' + string(i) + ')');
 else
   exitcode = unix(SCI + '/bin/scilab -nwni -e ""exit(' + string(i) + ')""');
 end
 
 if exitcode <> i then pause,end
 
end