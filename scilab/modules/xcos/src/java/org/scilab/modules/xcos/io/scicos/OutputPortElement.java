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

package org.scilab.modules.xcos.io.scicos;

import static java.util.Arrays.asList;

import java.util.List;

import org.scilab.modules.types.scilabTypes.ScilabDouble;
import org.scilab.modules.types.scilabTypes.ScilabMList;
import org.scilab.modules.types.scilabTypes.ScilabString;
import org.scilab.modules.types.scilabTypes.ScilabType;
import org.scilab.modules.xcos.port.BasicPort.DataType;
import org.scilab.modules.xcos.port.output.ExplicitOutputPort;
import org.scilab.modules.xcos.port.output.ImplicitOutputPort;
import org.scilab.modules.xcos.port.output.OutputPort;

/**
 * Perform an output port transformation between Scicos and Xcos.
 * 
 * On this element we doesn't validate the Scicos values has they have been
 * already checked on the {@link BlockElement}.
 */
public class OutputPortElement extends AbstractElement<OutputPort> {
	private static final List<String> DATA_FIELD_NAMES = asList(
			"Block", "graphics", "model", "gui", "doc");
	
	private static final int GRAPHICS_INDEX = 1;
	private static final int MODEL_INDEX = 2;
	
	private static final int GRAPHICS_POUT_INDEX = 7;
	private static final int GRAPHICS_OUTIMPL_INDEX = 13;
	
	private static final int MODEL_OUT_DATALINE_INDEX = 5;
	private static final int MODEL_OUT_DATACOL_INDEX = 6;
	private static final int MODEL_OUT_DATATYPE_INDEX = 7;
	
	private static final String EXPLICIT = "E";
	private static final String IMPLICIT = "I";
	
	/** Mutable fields to easily get the data through methods */ 
	private ScilabMList data;
	private final ScilabMList graphics;
	private final ScilabMList model;
	
	private int alreadyDecodedCount;
	private boolean allColumnsAreZeros = true;
	
	/**
	 * Default constructor
	 * 
	 * @param element the Scicos block parameters used by this element.
	 */
	public OutputPortElement(ScilabType element) {
		data = (ScilabMList) element;
		graphics = (ScilabMList) data.get(GRAPHICS_INDEX);
		model = (ScilabMList) data.get(MODEL_INDEX);
	}
	
	/**
	 * @return the number of output port for the element.
	 */
	public int getNumberOfOutputPort() {
		return model.get(MODEL_OUT_DATALINE_INDEX).getHeight();
	}
	
	/**
	 * Decode Scicos element into the block.
	 * 
	 * @param element
	 *            the scicos element
	 * @param into
	 *            the previously instantiated block.
	 * @return the modified into block.
	 * @throws ScicosFormatException
	 *             on error.
	 * @see org.scilab.modules.xcos.io.scicos.Element#decode(org.scilab.modules.types.scilabTypes.ScilabType,
	 *      java.lang.Object)
	 */
	@Override
	public OutputPort decode(ScilabType element, OutputPort into)
			throws ScicosFormatException {
		
		OutputPort port;
		data = (ScilabMList) element;
		
		port = allocatePort();
		fillParameters(port);
		
		// Update the index counter
		alreadyDecodedCount++;
		
		return port;
	}

	
	
	/**
	 * Allocate a port according to the explicit/implicit values.
	 * 
	 * @return a new typed port
	 */
	private OutputPort allocatePort() {
		OutputPort ret;
		ScilabType outImpl = graphics.get(GRAPHICS_OUTIMPL_INDEX);
		
		/*
		 * backward compatibility, use explicit as default.
		 */
		if (isEmptyField(outImpl)) {
			return new ExplicitOutputPort();
		}
		final ScilabString outImplicit = (ScilabString) outImpl;
				
		final boolean isColumnDominant = outImplicit.getHeight() >= outImplicit.getWidth();
		final int[] indexes = getIndexes(alreadyDecodedCount, isColumnDominant);
		final String[][] outimpl = outImplicit.getData();
		
		if (outimpl[indexes[0]][indexes[1]].equals(EXPLICIT)) {
			ret = new ExplicitOutputPort();
		} else if (outimpl[indexes[0]][indexes[1]].equals(IMPLICIT)) {
			ret = new ImplicitOutputPort();
		} else {
			// when not specified, use explicit
			ret = new ExplicitOutputPort();
		}
		
		return ret;
	}

