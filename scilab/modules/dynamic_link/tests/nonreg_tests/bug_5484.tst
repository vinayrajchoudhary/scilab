// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->
// <-- WINDOWS ONLY -->


// <-- Non-regression test for bug 5484 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=5484
// <-- Short Description -->
// LCC-Win32 does not work with this example

if MSDOS then
  ilib_verbose(0);
  if with_lcc() then
    copyfile(SCI + '/modules/dynamic_link/tests/nonreg_tests/bug_5484.c',TMPDIR + '/bug_5484.c');
	cd TMPDIR;
	ierr = execstr("r = ilib_for_link(''pendel_c'',''bug_5484.c'','''',''c'','''',''loader.sce'','''','''',''-I""""''+WSCI+''\modules\scicos_blocks\includes""""'');" , "errcatch");
	if ierr <> 0 then pause,end
	if fileinfo(r) == [] then pause,end
  end
end

// =============================================================================