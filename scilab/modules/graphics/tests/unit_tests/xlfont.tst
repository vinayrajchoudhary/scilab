// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================


// <-- TEST WITH GRAPHIC -->

fonts = xlfont();
if size(fonts,'*') <> 11 then pause,end

default_fonts = [ "Monospaced" , ..
"Symbol" , ..
"Serif" , ..
"Serif" , ..
"Serif" , ..
"Serif" , ..
"SansSerif" , ..
"SansSerif" , ..
"SansSerif" , ..
"SansSerif" , ..
"SansSerif" ];

if ~MSDOS then 
default_fonts = strsubst(default_fonts,'Symbol','OpenSymbol');
end

if ( or(fonts <> default_fonts) ) then pause,end

availablefonts = xlfont('AVAILABLE_FONTS');
if size(availablefonts,'*') < 11 then pause,end

for i=0:size(fonts,'*')-1
  xlfont(default_fonts(1),i);
end  
ref = emptystr(1:size(fonts,'*')) + default_fonts(1);
fonts = xlfont();

if ( and(fonts <> default_fonts) ) then pause,end

for i=0:size(fonts,'*')-1
  xlfont(default_fonts(2),i,%t);
end  
ref = emptystr(1:size(fonts,'*')) + default_fonts(2);
fonts = xlfont();

if ( and(fonts <> default_fonts) ) then pause,end

for i=0:size(fonts,'*')-1
  xlfont(default_fonts(2),i,%t,%t);
end  
ref = emptystr(1:size(fonts,'*')) + default_fonts(2);
fonts = xlfont();

if ( and(fonts <> default_fonts) ) then pause,end
