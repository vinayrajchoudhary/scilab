#include "XcosDiagram.hxx"
/* Generated by GIWS (version 1.0.3) */
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

namespace org_scilab_modules_xcos {

// Returns the current env

JNIEnv * XcosDiagram::getCurrentEnv() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);
return curEnv;
}
// Destructor

XcosDiagram::~XcosDiagram() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
curEnv->DeleteGlobalRef(this->stringArrayClass);}
// Constructors

XcosDiagram::XcosDiagram(JavaVM * jvm_) {
jmethodID constructObject = NULL ;
jobject localInstance ;
jclass localClass ;
const std::string construct="<init>";
const std::string param="()V";
jvm=jvm_;

JNIEnv * curEnv = getCurrentEnv();

localClass = curEnv->FindClass( this->className().c_str() ) ;
if (localClass == NULL) {
std::cerr << "Could not get the Class " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass) ;

/* localClass is not needed anymore */
curEnv->DeleteLocalRef(localClass);

if (this->instanceClass == NULL) {
std::cerr << "Could not create a Global Ref of " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}


constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
std::cerr << "Could not retrieve the constructor of the class " << this->className() << " with the profile : " << construct << param << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
std::cerr << "Could not instantiate the object " << this->className() << " with the constructor : " << construct << param << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
std::cerr << "Could not create a new global ref of " << this->className() << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
/* localInstance not needed anymore */
curEnv->DeleteLocalRef(localInstance);

                /* Methods ID set to NULL */
voidsetBlockTextValuejintjobjectArrayjintjintID=NULL; 


}

XcosDiagram::XcosDiagram(JavaVM * jvm_, jobject JObj) {
        jvm=jvm_;

        JNIEnv * curEnv = getCurrentEnv();

jclass localClass = curEnv->GetObjectClass(JObj);
        this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass);
        curEnv->DeleteLocalRef(localClass);

        if (this->instanceClass == NULL) {

std::cerr << "Could not create a Global Ref of " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
        }

        this->instance = curEnv->NewGlobalRef(JObj) ;
        if(this->instance == NULL){

std::cerr << "Could not create a new global ref of " << this->className() << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
        }
        /* Methods ID set to NULL */
        voidsetBlockTextValuejintjobjectArrayjintjintID=NULL; 


}

// Generic methods

void XcosDiagram::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
std::cerr << "Fail to enter monitor." << std::endl;
exit(EXIT_FAILURE);

}
}

void XcosDiagram::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {

std::cerr << "Fail to exit monitor." << std::endl;
exit(EXIT_FAILURE);
}
}
// Method(s)

void XcosDiagram::setBlockTextValue (JavaVM * jvm_, int blockID, char ** blockValue, int blockValueSize, int iRows, int iCols){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread((void **) &curEnv, NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidsetBlockTextValuejintjobjectArrayjintjintID = curEnv->GetStaticMethodID(cls, "setBlockTextValue", "(I[Ljava/lang/String;II)V" ) ;
if (voidsetBlockTextValuejintjobjectArrayjintjintID == NULL) {
std::cerr << "Could not access to the method " << "setBlockTextValue" << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
jclass stringArrayClass = curEnv->FindClass("java/lang/String");

// create java array of strings.
jobjectArray blockValue_ = curEnv->NewObjectArray( blockValueSize, stringArrayClass, NULL);
if (blockValue_ == NULL)
{
std::cerr << "Could not allocate Java string array, memory full." << std::endl;
exit(EXIT_FAILURE);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < blockValueSize; i++)
{
jstring TempString = curEnv->NewStringUTF( blockValue[i] );
if (TempString == NULL)
{
std::cerr << "Could not convert C string to Java UTF string, memory full." << std::endl;
exit(EXIT_FAILURE);
}

curEnv->SetObjectArrayElement( blockValue_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
                         curEnv->CallStaticVoidMethod(cls, voidsetBlockTextValuejintjobjectArrayjintjintID ,blockID, blockValue_, iRows, iCols);
curEnv->DeleteLocalRef(stringArrayClass);
curEnv->DeleteLocalRef(blockValue_);

if (curEnv->ExceptionCheck()) {
curEnv->ExceptionDescribe() ;
}

}

}