
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - Yann COLLETTE <yann.collette@renault.com>
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

deff('y=test_func(x)','y=x^2');

x0 = 10;

T_init = compute_initial_temp(x0, test_func, 0.8, 1000, [])

if (T_init==%nan) | (abs(T_init)==%inf) then pause,end