/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan SIMON
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.ui_data.actions;


import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.io.File;
import java.util.HashSet;
import java.util.Set;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.KeyStroke;

import org.scilab.modules.gui.bridge.checkboxmenuitem.SwingScilabCheckBoxMenuItem;
import org.scilab.modules.gui.bridge.menuitem.SwingScilabMenuItem;
import org.scilab.modules.gui.bridge.pushbutton.SwingScilabPushButton;
import org.scilab.modules.gui.checkboxmenuitem.CheckBoxMenuItem;
import org.scilab.modules.gui.checkboxmenuitem.ScilabCheckBoxMenuItem;
import org.scilab.modules.gui.events.callback.CallBack;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.menuitem.ScilabMenuItem;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;

/**
 * Default action for a BrowseVar
 */
public abstract class DefaultAction extends CallBack {
	private static final Set<String> ICON_PATH = new HashSet<String>();

	static {
		addIconPath(System.getenv("SCI") + "/modules/gui/images/icons/");
	}


	/**
	 * Default constructor.
	 * 
	 *The {@link AbstractAction} object is configured using the reflection API.
	 * So you have to be sure that the following fields are declared as static
	 * final fields of each subclasses.
	 * <ul>
	 * <li>String NAME : The name of the action</li>
	 * <li>String SMALL_ICON : The associated icon name (located on
	 * $SCI/modules/gui/images/icons)</li>
	 * <li>int MNEMONIC_KEY : The key associated with the action (see
	 * {@link KeyEvent})</li>
	 * <li>int ACCELERATOR_KEY : The key mask to apply to the mnemonic</li>
	 * </ul>
	 * 
	 * @param scilabVariableBrowser
	 *            corresponding scilabVariableBrowser
	 */
	public DefaultAction() {
		super("");

		installProperties();
	}
	
	/**
	 * Add an icon path to the default icon path.
	 * 
	 * @param path the icon path (with the trailing /)
	 */
	public static void addIconPath(String path) {
		ICON_PATH.add(path);
	}

	/**
	 * Install the static actions properties on the instance
	 */
	private void installProperties() {
		String name = "";
		String icon = "";
		int mnemonic = 0;
		int accelerator = 0;
		try {
			name = (String) getClass().getField("NAME").get(null);
			
			/*
			 * Getting icon from the registered icon path
			 */
			final String iconName = (String) getClass().getField("SMALL_ICON").get(null);
			for (String path : ICON_PATH) {
				if (new File(path + iconName).exists()) {
					icon = path + iconName;
					break;
				}
			}
			
			mnemonic = getClass().getField("MNEMONIC_KEY").getInt(null);
			accelerator = getClass().getField("ACCELERATOR_KEY").getInt(null);
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			e.printStackTrace();
		}

		assert !"".equals(name);
		putValue(Action.NAME, name);
		putValue(Action.SHORT_DESCRIPTION, name);
		putValue(Action.LONG_DESCRIPTION, name);
		if (!ICON_PATH.equals(icon)) {
			putValue(Action.SMALL_ICON, new ImageIcon(icon));
		}

		/*
		 * Set up the accelerator instead of the mnemonic as the menu is the
		 * preferred way on keyboard control. We are using Action.MNEMONIC_KEY
		 * as keyboard key and Action.ACCELERATOR_KEY as a mask.
		 * 
		 * Install it only when there is a real shortcut (with a mnemonic).
		 */
		if (mnemonic != 0) {
			putValue(Action.MNEMONIC_KEY, mnemonic);
			putValue(Action.ACCELERATOR_KEY, KeyStroke.getKeyStroke(mnemonic,
					accelerator));
		}
	}

	/**
	 * Create a menu item
	 * 
	 * @param callBack
	 *            the associated callBack
	 * @return the menu item
	 */
	protected static MenuItem createMenu(CallBack callBack) {
		MenuItem item = ScilabMenuItem.createMenuItem();

		SwingScilabMenuItem swingItem = (SwingScilabMenuItem) item
				.getAsSimpleMenuItem();
		swingItem.setAction(callBack);

		return item;
	}

	/**
	 * Create a button
	 * 
	 * @param callback
	 *            the associated callback
	 * @return the push button
	 */
	protected static PushButton createButton(CallBack callback) {
		PushButton item = ScilabPushButton.createPushButton();

		SwingScilabPushButton swingItem = (SwingScilabPushButton) item
				.getAsSimplePushButton();
		swingItem.setAction(callback);

		// Not compatible with java 1.5
		// Hide the name text
		// swingItem.setHideActionText(true);
		swingItem.setText("");

		return item;
	}

	/**
	 * Create a checkbox item
	 * 
	 * @param callback
	 *            the associated callback
	 * @return the checkbox item
	 */
	protected static CheckBoxMenuItem createCheckBoxMenu(CallBack callback) {
		CheckBoxMenuItem item = ScilabCheckBoxMenuItem.createCheckBoxMenuItem();

		SwingScilabCheckBoxMenuItem swingItem = (SwingScilabCheckBoxMenuItem) item
				.getAsSimpleCheckBoxMenuItem();
		swingItem.setAction(callback);

		return item;
	}

	
	/**
	 * Action
	 * @param e parameters
	 * @see org.scilab.modules.gui.events.callback.CallBack#actionPerformed(java.awt.event.ActionEvent)
	 */
	@Override
	public abstract void actionPerformed(ActionEvent e);
	
	/**
	 * Not used
	 * @see org.scilab.modules.gui.events.callback.CallBack#callBack()
	 */
	@Override
	public void callBack() {
		assert "Must never be called as we bypass Callback.java".equals("");
	}
}