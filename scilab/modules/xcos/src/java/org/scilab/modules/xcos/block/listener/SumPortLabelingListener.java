/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Clément DAVID
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xcos.block.listener;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import org.scilab.modules.types.ScilabDouble;
import org.scilab.modules.xcos.block.BasicBlock;
import org.scilab.modules.xcos.port.BasicPort;
import org.scilab.modules.xcos.port.input.InputPort;

/**
 * Change the port label on ipar change.
 * 
 * This listener must be installed on "integerParameters" property.
 */
public class SumPortLabelingListener implements PropertyChangeListener, Serializable {
	
	private static final String NOT_PRINTED_LABEL = "+";
	private static SumPortLabelingListener instance;
	
	/**
	 * Default constructor 
	 */
	public SumPortLabelingListener() { }
	
	/**
	 * @return the shared instance
	 */
	public static SumPortLabelingListener getInstance() {
		if (instance == null) {
			instance = new SumPortLabelingListener();
		}
		return instance;
	}

	/**
	 * Change the label of the port according to the integer parameters
	 * property.
	 * 
	 * @param evt the event
	 * @see java.beans.PropertyChangeListener#propertyChange(java.beans.PropertyChangeEvent)
	 */
	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		final BasicBlock source = (BasicBlock) evt.getSource();
		final ScilabDouble data = (ScilabDouble) evt.getNewValue();

		/**
		 * Get the input port children
		 */
		final List<InputPort> ports = new ArrayList<InputPort>();
		for (int i = 0; i < source.getChildCount(); i++) {
			final BasicPort port = (BasicPort) source.getChildAt(i);
			
			if (port instanceof InputPort) {
				ports.add((InputPort) port);
			}
		}

		/**
		 * Set the ports labels
		 */
		for (InputPort port : ports) {
			final double gain;
			
			if (data.isEmpty()) {
				gain = 1; 
			} else {
				gain = data.getRealPart()[port.getOrdering() - 1][0]; 
			}
			
			port.setValue(getLabel(gain));
		}
		
		/**
		 * Check if all the values are equals to the default one.
		 */
		boolean allPortIsDefaultLabel = true;
		for (InputPort port : ports) {
			if (port.getValue() instanceof String) {
				String current = port.getValue().toString();
				if (!NOT_PRINTED_LABEL.equals(current)) {
					allPortIsDefaultLabel = false;
					break;
				}
			}
		}

		if (!allPortIsDefaultLabel) {
			return;
		}
		
		/**
		 * When all values are equals to the default one, set it to the block
		 * and hide the children.
		 */
		source.setValue(NOT_PRINTED_LABEL);
		for (InputPort port : ports) {
			port.setValue("");
		}
	}
	
	/**
	 * Return the symbol for the gain value
	 * @param gain the current gain
	 * @return A label representing the gain
	 */
	private String getLabel(double gain) {
		if (gain > 0) {
			return NOT_PRINTED_LABEL; // "+"
		} else {
			return "-";
		}
	}
}