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

package org.scilab.modules.xcos.link;

import org.scilab.modules.xcos.link.commandcontrol.CommandControlLink;
import org.scilab.modules.xcos.link.explicit.ExplicitLink;
import org.scilab.modules.xcos.link.implicit.ImplicitLink;
import org.scilab.modules.xcos.port.BasicPort;
import org.scilab.modules.xcos.port.command.CommandPort;
import org.scilab.modules.xcos.port.control.ControlPort;
import org.scilab.modules.xcos.port.input.ExplicitInputPort;
import org.scilab.modules.xcos.port.input.ImplicitInputPort;
import org.scilab.modules.xcos.port.output.ExplicitOutputPort;
import org.scilab.modules.xcos.port.output.ImplicitOutputPort;

/**
 * Enum used to get the links and ports class from ids. 
 */
public enum LinkPortMap {
	/**
	 * Explicit input port mapping
	 */
	EX_INPUT(ExplicitLink.class, ExplicitInputPort.class, false),
	/**
	 * Implicit input port mapping
	 * 
	 * Note: for implicit link, the from and to start flag is inverted. So here
	 * the {@link #isStart} is inverted too.
	 */
	IM_INPUT(ImplicitLink.class, ImplicitInputPort.class, true),
	/**
	 * Explicit output port mapping
	 */
	EX_OUTPUT(ExplicitLink.class, ExplicitOutputPort.class, true),
	/**
	 * Implicit output port mapping
	 * 
	 * Note: for implicit link, the from and to start flag is inverted. So here
	 * the {@link #isStart} is inverted too.
	 */
	IM_OUTPUT(ImplicitLink.class, ImplicitOutputPort.class, false),
	/**
	 * Control port mapping
	 */
	CONTROL(CommandControlLink.class, ControlPort.class, false),
	/**
	 * Command port mapping
	 */
	COMMAND(CommandControlLink.class, CommandPort.class, true);
	
	private final Class< ? extends BasicLink> linkKlass;
	private final Class< ? extends BasicPort> portKlass;
	private final boolean isStart;
	
	/**
	 * Default constructor 
	 * @param linkKlass the associated link class
	 * @param portKlass the associated port class
	 * @param isStart is this port a start point ?
	 */
	private LinkPortMap(Class< ? extends BasicLink> linkKlass,
			Class< ? extends BasicPort> portKlass, boolean isStart) {
		this.linkKlass = linkKlass;
		this.portKlass = portKlass;
		this.isStart = isStart;
	}
	
	/**
	 * @return the associated link class
	 */
	public final Class< ? extends BasicLink> getLinkKlass() {
		return linkKlass;
	}

	/**
	 * @return the associated port class
	 */
	public final Class< ? extends BasicPort> getPortKlass() {
		return portKlass;
	}

	/**
	 * @return is this port a start point ?
	 */
	public final boolean isStart() {
		return isStart;
	}
	
	/*
	 * Static methods
	 */

	/**
	 * Get the enum value.
	 * 
	 * This method doesn't pass the cyclomatic complexity but is really simple
	 * as doesn't contains any operations but just a reasonable mapping.
	 * 
	 * @param type
	 *            the type field
	 * @param isStart
	 *            is this port a start point ?
	 * @return the enum value
	 */
	// CSOFF: CyclomaticComplexity
	public static LinkPortMap getLinkPortMap(int type, boolean isStart) {
		LinkPortMap ret = null;
		
		if (type == 1 && !isStart) {
			ret = LinkPortMap.EX_INPUT;
		} else if (type == 1 && isStart) {
			ret = LinkPortMap.EX_OUTPUT;
		} else if (type == 2 && !isStart) {
			ret = LinkPortMap.IM_INPUT;
		} else if (type == 2 && isStart) {
			ret = LinkPortMap.IM_OUTPUT;
		} else if (type == -1 && !isStart) {
			ret = LinkPortMap.CONTROL;
		} else if (type == -1 && isStart) {
			ret = LinkPortMap.COMMAND;
		}
		
		return ret;
	}
	// CSON: CyclomaticComplexity
	
	/**
	 * Get the start value from the xcos instance
	 * @param port the instance
	 * @return 1.0 if is a start point, 0.0 otherwise.
	 */
	public static double isStart(BasicPort port) {
		double ret = 0.0;
		
		final Class< ? extends BasicPort> klass = port.getClass();
		for (LinkPortMap current : values()) {
			if (klass.equals(current.getPortKlass())) {
				if (current.isStart()) {
					ret = 1.0;
				}
				break;
			}
		}
		
		return ret;
	}
	
	/**
	 * Get the link class associated with the type
	 * @param type the type field
	 * @return the link class
	 */
	public static Class< ? extends BasicLink> getLinkClass(int type) {
		return getLinkPortMap(type, false).getLinkKlass();
	}
	
	/**
	 * Get the port class associated with the link class.
	 * @param klass the link class
	 * @param isStart if an output port must be found.
	 * @return the port class
	 */
	public static Class< ? extends BasicPort> getPortClass(Class< ? extends BasicLink> klass, boolean isStart) {
		for (LinkPortMap pt : values()) {
			if (pt.getLinkKlass() == klass
					&& pt.isStart() == isStart) {
				return pt.getPortKlass();
			}
		}
		
		return null;
	}
}