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

import org.scilab.modules.types.scilabTypes.ScilabBoolean;
import org.scilab.modules.types.scilabTypes.ScilabDouble;
import org.scilab.modules.types.scilabTypes.ScilabList;
import org.scilab.modules.types.scilabTypes.ScilabMList;
import org.scilab.modules.types.scilabTypes.ScilabString;
import org.scilab.modules.types.scilabTypes.ScilabTList;
import org.scilab.modules.types.scilabTypes.ScilabType;
import org.scilab.modules.xcos.block.BasicBlock;
import org.scilab.modules.xcos.block.BasicBlock.SimulationFunctionType;
import org.scilab.modules.xcos.io.scicos.ScicosFormatException.WrongElementException;
import org.scilab.modules.xcos.io.scicos.ScicosFormatException.WrongStructureException;
import org.scilab.modules.xcos.io.scicos.ScicosFormatException.WrongTypeException;
import org.scilab.modules.xcos.port.command.CommandPort;
import org.scilab.modules.xcos.port.control.ControlPort;

/**
 * Protected class which decode model fields of a block.
 * 
 * This class is intentionally package-protected to prevent external use.
 */
//CSOFF: ClassDataAbstractionCoupling
class BlockModelElement extends BlockPartsElement {
	private static final List<String> DATA_FIELD_NAMES = asList("model", "sim",
			"in", "in2", "intyp", "out", "out2", "outtyp", "evtin", "evtout",
			"state", "dstate", "odstate", "rpar", "ipar", "opar", "blocktype",
			"firing", "dep_ut", "label", "nzcross", "nmode", "equations");

	private static final int CTRL_PORT_INDEX = 8;
	private static final int CMD_PORT_INDEX = 9;
	private static final int STATE_INDEX = 10;
	private static final int FIRING_INDEX = 17;
	private static final int DEPENDU_INDEX = 18;

	/** Mutable field to easily get the data through methods */
	private ScilabMList data;
	
	/**
	 * Default constructor
	 */
	public BlockModelElement() { }

	/**
	 * Decode Scicos element into the block.
	 * 
	 * This decode method doesn't coverage Port management because we need
	 * graphics informations to handle it.
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
	public BasicBlock decode(ScilabType element, BasicBlock into)
			throws ScicosFormatException {

		if (into == null) {
			throw new IllegalArgumentException();
		}

		data = (ScilabMList) element;

		validate();

		/*
		 * fill the data
		 */
		fillSimulationFunction(into);
		fillControlCommandPorts(into);
		fillFirstRawParameters(into);
		fillFiringParameters(into);
		fillSecondRawParameters(into);

