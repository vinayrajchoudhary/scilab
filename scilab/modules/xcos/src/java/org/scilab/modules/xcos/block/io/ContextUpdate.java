package org.scilab.modules.xcos.block.io;

import java.io.File;
import java.io.IOException;

import org.scilab.modules.hdf5.scilabTypes.ScilabDouble;
import org.scilab.modules.hdf5.scilabTypes.ScilabList;
import org.scilab.modules.xcos.block.BasicBlock;
import org.scilab.modules.xcos.io.BlockReader;
import org.scilab.modules.xcos.utils.XcosInterpreterManagement;
import org.scilab.modules.xcos.utils.XcosInterpreterManagement.InterpreterException;

public abstract class ContextUpdate extends BasicBlock{

    private static final long serialVersionUID = 6076826729067963560L;
    
    /**
     * This enum represent all the subclasses of ContextUpdate .
     *
     * It is used to easily loop over a BasicBlock I/O blocks
     */
    public enum IOBlocks {
	EventInBlock(EventInBlock.class),
	EventOutBlock(EventOutBlock.class),
	ExplicitInBlock(ExplicitInBlock.class),
	ExplicitOutBlock(ExplicitOutBlock.class),
	ImplicitInBlock(ImplicitInBlock.class),
	ImplicitOutBlock(ImplicitOutBlock.class),
	Unknow(ContextUpdate.class);
	
	private Class<? extends ContextUpdate> klass;
	
	private IOBlocks(Class<? extends ContextUpdate> klass) {
	    this.klass = klass;
	}
	
	public Class<? extends ContextUpdate> getReferencedClass() {
	    return klass;
	}
    }
    
	public ContextUpdate() {
		super();
	}

	protected ContextUpdate(String label) {
		this();
		setDefaultValues();
		setValue(label);
	}

	/**
	 * Initialize the block with the default values
	 */
	@Override
	protected void setDefaultValues() {
		super.setDefaultValues();
		setNbZerosCrossing(new ScilabDouble(0));
		setNmode(new ScilabDouble(0));
		setODState(new ScilabList());
		setValue(1);
	}
    
    public void onContextChange(String[] context) {
	//prevent to open twice
	if(isLocked()) {
	    return;
	}
	
	final File tempOutput;
	final File tempInput;
	final File tempContext;
	try {
	    tempInput = File.createTempFile("xcos",".h5");
	    tempInput.deleteOnExit();

	    // Write scs_m
	    tempOutput = exportBlockStruct();
	    // Write context
	    tempContext = exportContext(context);

	    String cmd;
	    
	    cmd = "xcosBlockEval(\""+tempOutput.getAbsolutePath()+"\"";
	    cmd += ", \""+tempInput.getAbsolutePath()+"\"";
	    cmd += ", "+getInterfaceFunctionName();
	    cmd += ", \""+tempContext.getAbsolutePath()+"\");";

		try {
			XcosInterpreterManagement.synchronousScilabExec(cmd);
		} catch (InterpreterException e) {
			e.printStackTrace();
		}
		BasicBlock modifiedBlock = BlockReader.readBlockFromFile(tempInput.getAbsolutePath());
		updateBlockSettings(modifiedBlock);
	    
	} catch (IOException e) {
	    e.printStackTrace();
	}
    }
}