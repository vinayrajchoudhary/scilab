// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

cd(TMPDIR);

if MSDOS then
	unix_w(jre_path()+"\bin\java.exe -cp "+SCI+"\modules\localization\tests\unit_tests CreateDir");
else
	unix_w(jre_path()+"/bin/java -classpath "+SCI+"/modules/localization/tests/unit_tests CreateDir");
end

tab_ref = [
"世界您好",
"азеазея",
"ハロー・ワールド",
"حريات وحقوق",
"תוכנית"];

for i = 1 : size(tab_ref,'*')
  fz = TMPDIR + filesep() + "dir_" + tab_ref(i) + filesep() + tab_ref(i) + '.hst';
  savehistory(fz);
  resethistory();
  if ls(fz) == [] then pause,end
  loadhistory(fz);
end