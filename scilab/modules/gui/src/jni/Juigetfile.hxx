/* Generated by GIWS (version 1.0.1) */
/*

Copyright 2007-2008 INRIA

Author : Sylvestre Ledru & others

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


#ifndef __ORG_SCILAB_MODULES_GUI_FILECHOOSER_JUIGETFILE__
#define __ORG_SCILAB_MODULES_GUI_FILECHOOSER_JUIGETFILE__
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <jni.h>

namespace org_scilab_modules_gui_filechooser {

class Juigetfile {
private:
JavaVM * jvm;
jobject instance;

jclass instanceClass; // cache class
jmethodID voiduigetfileID; // cache method id
jmethodID voiduigetfilejobjectArrayjobjectArrayID; // cache method id
jclass stringArrayClass;
jmethodID voiduigetfilejobjectArrayjobjectArrayjstringID; // cache method id
jmethodID voiduigetfilejobjectArrayjobjectArrayjstringjstringID; // cache method id
jmethodID voiduigetfilejobjectArrayjobjectArrayjstringjstringjbooleanID; // cache method id
jmethodID jstringgetTitleBoxID; // cache method id
jmethodID jobjectArraygetMaskID; // cache method id
jmethodID jobjectArraygetMaskDescriptionID; // cache method id
jmethodID jstringgetInitialDirectoryID; // cache method id
jmethodID jintgetSelectionSizeID; // cache method id
jmethodID jobjectArraygetSelectionID; // cache method id
jmethodID jobjectArraygetSelectionFileNamesID; // cache method id
jmethodID jbooleanisMultipleSelectionID; // cache method id
jmethodID jstringgetSelectionPathNameID; // cache method id
jmethodID jintgetFilterIndexID; // cache method id
jmethodID jstringgetMenuCallbackID; // cache method id
jmethodID voiduigetdirID; // cache method id
jmethodID voiduigetdirjstringID; // cache method id
jmethodID voiduigetdirjstringjstringID; // cache method id


/**
* Get the environment matching to the current thread.
*/
JNIEnv * getCurrentEnv();

public:
// Constructor
/**
* Create a wrapping of the object from a JNIEnv.
* It will call the default constructor
* @param JEnv_ the Java Env
*/
Juigetfile(JavaVM * jvm_);
/**
* Create a wrapping of an already existing object from a JNIEnv.
* The object must have already been instantiated
* @param JEnv_ the Java Env
* @param JObj the object
*/
Juigetfile(JavaVM * jvm_, jobject JObj);

// Destructor
~Juigetfile();

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
static void uigetfile(JavaVM * jvm_);

static void uigetfile(JavaVM * jvm_, char ** mask, int maskSize, char ** description, int descriptionSize);

static void uigetfile(JavaVM * jvm_, char ** mask, int maskSize, char ** description, int descriptionSize, char * initialDirectory);

static void uigetfile(JavaVM * jvm_, char ** mask, int maskSize, char ** description, int descriptionSize, char * initialDirectory, char * boxtTitle);

static void uigetfile(JavaVM * jvm_, char ** mask, int maskSize, char ** description, int descriptionSize, char * initialDirectory, char * boxtTitle, bool multipleSelection);

static char * getTitleBox(JavaVM * jvm_);

static char ** getMask(JavaVM * jvm_);

static char ** getMaskDescription(JavaVM * jvm_);

static char * getInitialDirectory(JavaVM * jvm_);

static int getSelectionSize(JavaVM * jvm_);

static char ** getSelection(JavaVM * jvm_);

static char ** getSelectionFileNames(JavaVM * jvm_);

static bool isMultipleSelection(JavaVM * jvm_);

static char * getSelectionPathName(JavaVM * jvm_);

static int getFilterIndex(JavaVM * jvm_);

static char * getMenuCallback(JavaVM * jvm_);

static void uigetdir(JavaVM * jvm_);

static void uigetdir(JavaVM * jvm_, char * initialDirectory);

static void uigetdir(JavaVM * jvm_, char * initialDirectory, char * title);


                        /**
                        * Get class name to use for static methods
                        * @return class name to use for static methods
                        */
                        
                static const std::string className()
                {
                return "org/scilab/modules/gui/filechooser/Juigetfile";
                }
                
};


}
#endif