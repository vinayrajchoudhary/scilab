/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.scilab.modules.javasci;


import org.scilab.modules.types.ScilabTypeEnum;
import org.scilab.modules.types.ScilabIntegerTypeEnum;

 /**
   * Connector for Javasci v2.
   * This class should <b>not</b> be used directly
   * @see org.scilab.modules.javasci.Scilab
   * @author DIGITEO - Sylvestre LEDRU
   */
public class Call_Scilab {

 /**
   * Constructor
   */
 protected Call_Scilab() {
    throw new UnsupportedOperationException();
 }
  public static int Call_ScilabOpen(String SCIpath, boolean advancedMode, String ScilabStartup, int Stacksize) {
    return Call_ScilabJNI.Call_ScilabOpen(SCIpath, advancedMode, ScilabStartup, Stacksize);
  }

  public static boolean TerminateScilab(String ScilabQuit) {
    return Call_ScilabJNI.TerminateScilab(ScilabQuit);
  }

  public static int SendScilabJob(String job) {
    return Call_ScilabJNI.SendScilabJob(job);
  }

  public static int SendScilabJobs(String[] jobs, int numberjobs) {
    return Call_ScilabJNI.SendScilabJobs(jobs, numberjobs);
  }

  public static void SetFromJavaToON() {
    Call_ScilabJNI.SetFromJavaToON();
  }

  public static boolean isGraphicOpened() {
    return Call_ScilabJNI.isGraphicOpened();
  }

  public static int GetLastErrorCode() {
    return Call_ScilabJNI.GetLastErrorCode();
  }

  public static boolean isExistingVariable(String varname) {
    return Call_ScilabJNI.isExistingVariable(varname);
  }

  public static String getLastErrorMessage() {
    return Call_ScilabJNI.getLastErrorMessage();
  }

  public static ScilabTypeEnum getVariableType(String varname) {
    return ScilabTypeEnum.swigToEnum(Call_ScilabJNI.getVariableType(varname));
  }

  public static ScilabIntegerTypeEnum getIntegerPrecision(String varname) {
    return ScilabIntegerTypeEnum.swigToEnum(Call_ScilabJNI.getIntegerPrecision(varname));
  }

  public static boolean isComplex(String varname) {
    return Call_ScilabJNI.isComplex(varname);
  }

  public static String[][] getString(String variableName) {
    return Call_ScilabJNI.getString(variableName);
  }

  public static int putString(String variableName, String[][] variable) {
    return Call_ScilabJNI.putString(variableName, variable);
  }

  public static int putDoubleComplex(String variableName, double[] variable, int nbRow, int nbCol) {
    return Call_ScilabJNI.putDoubleComplex(variableName, variable, nbRow, nbCol);
  }

  public static double[][] getDouble(String variableName) {
    return Call_ScilabJNI.getDouble(variableName);
  }

  public static int putDouble(String variableName, double[][] variable) {
    return Call_ScilabJNI.putDouble(variableName, variable);
  }

  public static boolean[][] getBoolean(String variableName) {
    return Call_ScilabJNI.getBoolean(variableName);
  }

  public static int putBoolean(String variableName, boolean[][] variable) {
    return Call_ScilabJNI.putBoolean(variableName, variable);
  }

  public static byte[][] getByte(String variableName) {
    return Call_ScilabJNI.getByte(variableName);
  }

  public static int putByte(String variableName, byte[][] variable) {
    return Call_ScilabJNI.putByte(variableName, variable);
  }

  public static byte[][] getUnsignedByte(String variableName) {
    return Call_ScilabJNI.getUnsignedByte(variableName);
  }

  public static int putUnsignedByte(String variableName, byte[][] variable) {
    return Call_ScilabJNI.putUnsignedByte(variableName, variable);
  }

  public static short[][] getShort(String variableName) {
    return Call_ScilabJNI.getShort(variableName);
  }

  public static int putShort(String variableName, short[][] variable) {
    return Call_ScilabJNI.putShort(variableName, variable);
  }

  public static short[][] getUnsignedShort(String variableName) {
    return Call_ScilabJNI.getUnsignedShort(variableName);
  }

  public static int putUnsignedShort(String variableName, short[][] variable) {
    return Call_ScilabJNI.putUnsignedShort(variableName, variable);
  }

  public static int[][] getInt(String variableName) {
    return Call_ScilabJNI.getInt(variableName);
  }

  public static int putInt(String variableName, int[][] variable) {
    return Call_ScilabJNI.putInt(variableName, variable);
  }

  public static int[][] getUnsignedInt(String variableName) {
    return Call_ScilabJNI.getUnsignedInt(variableName);
  }

  public static int putUnsignedInt(String variableName, int[][] variable) {
    return Call_ScilabJNI.putUnsignedInt(variableName, variable);
  }

  public static double[][] getDoubleComplexReal(String variableName) {
    return Call_ScilabJNI.getDoubleComplexReal(variableName);
  }

  public static double[][] getDoubleComplexImg(String variableName) {
    return Call_ScilabJNI.getDoubleComplexImg(variableName);
  }

}