		return into;
	}

	/**
	 * Fill the simulation data into the block
	 * 
	 * @param into
	 *            the target instance
	 */
	private void fillSimulationFunction(BasicBlock into) {
		String functionName = into.getSimulationFunctionName();
		SimulationFunctionType functionType = into.getSimulationFunctionType();

		if (data.get(1) instanceof ScilabString) {
			functionName = ((ScilabString) data.get(1)).getData()[0][0];
		} else if ((data.get(1) instanceof ScilabList)) {
			functionName = ((ScilabString) ((ScilabList) data.get(1)).get(0))
					.getData()[0][0];
			functionType = SimulationFunctionType
					.convertScilabValue((int) ((ScilabDouble) ((ScilabList) data
							.get(1)).get(1)).getRealPart()[0][0]);
		}

		into.setSimulationFunctionName(functionName);
		into.setSimulationFunctionType(functionType);
	}

	/**
	 * Fill the block with the control and command ports
	 * 
	 * @param into
	 *            the target instance
	 */
	private void fillControlCommandPorts(BasicBlock into) {
		ScilabDouble dataNbControlPort = (ScilabDouble) data
				.get(CTRL_PORT_INDEX);
		ScilabDouble dataNbCommandPort = (ScilabDouble) data
				.get(CMD_PORT_INDEX);

		if (dataNbControlPort.getRealPart() != null) {
			int nbControlPort = dataNbControlPort.getHeight();
			for (int i = 0; i < nbControlPort; i++) {
				into.addPort(new ControlPort());
			}
		}

		if (dataNbCommandPort.getRealPart() != null) {
			int nbCommandPort = dataNbCommandPort.getHeight();
			for (int i = 0; i < nbCommandPort; i++) {
				into.addPort(new CommandPort());
			}
		}
	}

	/**
	 * Fill the block with the first raw parameters
	 * 
	 * @param into
	 *            the target instance
	 */
	private void fillFirstRawParameters(BasicBlock into) {
		// state
		int field = STATE_INDEX;
		into.setState(data.get(field));

		// dstate
		field++;
		into.setDState(data.get(field));

		// odstate
		field++;
		into.setODState(data.get(field));

		// rpar
		field++;
		into.setRealParameters(data.get(field));

		// ipar
		field++;
		into.setIntegerParameters(data.get(field));

		// opar
		field++;
		into.setObjectsParameters(data.get(field));

		// blocktype
		field++;
		into.setBlockType(((ScilabString) data.get(field)).getData()[0][0]);
	}

	/**
	 * Fill the block with the firing parameters
	 * 
	 * @param into
	 *            the target instance
	 */
	private void fillFiringParameters(BasicBlock into) {
		/*
		 * A boolean can be used to indicate that no initial event will be emitted. 
		 */
		if (data.get(FIRING_INDEX) instanceof ScilabBoolean) {
			return;
		}
		
		/*
		 * Normal behavior
		 */
		final ScilabDouble firing = (ScilabDouble) data.get(FIRING_INDEX);

		if (!isEmptyField(firing)) {
			final List<CommandPort> allCommandPorts = BasicBlockInfo
					.getAllTypedPorts(into, false, CommandPort.class);

			final boolean isColumnDominant = firing.getHeight() >= firing
					.getWidth();
			final double[][] values = firing.getRealPart();
			final int[] indexes = {0, 0};

			for (int i = 0; i < allCommandPorts.size(); i++) {
				allCommandPorts.get(i).setInitialState(
						values[indexes[0]][indexes[1]]);
				incrementIndexes(indexes, isColumnDominant);
			}
		}
	}

	/**
	 * Fill the block with the second raw parameters
	 * 
	 * @param into
	 *            the target instance
	 */
	private void fillSecondRawParameters(BasicBlock into) {
		// dep-ut
		int field = DEPENDU_INDEX;
		into.setDependsOnU(((ScilabBoolean) data.get(field)).getData()[0][0]);
		into.setDependsOnT(((ScilabBoolean) data.get(field)).getData()[0][1]);

		// label
		// do nothing
		field++;

		// nzcross
		field++;
		into.setNbZerosCrossing(data.get(field));

		// nmode
		field++;
		into.setNmode(data.get(field));

		// equation
		field++;
		into.setEquations(data.get(field));
	}

	/**
	 * Validate the current data.
	 * 
	 * This method doesn't pass the metrics because it perform many test.
	 * Therefore all these tests are trivial and the conditioned action only
	 * throw an exception.
	 * 
	 * @throws ScicosFormatException
	 *             when there is a validation error.
	 */
	// CSOFF: CyclomaticComplexity
	// CSOFF: NPathComplexity
	// CSOFF: JavaNCSS
	// CSOFF: MethodLength
	private void validate() throws ScicosFormatException {
		if (!canDecode(data)) {
			throw new WrongElementException();
		}

		int field = 0;

		// we test if the structure as enough field
		if (data.size() != DATA_FIELD_NAMES.size()) {
			throw new WrongStructureException();
		}

		/*
		 * Checking the MList header
		 */

		// Check the first field
		if (!(data.get(field) instanceof ScilabString)) {
			throw new WrongTypeException();
		}
		final String[] header = ((ScilabString) data.get(field)).getData()[0];

		// Checking for the field names
		if (header.length != DATA_FIELD_NAMES.size()) {
			throw new WrongStructureException();
		}
		for (int i = 0; i < header.length; i++) {
			if (!header[i].equals(DATA_FIELD_NAMES.get(i))) {
				throw new WrongStructureException();
			}
		}

		/*
		 * Checking the data
		 */

		// sim : String or list(String, int)
		field++;
		if (!(data.get(field) instanceof ScilabString)
				&& !(data.get(field) instanceof ScilabList)) {
			throw new WrongTypeException();
		}

		// in
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// in2
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// intyp
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// out
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// out2
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// outtyp
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// evtin
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// evtout
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// state
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// dstate
		// TODO: the ScilabString value is undocumented
		field++;
		if (!(data.get(field) instanceof ScilabDouble)
				&& !(data.get(field) instanceof ScilabString)) {
			throw new WrongTypeException();
		}

		// odstate
		field++;
		if (!(data.get(field) instanceof ScilabDouble)
				&& !(data.get(field) instanceof ScilabList)) {
			throw new WrongTypeException();
		}

		// rpar
		// SuperBlocks store all "included" data in rpar field.
		field++;
		if (!(data.get(field) instanceof ScilabDouble)
				&& !(data.get(field) instanceof ScilabMList)
				&& !(data.get(field) instanceof ScilabString)) {
			throw new WrongTypeException();
		}

		// ipar
		// !! WARNING !! scifunc_block_m ipar = list(...)
		field++;
		if (!(data.get(field) instanceof ScilabDouble)
				&& !(data.get(field) instanceof ScilabList)) {
			throw new WrongTypeException();
		}

		// opar
		field++;
		if (!(data.get(field) instanceof ScilabList)) {
			throw new WrongTypeException();
		}

		// blocktype
		field++;
		if (!(data.get(field) instanceof ScilabString)) {
			throw new WrongTypeException();
		}

		// firing
		field++;
		if (!(data.get(field) instanceof ScilabDouble)
				&& !(data.get(field) instanceof ScilabBoolean)) {
			throw new WrongTypeException();
		}

		// dep-ut
		field++;
		if (!(data.get(field) instanceof ScilabBoolean)) {
			throw new WrongTypeException();
		}

		// label
		field++;
		if (!(data.get(field) instanceof ScilabString)) {
			throw new WrongTypeException();
		}

		// nzcross
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// nmode
		field++;
		if (!(data.get(field) instanceof ScilabDouble)) {
			throw new WrongTypeException();
		}

		// equations
		field++;
		if (!(data.get(field) instanceof ScilabTList)
				&& !isEmptyField(data.get(field))) {
			throw new WrongTypeException();
		}
	}
	// CSON: CyclomaticComplexity
	// CSON: NPathComplexity
	// CSON: JavaNCSS
	// CSON: MethodLength

	/**
	 * Check if the element can be decoded.
	 * 
	 * @param element
	 *            the Scicos element
	 * @return true, if the Scicos types match.
	 * @see org.scilab.modules.xcos.io.scicos.Element#canDecode(org.scilab.modules.types.scilabTypes.ScilabType)
	 */
	@Override
	public boolean canDecode(ScilabType element) {
		data = (ScilabMList) element;

		final String type = ((ScilabString) data.get(0)).getData()[0][0];
		return type.equals(DATA_FIELD_NAMES.get(0));
	}

	/**
	 * Encode the instance into the element
	 * 
	 * @param from the source instance
	 * @param element must be null.
	 * @return the element parameter
	 * @see org.scilab.modules.xcos.io.scicos.Element#encode(java.lang.Object, org.scilab.modules.types.scilabTypes.ScilabType)
	 */
	@Override
	public ScilabType encode(BasicBlock from, ScilabType element) {
		data = (ScilabMList) element;
		int field = 0;
		
		if (data == null) {
			data = allocateElement();
		} else {
			throw new IllegalArgumentException("The element parameter must be null.");
		}
		
		/*
		 * Fill the element
		 */
		field++; // sim
		data.set(field, from.getSimulationFunctionNameAndType());
		
		/*
		 * Fields managed by specific elements.
		 * 
		 * see InputPortElement and OutputPortElement.
		 */
		field++; // in
		field++; // in2
		field++; // intyp
		field++; // out
		field++; // out2
		field++; // outtyp
		
		field++; // evtin
		final List<ControlPort> ctrlPorts = BasicBlockInfo.getAllTypedPorts(from, false, ControlPort.class);
		data.set(field, BasicBlockInfo.getAllPortsDataLines(ctrlPorts));
		field++; // evtout
		final List<CommandPort> cmdPorts = BasicBlockInfo.getAllTypedPorts(from, false, CommandPort.class);
		data.set(field, BasicBlockInfo.getAllPortsDataLines(cmdPorts));
		
		field++; // state
		data.set(field, from.getState());
		field++; // dstate
		data.set(field, from.getDState());
		field++; // odstate
		data.set(field, from.getODState());
		
		field++; // rpar
		data.set(field, from.getRealParameters());
		field++; // ipar
		data.set(field, from.getIntegerParameters());
		field++; // opar
		data.set(field, from.getObjectsParameters());
		
		field++; // blocktype
		data.set(field, new ScilabString(from.getBlockType()));
		
		field++; // firing
		data.set(field, from.getAllCommandPortsInitialStates());
		
		field++; // dep_ut
		boolean[][] dependsOnUandT = {{from.isDependsOnU() , from.isDependsOnT()}};
		data.set(field, new ScilabBoolean(dependsOnUandT));
		
		field++; // label
		data.set(field, new ScilabString(""));
		
		field++; // nzcross
		data.set(field, from.getNbZerosCrossing());
		
		field++; // nmode
		data.set(field, from.getNmode());
		
		field++; // equations
		if (from.getEquations() != null) {
			data.set(field, from.getEquations());
		}
		
		return data;
	}

	/**
	 * Allocate a new element
	 * @return the new element
	 */
	private ScilabMList allocateElement() {
		ScilabMList element = new ScilabMList(DATA_FIELD_NAMES.toArray(new String[0]));
		element.add(new ScilabList()); // sim
		addSizedPortVector(element, ScilabDouble.class, getInSize()); // in
		addSizedPortVector(element, ScilabDouble.class, getInSize()); // in2
		addSizedPortVector(element, ScilabDouble.class, getInSize()); // intyp
		addSizedPortVector(element, ScilabDouble.class, getOutSize()); // out
		addSizedPortVector(element, ScilabDouble.class, getOutSize()); // out2
		addSizedPortVector(element, ScilabDouble.class, getOutSize()); // outtyp
		addSizedPortVector(element, ScilabDouble.class, getEinSize()); // evtin
		addSizedPortVector(element, ScilabDouble.class, getEoutSize()); // evtout
		element.add(new ScilabDouble()); // state
		element.add(new ScilabDouble()); // dstate
		element.add(new ScilabDouble()); // ostate
		element.add(new ScilabDouble()); // rpar
		element.add(new ScilabDouble()); // ipar
		element.add(new ScilabDouble()); // opar
		element.add(new ScilabString()); // blocktype
		element.add(new ScilabDouble()); // firing
		element.add(new ScilabDouble()); // dep_ut
		element.add(new ScilabString("")); // label
		element.add(new ScilabDouble()); // nzcross
		element.add(new ScilabDouble()); // nmode
		element.add(new ScilabList()); // equations
		return element;
	}
}
//CSON: ClassDataAbstractionCoupling