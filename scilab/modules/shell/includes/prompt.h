/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Sylvestre LEDRU
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#ifndef _PROMPT_H_
#define _PROMPT_H_
/* Define prompts of Scilab */

#include "machine.h" /* C2F */

#include "dynlib_shell.h"

#ifdef SCIPROMPT
#undef SCIPROMPT
#endif
#define SCIPROMPT "-->"

#ifdef SCIPROMPT_PAUSE
#undef SCIPROMPT_PAUSE
#endif
#define SCIPROMPT_PAUSE ">>"

#ifdef SCIPROMPT_INTERRUPT
#undef SCIPROMPT_INTERRUPT
#endif
#define SCIPROMPT_INTERRUPT "-%d->"

#define PROMPT_SIZE_MAX 64

/*--------------------------------------------------------------------------*/ 
SHELL_IMPEXP void C2F(setprlev)( int *pause);
SHELL_IMPEXP void GetCurrentPrompt(char *CurrentPrompt);
SHELL_IMPEXP void SetTemporaryPrompt(char *tempPrompt);
SHELL_IMPEXP char *GetTemporaryPrompt(void);
SHELL_IMPEXP void ClearTemporaryPrompt(void);
/*--------------------------------------------------------------------------*/ 
#endif /* _PROMPT_H_ */