/* Generated by GIWS (version 1.2.0) */
/*

Copyright 2007-2008 INRIA
Copyright 2008-2010 DIGITEO

Author : Sylvestre Ledru & others

This is generated code.

This software is a computer program whose purpose is to hide the complexity
of accessing Java objects/methods from C++ code.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
*/


#ifndef __ORG_SCILAB_MODULES_XCOS_PALETTE_PALETTE__
#define __ORG_SCILAB_MODULES_XCOS_PALETTE_PALETTE__
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <jni.h>

#include "GiwsException.hxx"

#ifndef _MSC_VER /* Defined anyway with Visual */
#if !defined(byte)
typedef signed char byte;
#else
#pragma message("Byte has been redefined elsewhere. Some problems can happen")
#endif
#endif

namespace org_scilab_modules_xcos_palette {
class Palette {

private:
JavaVM * jvm;

protected:
jmethodID voidloadPaljstringjobjectArray_ID; // cache method id
jclass stringArrayClass;
jmethodID voidloadPaljstringID; // cache method id
jmethodID voidaddCategoryjobjectArray_jbooleanID; // cache method id
jmethodID voidremovejobjectArray_ID; // cache method id
jmethodID voidenablejobjectArray_jbooleanID; // cache method id
jmethodID voidmovejobjectArray_jobjectArray_ID; // cache method id
jmethodID voidgeneratePaletteIconjstringjstringID; // cache method id



jobject instance;
jclass instanceClass; // cache class


/**
* Get the environment matching to the current thread.
*/
virtual JNIEnv * getCurrentEnv();

public:
// Constructor
/**
* Create a wrapping of the object from a JNIEnv.
* It will call the default constructor
* @param JEnv_ the Java Env
*/
Palette(JavaVM * jvm_);

/**
* Create a wrapping of an already existing object from a JNIEnv.
* The object must have already been instantiated
* @param JEnv_ the Java Env
* @param JObj the object
*/
Palette(JavaVM * jvm_, jobject JObj);


/** 
* This is a fake constructor to avoid the constructor
* chaining when dealing with extended giws classes 
*/
#ifdef FAKEGIWSDATATYPE
Palette(fakeGiwsDataType::fakeGiwsDataType /* unused */) {}
#endif

// Destructor
~Palette();

// Generic method
// Synchronization methods
/**
* Enter monitor associated with the object.
* Equivalent of creating a "synchronized(obj)" scope in Java.
*/
void synchronize();

/**
* Exit monitor associated with the object.
* Equivalent of ending a "synchronized(obj)" scope.
*/
void endSynchronize();

// Methods
static void loadPal(JavaVM * jvm_, char * path, char ** category, int categorySize);

static void loadPal(JavaVM * jvm_, char * path);

static void addCategory(JavaVM * jvm_, char ** name, int nameSize, bool visible);

static void remove(JavaVM * jvm_, char ** name, int nameSize);

static void enable(JavaVM * jvm_, char ** name, int nameSize, bool status);

static void move(JavaVM * jvm_, char ** source, int sourceSize, char ** target, int targetSize);

static void generatePaletteIcon(JavaVM * jvm_, char * blockPath, char * iconPath);


                        /**
                        * Get class name to use for static methods
                        * @return class name to use for static methods
                        */
                        
                static const std::string className()
                {
                return "org/scilab/modules/xcos/palette/Palette";
                }
                
};


}
#endif