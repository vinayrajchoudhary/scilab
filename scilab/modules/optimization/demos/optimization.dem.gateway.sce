//
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
//
// This file is distributed under the same license as the Scilab package.
//


demopath = get_absolute_file_path("optimization.dem.gateway.sce");

subdemolist = ["LMITOOL"                       , "lmitool/lmi.dem.sce"           ; ..
               "Multiflow problem"             , "multiflow/multiflow.dem.sce"   ; ..
               "Non linear data fitting"       , "datafit/datafit.dem.sce"       ; ..
               "Optimal ressource allocation"  , "optloc/optloc.dem.sce"         ]

subdemolist(:,2) = demopath + subdemolist(:,2)