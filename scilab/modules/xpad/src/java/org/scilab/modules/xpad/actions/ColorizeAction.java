/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Bruno JOFRET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xpad.actions;

import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.KeyStroke;

import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.xpad.Xpad;
import org.scilab.modules.xpad.style.ScilabStyleDocument;

public class ColorizeAction extends DefaultAction {

	private static Xpad color_editor;

	private ColorizeAction(Xpad editor) {
		super("Colorize", editor);
		//setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_, ActionEvent.CTRL_MASK));
		color_editor = editor;
	}

	public void doAction() {
		((ScilabStyleDocument) getEditor().getTextPane().getStyledDocument()).colorize(0, getEditor().getTextPane().getDocument().getLength());
	}

	public static MenuItem createMenu(Xpad editor) {
		return createMenu("Colorize", null, new ColorizeAction(editor), null);
	}

	public static void getXpadEditor(){
		((ScilabStyleDocument) color_editor.getTextPane().getStyledDocument()).setEditor(color_editor);
	}
}