	/**
	 * Fill the port with the parameters from the model structure.
	 * @param port the target instance 
	 */
	private void fillParameters(OutputPort port) {
		ScilabDouble dataLines = (ScilabDouble) model.get(MODEL_OUT_DATALINE_INDEX);
		ScilabDouble dataColumns = (ScilabDouble) model.get(MODEL_OUT_DATACOL_INDEX);
		ScilabDouble dataType = (ScilabDouble) model.get(MODEL_OUT_DATATYPE_INDEX);

		if (dataLines.getRealPart() != null) {
			int nbLines = (int) dataLines.getRealPart()[alreadyDecodedCount][0];
			port.setDataLines(nbLines);
		}
		if (dataColumns.getRealPart() != null) {
			int nbColumns = (int) dataColumns.getRealPart()[alreadyDecodedCount][0];
			port.setDataColumns(nbColumns);
		}
		if (dataType.getRealPart() != null) {
			int type;
			
			try {
				type = (int) dataType.getRealPart()[alreadyDecodedCount][0];
			} catch (ArrayIndexOutOfBoundsException e) {
				type = 1;
			}
			
			port.setDataType(DataType.convertScilabValue(type));
		}
	}

	/**
	 * Test if the current instance can be used to decode the element
	 * 
	 * @param element the current element
	 * @return true, if the element can be decoded, false otherwise
	 * @see org.scilab.modules.xcos.io.scicos.Element#canDecode(org.scilab.modules.types.scilabTypes.ScilabType)
	 */
	@Override
	public boolean canDecode(ScilabType element) {
		data = (ScilabMList) element;
		
		final String type = ((ScilabString) data.get(0)).getData()[0][0];
		return type.equals(DATA_FIELD_NAMES.get(0)) && getNumberOfOutputPort() > alreadyDecodedCount;
	}
	
	/**
	 * Encode the instance into the element
	 * 
	 * @param from the source instance
	 * @param element the previously allocated element.
	 * @return the element parameter
	 * @see org.scilab.modules.xcos.io.scicos.Element#encode(java.lang.Object, org.scilab.modules.types.scilabTypes.ScilabType)
	 */
	@Override
	public ScilabType encode(OutputPort from, ScilabType element) {
		data = (ScilabMList) element;
		
		if (data == null) {
			throw new IllegalArgumentException();
		}

		encodeModel(from);
		encodeGraphics(from);
		
		// Update the index counter
		alreadyDecodedCount++;
		
		return data;
	}

	/**
	 * Encode the data into the model fields.
	 * 
	 * This method fills :
	 * <ul>
	 * <li>Block.model.out</li>
	 * <li>Block.model.out2</li>
	 * <li>Block.model.outtyp</li>
	 * </ul>
	 * 
	 * @param from the source data
	 */
	private void encodeModel(OutputPort from) {
		ScilabDouble sciValues;
		double[][] values;
		
		// out
		sciValues = (ScilabDouble) model.get(MODEL_OUT_DATALINE_INDEX);
		values = sciValues.getRealPart();
		int datalines = from.getDataLines();
		values[alreadyDecodedCount][0] = datalines;
		
		// out2
		sciValues = (ScilabDouble) model.get(MODEL_OUT_DATACOL_INDEX);
		values = sciValues.getRealPart();
		int datacolumns = from.getDataColumns();
		if (datacolumns == 0) {
			datacolumns = 1;
		} else {
			allColumnsAreZeros = false;
		}
		values[alreadyDecodedCount][0] = datacolumns;
		
		// outtyp
		sciValues = (ScilabDouble) model.get(MODEL_OUT_DATATYPE_INDEX);
		values = sciValues.getRealPart();
		values[alreadyDecodedCount][0] = from.getDataType().getAsDouble();
	}
	
	/**
	 * Encode the data into the graphic fields.
	 * 
	 * This method fills :
	 * <ul>
	 * <li>Block.graphics.pout</li>
	 * <li>Block.graphics.out_implicit</li>
	 * </ul>
	 * 
	 * @param from the source data
	 */
	private void encodeGraphics(OutputPort from) {
		ScilabDouble sciValues;
		ScilabString sciStrings;
		double[][] values;
		String[][] strings;
		
		// pout
		sciValues = (ScilabDouble) graphics.get(GRAPHICS_POUT_INDEX);
		values = sciValues.getRealPart();
		values[alreadyDecodedCount][0] = from.getConnectedLinkId();
		
		// out_implicit
		sciStrings = (ScilabString) graphics.get(GRAPHICS_OUTIMPL_INDEX);
		strings = sciStrings.getData();
		strings[alreadyDecodedCount][0] = from.getType().getAsString();
	}
	
	/**
	 * Clear Block.model.out2 if it contains only zeros.
	 */
	@Override
	public void afterEncode() {
		if (allColumnsAreZeros) {
			model.set(MODEL_OUT_DATACOL_INDEX, new ScilabDouble());
		}
	}
}