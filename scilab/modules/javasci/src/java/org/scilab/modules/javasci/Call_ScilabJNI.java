/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.scilab.modules.javasci;


/* It is generated code. Disable checkstyle */
//CHECKSTYLE:OFF
 /**
   * Connector for Javasci v2.
   * This class should <b>not</b> be used directly
   * @see org.scilab.modules.javasci.Scilab
   * @author DIGITEO - Sylvestre LEDRU
   */
class Call_ScilabJNI {

  /**
    * Constructor
    */
  protected Call_ScilabJNI() {
    throw new UnsupportedOperationException();
  }

  static {
    try {
    if (System.getProperty("os.name").toLowerCase().contains("windows")) {
        System.loadLibrary("javasci");
    } else {
        System.loadLibrary("scilab");
        System.loadLibrary("javasci2");
        }
    } catch (SecurityException e) {
        System.err.println("A security manager exists and does not allow the loading of the specified dynamic library :");
        e.printStackTrace(System.err);
    } catch (UnsatisfiedLinkError e)    {
        System.err.println("The native library javasci does not exist or cannot be found.");
        e.printStackTrace(System.err);
    }
  }

  public final static native int Call_ScilabOpen(String jarg1, boolean jarg2, String jarg3, int jarg4);
  public final static native boolean TerminateScilab(String jarg1);
  public final static native int SendScilabJob(String jarg1);
  public final static native int SendScilabJobs(String[] jarg1, int jarg2);
  public final static native void SetFromJavaToON();
  public final static native boolean isGraphicOpened();
  public final static native int GetLastErrorCode();
  public final static native boolean isExistingVariable(String jarg1);
  public final static native String getLastErrorMessage();
  public final static native int getVariableType(String jarg1);
  public final static native int getIntegerPrecision(String jarg1);
  public final static native boolean isComplex(String jarg1);
  public final static native String[][] getString(String jarg1);
  public final static native int putString(String jarg1, String[][] jarg2);
  public final static native int putDoubleComplex(String jarg1, double[] jarg2, int jarg3, int jarg4);
  public final static native double[][] getDouble(String jarg1);
  public final static native int putDouble(String jarg1, double[][] jarg2);
  public final static native boolean[][] getBoolean(String jarg1);
  public final static native int putBoolean(String jarg1, boolean[][] jarg2);
  public final static native byte[][] getByte(String jarg1);
  public final static native int putByte(String jarg1, byte[][] jarg2);
  public final static native byte[][] getUnsignedByte(String jarg1);
  public final static native int putUnsignedByte(String jarg1, byte[][] jarg2);
  public final static native short[][] getShort(String jarg1);
  public final static native int putShort(String jarg1, short[][] jarg2);
  public final static native short[][] getUnsignedShort(String jarg1);
  public final static native int putUnsignedShort(String jarg1, short[][] jarg2);
  public final static native int[][] getInt(String jarg1);
  public final static native int putInt(String jarg1, int[][] jarg2);
  public final static native int[][] getUnsignedInt(String jarg1);
  public final static native int putUnsignedInt(String jarg1, int[][] jarg2);
  public final static native double[][] getDoubleComplexReal(String jarg1);
  public final static native double[][] getDoubleComplexImg(String jarg1);
}