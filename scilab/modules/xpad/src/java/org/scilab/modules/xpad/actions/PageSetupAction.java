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

import java.awt.print.PageFormat;
import java.awt.print.PrinterJob;

import javax.print.attribute.HashPrintRequestAttributeSet;

import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.xpad.Xpad;

public class PageSetupAction extends DefaultAction {

	private static PageFormat pageFormat;

	private PageSetupAction(Xpad editor) {
		super("Page Setup...", editor);
	}

	public void doAction() {
		PrinterJob printTask = PrinterJob.getPrinterJob();
		pageFormat = printTask.pageDialog(new HashPrintRequestAttributeSet());
	}

	public static MenuItem createMenu(Xpad editor) {
		return createMenu("Page Setup...", null, new PageSetupAction(editor), null);
	}

	public static PageFormat getPageFormat() {
		return pageFormat;
	}
}