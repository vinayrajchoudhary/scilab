/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2010 - DIGITEO - Clément DAVID
 * 
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at    
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.block.actions;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JColorChooser;

import org.scilab.modules.graph.ScilabGraph;
import org.scilab.modules.graph.actions.base.VertexSelectionDependantAction;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.xcos.graph.XcosDiagram;
import org.scilab.modules.xcos.utils.XcosMessages;

import com.mxgraph.util.mxConstants;
import com.mxgraph.util.mxUtils;

/**
 * Change the filled color of multiple blocks
 */
public final class FilledColorAction extends VertexSelectionDependantAction {
	/** Name of the action */
	public static final String NAME = XcosMessages.FILL_COLOR;
	/** Icon name of the action */
	public static final String SMALL_ICON = "";
	/** Mnemonic key of the action */
	public static final int MNEMONIC_KEY = 0;
	/** Accelerator key for the action */
	public static final int ACCELERATOR_KEY = 0;
    
    /**
     * @param scilabGraph graph
     */
    public FilledColorAction(ScilabGraph scilabGraph) {
    	super(scilabGraph);
    }

    /**
     * @param scilabGraph graph
     * @return menu item
     */
    public static MenuItem createMenu(ScilabGraph scilabGraph) {
	return createMenu(scilabGraph, FilledColorAction.class);
    }

	/**
	 * @param e parameter
	 * @see org.scilab.modules.graph.actions.base.DefaultAction#actionPerformed(java.awt.event.ActionEvent)
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
	XcosDiagram graph = (XcosDiagram) getGraph(null);
	Object[] selectedCells = graph.getSelectionCells();
	
	//if no cells are selected : Do nothing
	if (selectedCells.length == 0) { return; }

	// Get the selected cells statistics values
	Map<String, Integer> colorStats = new HashMap<String, Integer>();
	for (Object object : selectedCells) {
		String color = (String) graph.getCellStyle(object).get(mxConstants.STYLE_FILLCOLOR);
		if (colorStats.containsKey(color)) {
			colorStats.put(color, colorStats.get(color) + 1);
		} else {
			colorStats.put(color, 1);
		}
	}
	
	// Getting the most present color
	String color = "#FF0000";
	int max = 0;
	for (String key : colorStats.keySet()) {
		int current = colorStats.get(key);
		if (current > max) {
			color = key;
			max = current;
		}
	}
	
	// Apply the most common color as the default color
	Color newColor = JColorChooser.showDialog(getGraph(null).getAsComponent(), NAME, mxUtils.parseColor(color));

	if (newColor != null) {
	    graph.setCellStyles(mxConstants.STYLE_FILLCOLOR, mxUtils.hexString(newColor));
    	}
    }
}