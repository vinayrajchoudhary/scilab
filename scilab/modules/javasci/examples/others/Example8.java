/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA
 * 
 * This file is released under the 3-clause BSD license. See COPYING-BSD.
 *
 */

import javasci.SciString;
import javasci.Scilab;

/**
 * @deprecated
 */
class Example8 {

    public static void main(String[] args) 
        {
  
            SciString SCIPATH = new SciString("SCILABROOTPATH");
            Scilab.Exec("SCILABROOTPATH=getenv('SCI');");
    
            Scilab.ExecuteScilabScript(SCIPATH.getData()+"/modules/javasci/examples/others/test.sce");
    
            /* "notest.sce" not exist */
            if (! Scilab.ExecuteScilabScript(SCIPATH.getData()+"/modules/javasci/examples/others/notest.sce") )
            {
                System.out.println("Scilab Error code: "+Scilab.GetLastErrorCode());
            }
     
            Scilab.Finish();
        }
}
