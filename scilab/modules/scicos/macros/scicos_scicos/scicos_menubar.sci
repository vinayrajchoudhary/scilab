function scicos_menubar(win,menus)
// Copyright (C) INRIA
// 
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at    
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

names = menus(1); 
for k = size(names,'*'):-1:1
  delmenu(win,names(k))
end

for k=1:size(names,'*')
  //** Automatically add the [ALT] menufile shortcut  
  addmenu(win, "&"+names(k), menus(k+1), list(0,names(k))); 
end
datas = []; 
endfunction