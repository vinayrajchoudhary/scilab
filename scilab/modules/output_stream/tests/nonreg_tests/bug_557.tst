// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Pierre MARECHAL <pierre.marechal@inria.fr>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- JVM NOT MANDATORY -->

// <-- Non-regression test for bug 557 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=557
//
// <-- Short Description -->
//    mprintf and diary don't work together
//    after each character of the string generated by
//    mprintf a newline character is inserted

// Génération du fichier de référence

l = [" ";"-->mprintf(''hello world\n'')";"hello world";" ";"-->diary(TMPDIR+''/bug557.dia'');"];
l2 = ["hello world";" "];
mputl(l,TMPDIR+'/bug557.ref');

// Génération du fichier rapport

diary(TMPDIR+'/bug557.dia');
mprintf('hello world\n')
diary(TMPDIR+'/bug557.dia');

// Comparaison

[u1,ierr]=mopen(TMPDIR+'/bug557.ref');
[u2,ierr]=mopen(TMPDIR+'/bug557.dia');

ref=mgetl(u1);mclose(u1);
dia=mgetl(u2);mclose(u2);

// Affichage du résultat
ref
dia
if or(ref<>dia) then pause,end