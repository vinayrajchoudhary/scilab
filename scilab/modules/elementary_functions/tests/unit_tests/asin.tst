// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Pierre MARECHAL <pierre.marechal@inria.fr>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// unit tests for asin() function (element wise coasine inverse)
// =============================================================================

if execstr("asin()"   ,"errcatch") == 0 then pause, end
if execstr("asin(1,2)","errcatch") == 0 then pause, end

rt2 = sqrt(2);
rt3 = sqrt(3);
v   = [0 , %pi/6 , %pi/4 , %pi/3 , %pi/2    , %pi/3 , %pi/4 , %pi/6 , 0 ];
x   = [0 , 1/2   , rt2/2 , rt3/2 , 1        , rt3/2 , rt2/2 , 1/2   , 0 ];

if or(abs(asin(x)-v) > sqrt (%eps)) then pause, end

if ~isnan(asin(%nan))        then pause, end
if ~isnan(asin(-%nan))       then pause, end

A = rand(100,100);

// asin(-x) = - asin(x)
if or( asin(-A) + asin(A) > %eps) then pause, end


// asin(x) = acos(-x) - pi/2
if or( (asin(A) - acos(-A) + %pi/2) > %eps ) then pause, end