#include "SubwinBackgroundDrawerGL.hxx"
/* Generated by GIWS (version 0.9.9.4) */
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

namespace org_scilab_modules_renderer_subwinDrawing {

// Returns the current env

JNIEnv * SubwinBackgroundDrawerGL::getCurrentEnv() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);
return curEnv;
}
// Destructor

SubwinBackgroundDrawerGL::~SubwinBackgroundDrawerGL() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread((void **) &curEnv, NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
}
// Constructors

SubwinBackgroundDrawerGL::SubwinBackgroundDrawerGL(JavaVM * jvm_) {
jmethodID constructObject = NULL ;
jobject localInstance ;
jclass localClass ;
const std::string construct="<init>";
const std::string param="()V";
jvm=jvm_;

JNIEnv * curEnv = getCurrentEnv();

localClass = curEnv->FindClass( this->className().c_str() ) ;
if (localClass == NULL) {
  throw GiwsException::JniClassNotFoundException(curEnv, this->className());
}

this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass) ;

/* localClass is not needed anymore */
curEnv->DeleteLocalRef(localClass);

if (this->instanceClass == NULL) {
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}


constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}
/* localInstance not needed anymore */
curEnv->DeleteLocalRef(localInstance);

                /* Methods ID set to NULL */
voiddisplayID=NULL; 
voidinitializeDrawingjintID=NULL; 
voidendDrawingID=NULL; 
voidshowjintID=NULL; 
voiddestroyjintID=NULL; 
voidsetFigureIndexjintID=NULL; 
voidsetBoxParametersjintID=NULL; 
voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID=NULL; 


}

SubwinBackgroundDrawerGL::SubwinBackgroundDrawerGL(JavaVM * jvm_, jobject JObj) {
        jvm=jvm_;

        JNIEnv * curEnv = getCurrentEnv();

jclass localClass = curEnv->GetObjectClass(JObj);
        this->instanceClass = (jclass) curEnv->NewGlobalRef(localClass);
        curEnv->DeleteLocalRef(localClass);

        if (this->instanceClass == NULL) {
throw GiwsException::JniObjectCreationException(curEnv, this->className());
        }

        this->instance = curEnv->NewGlobalRef(JObj) ;
        if(this->instance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
        }
        /* Methods ID set to NULL */
        voiddisplayID=NULL; 
voidinitializeDrawingjintID=NULL; 
voidendDrawingID=NULL; 
voidshowjintID=NULL; 
voiddestroyjintID=NULL; 
voidsetFigureIndexjintID=NULL; 
voidsetBoxParametersjintID=NULL; 
voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID=NULL; 


}

// Generic methods


void SubwinBackgroundDrawerGL::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
std::cerr << "Fail to enter monitor." << std::endl;
exit(EXIT_FAILURE);
}
}


void SubwinBackgroundDrawerGL::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
std::cerr << "Fail to exit monitor." << std::endl;
exit(EXIT_FAILURE);
}
}

// Method(s)

void SubwinBackgroundDrawerGL::display (){

JNIEnv * curEnv = getCurrentEnv();

if (voiddisplayID==NULL) { /* Use the cache Luke */ voiddisplayID = curEnv->GetMethodID(this->instanceClass, "display", "()V" ) ;
if (voiddisplayID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "display");
}
}
                         curEnv->CallVoidMethod( this->instance, voiddisplayID );
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::initializeDrawing (int figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (voidinitializeDrawingjintID==NULL) { /* Use the cache Luke */ voidinitializeDrawingjintID = curEnv->GetMethodID(this->instanceClass, "initializeDrawing", "(I)V" ) ;
if (voidinitializeDrawingjintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "initializeDrawing");
}
}
                         curEnv->CallVoidMethod( this->instance, voidinitializeDrawingjintID ,figureIndex);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::endDrawing (){

JNIEnv * curEnv = getCurrentEnv();

if (voidendDrawingID==NULL) { /* Use the cache Luke */ voidendDrawingID = curEnv->GetMethodID(this->instanceClass, "endDrawing", "()V" ) ;
if (voidendDrawingID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "endDrawing");
}
}
                         curEnv->CallVoidMethod( this->instance, voidendDrawingID );
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::show (int figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (voidshowjintID==NULL) { /* Use the cache Luke */ voidshowjintID = curEnv->GetMethodID(this->instanceClass, "show", "(I)V" ) ;
if (voidshowjintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "show");
}
}
                         curEnv->CallVoidMethod( this->instance, voidshowjintID ,figureIndex);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::destroy (int figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (voiddestroyjintID==NULL) { /* Use the cache Luke */ voiddestroyjintID = curEnv->GetMethodID(this->instanceClass, "destroy", "(I)V" ) ;
if (voiddestroyjintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "destroy");
}
}
                         curEnv->CallVoidMethod( this->instance, voiddestroyjintID ,figureIndex);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::setFigureIndex (int figureIndex){

JNIEnv * curEnv = getCurrentEnv();

if (voidsetFigureIndexjintID==NULL) { /* Use the cache Luke */ voidsetFigureIndexjintID = curEnv->GetMethodID(this->instanceClass, "setFigureIndex", "(I)V" ) ;
if (voidsetFigureIndexjintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "setFigureIndex");
}
}
                         curEnv->CallVoidMethod( this->instance, voidsetFigureIndexjintID ,figureIndex);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::setBoxParameters (int backgroundColor){

JNIEnv * curEnv = getCurrentEnv();

if (voidsetBoxParametersjintID==NULL) { /* Use the cache Luke */ voidsetBoxParametersjintID = curEnv->GetMethodID(this->instanceClass, "setBoxParameters", "(I)V" ) ;
if (voidsetBoxParametersjintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "setBoxParameters");
}
}
                         curEnv->CallVoidMethod( this->instance, voidsetBoxParametersjintID ,backgroundColor);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SubwinBackgroundDrawerGL::drawBox (double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, int concealedCornerIndex){

JNIEnv * curEnv = getCurrentEnv();

if (voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID==NULL) { /* Use the cache Luke */ voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID = curEnv->GetMethodID(this->instanceClass, "drawBox", "(DDDDDDI)V" ) ;
if (voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "drawBox");
}
}
                         curEnv->CallVoidMethod( this->instance, voiddrawBoxjdoublejdoublejdoublejdoublejdoublejdoublejintID ,xMin, xMax, yMin, yMax, zMin, zMax, concealedCornerIndex);
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

}