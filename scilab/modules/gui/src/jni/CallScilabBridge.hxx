/* Generated by GIWS (version 2.0.0) with command:
giws -e -r -f CallScilabBridge.giws.xml 
*/
/*

Copyright 2007-2008 INRIA
Copyright 2008-2011 DIGITEO
Copyright 2011-2012 Scilab Enterprises

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


#ifndef __ORG_SCILAB_MODULES_GUI_BRIDGE_CALLSCILABBRIDGE__
#define __ORG_SCILAB_MODULES_GUI_BRIDGE_CALLSCILABBRIDGE__
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <jni.h>

#include "GiwsException.hxx"

        #if !defined(byte) | !defined(_MSC_VER) /* Defined anyway with Visual */
                typedef signed char byte;
        #else
                #pragma message("Byte has been redefined elsewhere. Some problems can happen")
        #endif


#ifndef GIWSEXPORT
# if defined(_MSC_VER) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define GIWSEXPORT
#   else
#     define GIWSEXPORT __declspec(dllexport)
#   endif
# else
#   if __GNUC__ >= 4
#     define GIWSEXPORT __attribute__ ((visibility ("default")))
#   else
#     define GIWSEXPORT
#   endif
# endif
#endif

namespace org_scilab_modules_gui_bridge {
class GIWSEXPORT CallScilabBridge {

private:
JavaVM * jvm;

protected:
jmethodID jintnewWindowID; // cache method id
jmethodID jintnewMenuBarID; // cache method id
jmethodID jintnewMenuID; // cache method id
jmethodID jintnewPushButtonID; // cache method id
jmethodID jintnewPushButtonjstringjava_lang_StringID; // cache method id
jmethodID jintnewEditBoxID; // cache method id
jmethodID jintnewLabelID; // cache method id
jmethodID jintnewCheckBoxID; // cache method id
jmethodID jintnewRadioButtonID; // cache method id
jmethodID jintnewSliderID; // cache method id
jmethodID jintnewPopupMenuID; // cache method id
jmethodID jintnewListBoxID; // cache method id
jmethodID jintnewFrameID; // cache method id
jmethodID jintnewUiTableID; // cache method id
jmethodID jintnewUiDisplayTreeID; // cache method id
jmethodID jstringnewContextMenujobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jclass stringArrayClass;
jmethodID jintnewContextMenuID; // cache method id
jmethodID voiddestroyWidgetjintintID; // cache method id
jmethodID voiddestroyFramejintintID; // cache method id
jmethodID jintnewWindowjintintID; // cache method id
jmethodID voidsetFigureAsParentjintintjintintID; // cache method id
jmethodID voidsetMenuAsParentjintintjintintID; // cache method id
jmethodID voidsetRootAsParentjintintID; // cache method id
jmethodID voidsetParentjintintjintintID; // cache method id
jmethodID voidsetPushButtonParentjintintjintintID; // cache method id
jmethodID voidremovePushButtonFromParentjintintjintintID; // cache method id
jmethodID voidsetEditBoxParentjintintjintintID; // cache method id
jmethodID voidremoveEditBoxFromParentjintintjintintID; // cache method id
jmethodID voidsetLabelParentjintintjintintID; // cache method id
jmethodID voidremoveLabelFromParentjintintjintintID; // cache method id
jmethodID voidsetCheckBoxParentjintintjintintID; // cache method id
jmethodID voidremoveCheckBoxFromParentjintintjintintID; // cache method id
jmethodID voidsetRadioButtonParentjintintjintintID; // cache method id
jmethodID voidremoveRadioButtonFromParentjintintjintintID; // cache method id
jmethodID voidsetUiTableParentjintintjintintID; // cache method id
jmethodID voidremoveUiTableFromParentjintintjintintID; // cache method id
jmethodID voidsetUiDisplayTreeParentjintintjintintID; // cache method id
jmethodID voidremoveUiDisplayTreeFromParentjintintjintintID; // cache method id
jmethodID voidsetSliderParentjintintjintintID; // cache method id
jmethodID voidremoveSliderFromParentjintintjintintID; // cache method id
jmethodID voidsetPopupMenuParentjintintjintintID; // cache method id
jmethodID voidremovePopupMenuFromParentjintintjintintID; // cache method id
jmethodID voidsetListBoxParentjintintjintintID; // cache method id
jmethodID voidremoveListBoxFromParentjintintjintintID; // cache method id
jmethodID voidsetFrameParentjintintjintintID; // cache method id
jmethodID voidremoveFrameFromParentjintintjintintID; // cache method id
jmethodID voidsetWidgetTextjintintjstringjava_lang_StringID; // cache method id
jmethodID jstringgetWidgetTextjintintID; // cache method id
jmethodID voidsetFrameTextjintintjstringjava_lang_StringID; // cache method id
jmethodID jstringgetFrameTextjintintID; // cache method id
jmethodID voidsetWidgetBackgroundColorjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getWidgetBackgroundColorjintintID; // cache method id
jmethodID voidsetWidgetForegroundColorjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getWidgetForegroundColorjintintID; // cache method id
jmethodID voidsetFrameBackgroundColorjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getFrameBackgroundColorjintintID; // cache method id
jmethodID voidsetFrameForegroundColorjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getFrameForegroundColorjintintID; // cache method id
jmethodID voidsetWidgetFontNamejintintjstringjava_lang_StringID; // cache method id
jmethodID jstringgetWidgetFontNamejintintID; // cache method id
jmethodID voidsetWidgetFontWeightjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetWidgetFontSizejintintjintintID; // cache method id
jmethodID jintgetWidgetFontSizejintintID; // cache method id
jmethodID voidsetWidgetFontAnglejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetFrameFontNamejintintjstringjava_lang_StringID; // cache method id
jmethodID jstringgetFrameFontNamejintintID; // cache method id
jmethodID voidsetFrameFontWeightjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetFrameFontSizejintintjintintID; // cache method id
jmethodID jintgetFrameFontSizejintintID; // cache method id
jmethodID voidsetFrameFontAnglejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetWidgetPositionjintintjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getWidgetPositionjintintID; // cache method id
jmethodID voidsetFramePositionjintintjintintjintintjintintjintintID; // cache method id
jmethodID jintArray_getFramePositionjintintID; // cache method id
jmethodID voidsetWidgetCallbackjintintjstringjava_lang_StringjintintID; // cache method id
jmethodID voidsetFrameCallbackjintintjstringjava_lang_StringjintintID; // cache method id
jmethodID voidsetWidgetHorizontalAlignmentjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetWidgetVerticalAlignmentjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetSliderMinorTickSpacingjintintjintintID; // cache method id
jmethodID voidsetSliderMajorTickSpacingjintintjintintID; // cache method id
jmethodID voidsetListBoxSelectedIndicesjintintjintArray_intintID; // cache method id
jmethodID jintArray_getListBoxSelectedIndicesjintintID; // cache method id
jmethodID jintgetListBoxSelectionSizejintintID; // cache method id
jmethodID voidsetPopupMenuSelectedIndexjintintjintintID; // cache method id
jmethodID jintgetPopupMenuSelectedIndexjintintID; // cache method id
jmethodID voidsetSliderValuejintintjintintID; // cache method id
jmethodID jintgetSliderValuejintintID; // cache method id
jmethodID voidsetRadioButtonCheckedjintintjbooleanbooleanID; // cache method id
jmethodID jbooleanisRadioButtonCheckedjintintID; // cache method id
jmethodID voidsetCheckBoxCheckedjintintjbooleanbooleanID; // cache method id
jmethodID jbooleanisCheckBoxCheckedjintintID; // cache method id
jmethodID voidsetSliderMinValuejintintjintintID; // cache method id
jmethodID voidsetSliderMaxValuejintintjintintID; // cache method id
jmethodID voidsetSliderVerticaljintintID; // cache method id
jmethodID voidsetSliderHorizontaljintintID; // cache method id
jmethodID voidsetListBoxMultipleSelectionEnabledjintintjbooleanbooleanID; // cache method id
jmethodID jobjectArray_getListBoxAllItemsTextjintintID; // cache method id
jmethodID jintgetListBoxNumberOfItemsjintintID; // cache method id
jmethodID voidsetListBoxTextjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetListBoxListBoxTopjintintjintintID; // cache method id
jmethodID jintgetListBoxListBoxTopjintintID; // cache method id
jmethodID jobjectArray_getPopupMenuAllItemsTextjintintID; // cache method id
jmethodID jintgetPopupMenuNumberOfItemsjintintID; // cache method id
jmethodID voidsetPopupMenuTextjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetWidgetReliefjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetFrameReliefjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetMenuEnabledjstringjava_lang_Stringjstringjava_lang_StringjbooleanbooleanID; // cache method id
jmethodID voidsetSubMenuEnabledjstringjava_lang_Stringjstringjava_lang_StringjintintjbooleanbooleanID; // cache method id
jmethodID voidsetWidgetEnablejintintjbooleanbooleanID; // cache method id
jmethodID voidsetFrameEnablejintintjbooleanbooleanID; // cache method id
jmethodID jbooleanisWidgetEnablejintintID; // cache method id
jmethodID jbooleanisFrameEnablejintintID; // cache method id
jmethodID voidsetMenuCheckedjintintjbooleanbooleanID; // cache method id
jmethodID jbooleanisMenuCheckedjintintID; // cache method id
jmethodID voidremoveMenujstringjava_lang_Stringjstringjava_lang_StringID; // cache method id
jmethodID jstringdisplayAndWaitContextMenujstringjava_lang_StringID; // cache method id
jmethodID jintnewMessageBoxID; // cache method id
jmethodID voidsetMessageBoxTitlejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxMessagejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxMessagejintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidmessageBoxDisplayAndWaitjintintID; // cache method id
jmethodID jintgetMessageBoxSelectedButtonjintintID; // cache method id
jmethodID voidsetMessageBoxDefaultSelectedButtonsjintintjintArray_intintID; // cache method id
jmethodID jintArray_getMessageBoxUserSelectedButtonsjintintID; // cache method id
jmethodID voidsetMessageBoxButtonsLabelsjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxInitialValuejintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID jobjectArray_getMessageBoxValuejintintID; // cache method id
jmethodID jintgetMessageBoxValueSizejintintID; // cache method id
jmethodID voidsetMessageBoxListBoxItemsjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID jintgetMessageBoxSelectedItemjintintID; // cache method id
jmethodID voidsetMessageBoxLineLabelsjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxColumnLabelsjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxDefaultInputjintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetMessageBoxModaljintintjbooleanbooleanID; // cache method id
jmethodID voidsetMessageBoxIconjintintjstringjava_lang_StringID; // cache method id
jmethodID jbooleanisToolbarVisiblejstringjava_lang_StringID; // cache method id
jmethodID voidsetToolbarVisiblejstringjava_lang_StringjbooleanbooleanID; // cache method id
jmethodID voidsetEventHandlerjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetEventHandlerEnabledjintintjbooleanbooleanID; // cache method id
jmethodID jintnewWaitBarID; // cache method id
jmethodID voidsetWaitBarMessagejintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id
jmethodID voidsetWaitBarValuejintintjintintID; // cache method id
jmethodID voiddestroyWaitBarjintintID; // cache method id
jmethodID voidsetWaitBarIndeterminateModejintintjbooleanbooleanID; // cache method id
jmethodID voidlaunchHelpBrowserjobjectArray_java_lang_Stringjava_lang_Stringjstringjava_lang_StringID; // cache method id
jmethodID voidsearchKeywordjobjectArray_java_lang_Stringjava_lang_Stringjstringjava_lang_Stringjstringjava_lang_StringjbooleanbooleanID; // cache method id
jmethodID jintnewExportFileChooserjstringjava_lang_StringID; // cache method id
jmethodID jintnewFontChooserID; // cache method id
jmethodID voidfontChooserDisplayAndWaitjintintID; // cache method id
jmethodID voidsetFontChooserFontNamejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetFontChooserFontSizejintintjintintID; // cache method id
jmethodID voidsetFontChooserBoldjintintjbooleanbooleanID; // cache method id
jmethodID voidsetFontChooserItalicjintintjbooleanbooleanID; // cache method id
jmethodID jstringgetFontChooserFontNamejintintID; // cache method id
jmethodID jintgetFontChooserFontSizejintintID; // cache method id
jmethodID jbooleangetFontChooserBoldjintintID; // cache method id
jmethodID jbooleangetFontChooserItalicjintintID; // cache method id
jmethodID jintnewColorChooserID; // cache method id
jmethodID voidcolorChooserDisplayAndWaitjintintID; // cache method id
jmethodID voidsetColorChooserDefaultColorjintintjintArray_intintID; // cache method id
jmethodID jintArray_getColorChooserSelectedColorjintintID; // cache method id
jmethodID voidsetColorChooserTitlejintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetWidgetVisiblejintintjbooleanbooleanID; // cache method id
jmethodID voidsetFrameVisiblejintintjbooleanbooleanID; // cache method id
jmethodID jbooleanisWidgetVisiblejintintID; // cache method id
jmethodID jbooleanisFrameVisiblejintintID; // cache method id
jmethodID jstringgetClipboardContentsID; // cache method id
jmethodID voidpasteClipboardIntoConsoleID; // cache method id
jmethodID voidcopyConsoleSelectionID; // cache method id
jmethodID voidemptyClipboardID; // cache method id
jmethodID voidsetClipboardContentsjstringjava_lang_StringID; // cache method id
jmethodID voidcopyFigureToClipBoardjintintID; // cache method id
jmethodID jintgetScreenResolutionID; // cache method id
jmethodID jdoublegetScreenWidthID; // cache method id
jmethodID jdoublegetScreenHeightID; // cache method id
jmethodID jintgetScreenDepthID; // cache method id
jmethodID jbooleanprintFigurejstringjava_lang_StringjbooleanbooleanjbooleanbooleanID; // cache method id
jmethodID jbooleanprintFilejstringjava_lang_StringID; // cache method id
jmethodID jbooleanprintStringjstringjava_lang_Stringjstringjava_lang_StringID; // cache method id
jmethodID jbooleanpageSetupID; // cache method id
jmethodID voidrequestFocusjstringjava_lang_StringID; // cache method id
jmethodID voidraiseWindowjintintID; // cache method id
jmethodID voiduseCanvasForDisplayjbooleanbooleanID; // cache method id
jmethodID jbooleanuseCanvasForDisplayID; // cache method id
jmethodID voidscilabAboutBoxID; // cache method id
jmethodID voidsetUiTableColnamesjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetUiTableRownamesjintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetUiTableDatajintintjstringjava_lang_StringID; // cache method id
jmethodID voidsetUiTreeDatajintintjobjectArray_java_lang_Stringjava_lang_StringID; // cache method id



jobject instance;
jclass instanceClass; // cache class

                       
// Caching (if any)


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
CallScilabBridge(JavaVM * jvm_);

/**
* Create a wrapping of an already existing object from a JNIEnv.
* The object must have already been instantiated
* @param JEnv_ the Java Env
* @param JObj the object
*/
CallScilabBridge(JavaVM * jvm_, jobject JObj);


/** 
* This is a fake constructor to avoid the constructor
* chaining when dealing with extended giws classes 
*/
#ifdef FAKEGIWSDATATYPE
CallScilabBridge(fakeGiwsDataType::fakeGiwsDataType /* unused */) {}
#endif

// Destructor
~CallScilabBridge();

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
static int newWindow(JavaVM * jvm_);

static int newMenuBar(JavaVM * jvm_);

static int newMenu(JavaVM * jvm_);

static int newPushButton(JavaVM * jvm_);

static int newPushButton(JavaVM * jvm_, char const* UID);

static int newEditBox(JavaVM * jvm_);

static int newLabel(JavaVM * jvm_);

static int newCheckBox(JavaVM * jvm_);

static int newRadioButton(JavaVM * jvm_);

static int newSlider(JavaVM * jvm_);

static int newPopupMenu(JavaVM * jvm_);

static int newListBox(JavaVM * jvm_);

static int newFrame(JavaVM * jvm_);

static int newUiTable(JavaVM * jvm_);

static int newUiDisplayTree(JavaVM * jvm_);

static char* newContextMenu(JavaVM * jvm_, char const* const* menuLabels, int menuLabelsSize);

static int newContextMenu(JavaVM * jvm_);

static void destroyWidget(JavaVM * jvm_, int objID);

static void destroyFrame(JavaVM * jvm_, int objID);

static int newWindow(JavaVM * jvm_, int figureIndex);

static void setFigureAsParent(JavaVM * jvm_, int figureID, int objID);

static void setMenuAsParent(JavaVM * jvm_, int menuID, int objID);

static void setRootAsParent(JavaVM * jvm_, int objID);

static void setParent(JavaVM * jvm_, int parentID, int objID);

static void setPushButtonParent(JavaVM * jvm_, int parentID, int objID);

static void removePushButtonFromParent(JavaVM * jvm_, int parentID, int objID);

static void setEditBoxParent(JavaVM * jvm_, int parentID, int objID);

static void removeEditBoxFromParent(JavaVM * jvm_, int parentID, int objID);

static void setLabelParent(JavaVM * jvm_, int parentID, int objID);

static void removeLabelFromParent(JavaVM * jvm_, int parentID, int objID);

static void setCheckBoxParent(JavaVM * jvm_, int parentID, int objID);

static void removeCheckBoxFromParent(JavaVM * jvm_, int parentID, int objID);

static void setRadioButtonParent(JavaVM * jvm_, int parentID, int objID);

static void removeRadioButtonFromParent(JavaVM * jvm_, int parentID, int objID);

static void setUiTableParent(JavaVM * jvm_, int parentID, int objID);

static void removeUiTableFromParent(JavaVM * jvm_, int parentID, int objID);

static void setUiDisplayTreeParent(JavaVM * jvm_, int parentID, int objID);

static void removeUiDisplayTreeFromParent(JavaVM * jvm_, int parentID, int objID);

static void setSliderParent(JavaVM * jvm_, int parentID, int objID);

static void removeSliderFromParent(JavaVM * jvm_, int parentID, int objID);

static void setPopupMenuParent(JavaVM * jvm_, int parentID, int objID);

static void removePopupMenuFromParent(JavaVM * jvm_, int parentID, int objID);

static void setListBoxParent(JavaVM * jvm_, int parentID, int objID);

static void removeListBoxFromParent(JavaVM * jvm_, int parentID, int objID);

static void setFrameParent(JavaVM * jvm_, int parentID, int objID);

static void removeFrameFromParent(JavaVM * jvm_, int parentID, int objID);

static void setWidgetText(JavaVM * jvm_, int objID, char const* text);

static char* getWidgetText(JavaVM * jvm_, int objID);

static void setFrameText(JavaVM * jvm_, int objID, char const* text);

static char* getFrameText(JavaVM * jvm_, int objID);

static void setWidgetBackgroundColor(JavaVM * jvm_, int objID, int red, int green, int blue);

static int* getWidgetBackgroundColor(JavaVM * jvm_, int objID);

static void setWidgetForegroundColor(JavaVM * jvm_, int objID, int red, int green, int blue);

static int* getWidgetForegroundColor(JavaVM * jvm_, int objID);

static void setFrameBackgroundColor(JavaVM * jvm_, int objID, int red, int green, int blue);

static int* getFrameBackgroundColor(JavaVM * jvm_, int objID);

static void setFrameForegroundColor(JavaVM * jvm_, int objID, int red, int green, int blue);

static int* getFrameForegroundColor(JavaVM * jvm_, int objID);

static void setWidgetFontName(JavaVM * jvm_, int objID, char const* name);

static char* getWidgetFontName(JavaVM * jvm_, int objID);

static void setWidgetFontWeight(JavaVM * jvm_, int objID, char const* weight);

static void setWidgetFontSize(JavaVM * jvm_, int objID, int size);

static int getWidgetFontSize(JavaVM * jvm_, int objID);

static void setWidgetFontAngle(JavaVM * jvm_, int objID, char const* angle);

static void setFrameFontName(JavaVM * jvm_, int objID, char const* name);

static char* getFrameFontName(JavaVM * jvm_, int objID);

static void setFrameFontWeight(JavaVM * jvm_, int objID, char const* weight);

static void setFrameFontSize(JavaVM * jvm_, int objID, int size);

static int getFrameFontSize(JavaVM * jvm_, int objID);

static void setFrameFontAngle(JavaVM * jvm_, int objID, char const* angle);

static void setWidgetPosition(JavaVM * jvm_, int objID, int x, int y, int width, int height);

static int* getWidgetPosition(JavaVM * jvm_, int objID);

static void setFramePosition(JavaVM * jvm_, int objID, int x, int y, int width, int height);

static int* getFramePosition(JavaVM * jvm_, int objID);

static void setWidgetCallback(JavaVM * jvm_, int objID, char const* text, int type);

static void setFrameCallback(JavaVM * jvm_, int objID, char const* text, int type);

static void setWidgetHorizontalAlignment(JavaVM * jvm_, int objID, char const* alignment);

static void setWidgetVerticalAlignment(JavaVM * jvm_, int objID, char const* alignment);

static void setSliderMinorTickSpacing(JavaVM * jvm_, int objID, int space);

static void setSliderMajorTickSpacing(JavaVM * jvm_, int objID, int space);

static void setListBoxSelectedIndices(JavaVM * jvm_, int objID, int const* indices, int indicesSize);

static int* getListBoxSelectedIndices(JavaVM * jvm_, int objID);

static int getListBoxSelectionSize(JavaVM * jvm_, int objID);

static void setPopupMenuSelectedIndex(JavaVM * jvm_, int objID, int index);

static int getPopupMenuSelectedIndex(JavaVM * jvm_, int objID);

static void setSliderValue(JavaVM * jvm_, int objID, int index);

static int getSliderValue(JavaVM * jvm_, int objID);

static void setRadioButtonChecked(JavaVM * jvm_, int objID, bool status);

static bool isRadioButtonChecked(JavaVM * jvm_, int objID);

static void setCheckBoxChecked(JavaVM * jvm_, int objID, bool status);

static bool isCheckBoxChecked(JavaVM * jvm_, int objID);

static void setSliderMinValue(JavaVM * jvm_, int objID, int value);

static void setSliderMaxValue(JavaVM * jvm_, int objID, int value);

static void setSliderVertical(JavaVM * jvm_, int objID);

static void setSliderHorizontal(JavaVM * jvm_, int objID);

static void setListBoxMultipleSelectionEnabled(JavaVM * jvm_, int objID, bool status);

static char** getListBoxAllItemsText(JavaVM * jvm_, int objID);

static int getListBoxNumberOfItems(JavaVM * jvm_, int objID);

static void setListBoxText(JavaVM * jvm_, int objID, char const* const* text, int textSize);

static void setListBoxListBoxTop(JavaVM * jvm_, int objID, int index);

static int getListBoxListBoxTop(JavaVM * jvm_, int objID);

static char** getPopupMenuAllItemsText(JavaVM * jvm_, int objID);

static int getPopupMenuNumberOfItems(JavaVM * jvm_, int objID);

static void setPopupMenuText(JavaVM * jvm_, int objID, char const* const* text, int textSize);

static void setWidgetRelief(JavaVM * jvm_, int objID, char const* reliefType);

static void setFrameRelief(JavaVM * jvm_, int objID, char const* reliefType);

static void setMenuEnabled(JavaVM * jvm_, char const* parentUID, char const* menuName, bool status);

static void setSubMenuEnabled(JavaVM * jvm_, char const* parentUID, char const* menuName, int position, bool status);

static void setWidgetEnable(JavaVM * jvm_, int objID, bool status);

static void setFrameEnable(JavaVM * jvm_, int objID, bool status);

static bool isWidgetEnable(JavaVM * jvm_, int objID);

static bool isFrameEnable(JavaVM * jvm_, int objID);

static void setMenuChecked(JavaVM * jvm_, int objID, bool status);

static bool isMenuChecked(JavaVM * jvm_, int objID);

static void removeMenu(JavaVM * jvm_, char const* parentUID, char const* menuName);

static char* displayAndWaitContextMenu(JavaVM * jvm_, char const* UID);

static int newMessageBox(JavaVM * jvm_);

static void setMessageBoxTitle(JavaVM * jvm_, int id, char const* title);

static void setMessageBoxMessage(JavaVM * jvm_, int id, char const* message);

static void setMessageBoxMessage(JavaVM * jvm_, int id, char const* const* message, int messageSize);

static void messageBoxDisplayAndWait(JavaVM * jvm_, int id);

static int getMessageBoxSelectedButton(JavaVM * jvm_, int id);

static void setMessageBoxDefaultSelectedButtons(JavaVM * jvm_, int id, int const* index, int indexSize);

static int* getMessageBoxUserSelectedButtons(JavaVM * jvm_, int id);

static void setMessageBoxButtonsLabels(JavaVM * jvm_, int id, char const* const* labels, int labelsSize);

static void setMessageBoxInitialValue(JavaVM * jvm_, int id, char const* const* value, int valueSize);

static char** getMessageBoxValue(JavaVM * jvm_, int id);

static int getMessageBoxValueSize(JavaVM * jvm_, int id);

static void setMessageBoxListBoxItems(JavaVM * jvm_, int id, char const* const* items, int itemsSize);

static int getMessageBoxSelectedItem(JavaVM * jvm_, int id);

static void setMessageBoxLineLabels(JavaVM * jvm_, int id, char const* const* labels, int labelsSize);

static void setMessageBoxColumnLabels(JavaVM * jvm_, int id, char const* const* labels, int labelsSize);

static void setMessageBoxDefaultInput(JavaVM * jvm_, int id, char const* const* values, int valuesSize);

static void setMessageBoxModal(JavaVM * jvm_, int id, bool status);

static void setMessageBoxIcon(JavaVM * jvm_, int id, char const* name);

static bool isToolbarVisible(JavaVM * jvm_, char const* parentUID);

static void setToolbarVisible(JavaVM * jvm_, char const* parentUID, bool status);

static void setEventHandler(JavaVM * jvm_, int figNum, char const* command);

static void setEventHandlerEnabled(JavaVM * jvm_, int figNum, bool status);

static int newWaitBar(JavaVM * jvm_);

static void setWaitBarMessage(JavaVM * jvm_, int id, char const* const* message, int messageSize);

static void setWaitBarValue(JavaVM * jvm_, int id, int value);

static void destroyWaitBar(JavaVM * jvm_, int objID);

static void setWaitBarIndeterminateMode(JavaVM * jvm_, int objID, bool status);

static void launchHelpBrowser(JavaVM * jvm_, char const* const* helps, int helpsSize, char const* language);

static void searchKeyword(JavaVM * jvm_, char const* const* helps, int helpsSize, char const* keyword, char const* language, bool fullText);

static int newExportFileChooser(JavaVM * jvm_, char const* figureUID);

static int newFontChooser(JavaVM * jvm_);

static void fontChooserDisplayAndWait(JavaVM * jvm_, int objID);

static void setFontChooserFontName(JavaVM * jvm_, int objID, char const* fontName);

static void setFontChooserFontSize(JavaVM * jvm_, int objID, int fontSize);

static void setFontChooserBold(JavaVM * jvm_, int objID, bool bold);

static void setFontChooserItalic(JavaVM * jvm_, int objID, bool italic);

static char* getFontChooserFontName(JavaVM * jvm_, int objID);

static int getFontChooserFontSize(JavaVM * jvm_, int objID);

static bool getFontChooserBold(JavaVM * jvm_, int objID);

static bool getFontChooserItalic(JavaVM * jvm_, int objID);

static int newColorChooser(JavaVM * jvm_);

static void colorChooserDisplayAndWait(JavaVM * jvm_, int objID);

static void setColorChooserDefaultColor(JavaVM * jvm_, int objID, int const* rgb, int rgbSize);

static int* getColorChooserSelectedColor(JavaVM * jvm_, int objID);

static void setColorChooserTitle(JavaVM * jvm_, int objID, char const* title);

static void setWidgetVisible(JavaVM * jvm_, int objID, bool status);

static void setFrameVisible(JavaVM * jvm_, int objID, bool status);

static bool isWidgetVisible(JavaVM * jvm_, int objID);

static bool isFrameVisible(JavaVM * jvm_, int objID);

static char* getClipboardContents(JavaVM * jvm_);

static void pasteClipboardIntoConsole(JavaVM * jvm_);

static void copyConsoleSelection(JavaVM * jvm_);

static void emptyClipboard(JavaVM * jvm_);

static void setClipboardContents(JavaVM * jvm_, char const* text);

static void copyFigureToClipBoard(JavaVM * jvm_, int figID);

static int getScreenResolution(JavaVM * jvm_);

static double getScreenWidth(JavaVM * jvm_);

static double getScreenHeight(JavaVM * jvm_);

static int getScreenDepth(JavaVM * jvm_);

static bool printFigure(JavaVM * jvm_, char const* figID, bool postScript, bool displayDialog);

static bool printFile(JavaVM * jvm_, char const* fileName);

static bool printString(JavaVM * jvm_, char const* theString, char const* pageHeader);

static bool pageSetup(JavaVM * jvm_);

static void requestFocus(JavaVM * jvm_, char const* objUID);

static void raiseWindow(JavaVM * jvm_, int objID);

static void useCanvasForDisplay(JavaVM * jvm_, bool onOrOff);

static bool useCanvasForDisplay(JavaVM * jvm_);

static void scilabAboutBox(JavaVM * jvm_);

static void setUiTableColnames(JavaVM * jvm_, int objID, char const* text);

static void setUiTableRownames(JavaVM * jvm_, int objID, char const* text);

static void setUiTableData(JavaVM * jvm_, int objID, char const* text);

static void setUiTreeData(JavaVM * jvm_, int objID, char const* const* text, int textSize);


                        /**
                        * Get class name to use for static methods
                        * @return class name to use for static methods
                        */
                        
                static const std::string className()
                {
                return "org/scilab/modules/gui/bridge/CallScilabBridge";
                }
                
};


}
#endif
