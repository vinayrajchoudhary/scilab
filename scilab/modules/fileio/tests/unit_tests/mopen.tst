// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
FLN = 'SCI/modules/fileio/tests/unit_tests/text.txt';

fd = mopen(FLN,'rt'); 
mclose(fd);

fd = mopen(FLN,'rb'); 
mclose(fd);

fd = mopen(TMPDIR+'/mopen.txt','wt')
mclose(fd);

fd = mopen(TMPDIR+'/mopen.txt','wb')
mclose(fd);