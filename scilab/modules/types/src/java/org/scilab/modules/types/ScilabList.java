/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2009-2009 - DIGITEO - Bruno JOFRET
 * 
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 * 
 */

package org.scilab.modules.types;

import java.util.ArrayList;
import java.util.Collection;

/**
 * This class provides a representation on the Scilab List datatype
 * <br>
 * Example:<br />
 * <code>
 * ScilabList data = new ScilabList();<br />
 * data.add(new ScilabString("hello"));<br />
 * data.add(new ScilabDouble(2));<br />
 * </code>
 * @see org.scilab.modules.javasci.Scilab
 */
public class ScilabList extends ArrayList<ScilabType> implements ScilabType {
	
	/**
	 * Construct an empty Scilab list.
	 */
	public ScilabList() {
		super();
	}

	/**
	 * Construct a list containing the elements of the specified collection, in
	 * the order that they are returned by the specified collection's iterator.
	 * 
	 * @param c
	 *			the collection whose elements are to be placed into this list.
	 */
	public ScilabList(Collection< ? extends ScilabType> c) {
		super(c);
	}
	
	/**
	 * @return 1 when there is data on the list, 0 otherwise.
	 * @see org.scilab.modules.types.ScilabType#getHeight()
	 */
	public int getHeight() {
		if (isEmpty()) {
			return 0;
		}
		return 1;
	}

	/**
	 * @return 1 when there is data on the list, 0 otherwise.
	 * @see org.scilab.modules.types.ScilabType#getWidth()
	 */
	public int getWidth() {
		if (isEmpty()) {
			return 0;
		}
		return size();
	}

	/**
	 * Display the representation in the Scilab language of the type
	 * @return the pretty-printed data 
	 * @see java.util.AbstractCollection#toString()
	 */
	public String toString() {

		StringBuffer result = new StringBuffer();
		if (isEmpty()) {
			result.append("list()");
			return result.toString();
		}

		result.append("list(");
		for (int i = 0; i < size(); i++) {
			result.append(get(i).toString());
			if (i != size() - 1) {
				result.append(", ");
			}
		}
		result.append(")");

		return result.toString();
	}
}