// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Vincent COUVERT <vincent.couvert@scilab.org>
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

function atomsGui()

if ~ exists("atomsinternalslib") then
  load("SCI/modules/atoms/macros/atoms_internals/lib");
end

// Test connection
allModules = atomsGetTOOLBOXES();
if size(allModules, "*") == 0 then
  messagebox(gettext("No Atoms module available. Check your Internet connection."), gettext("Atoms error"), "error");
  return
end

// Defaults
margin           = 10;
figwidth         = 800;
figheight        = 500;
buttonHeight     = 20;
widgetHeight     = 20;
defaultFont      = "Arial";
defaultFontSize  = 12;

// Close the window if it already exists
oldFig = findobj("tag", "atomsFigure");
if ~isempty(oldFig) then
  delete(oldFig);
end

atomsfig = figure("figure_name", gettext("Atoms"), ..
    "position", [0 0 figwidth figheight],..
    "background", -2,..
    "UserData", allModules, ..
    "tag", "atomsFigure");

// Remove Scilab graphics menus & toolbar
delmenu(atomsfig.figure_id, gettext("&File"));
delmenu(atomsfig.figure_id, gettext("&Tools"));
delmenu(atomsfig.figure_id, gettext("&Edit"));
delmenu(atomsfig.figure_id, gettext("&?"));
toolbar(atomsfig.figure_id, "off");

h = uimenu("parent", atomsfig, "label", gettext("File"));
uimenu("parent", h, "label", gettext("Close"), "callback", "cbAtomsGui", "tag", "closeAtomsMenu");

h = uimenu("parent", atomsfig, "label", gettext("?"));
uimenu("parent", h, "label", gettext("Atoms Help..."), "callback", "cbAtomsGui", "tag", "helpAtomsMenu");

atomsfig.axes_size = [figwidth figheight];

// Get modules titles to be displayed
modulesNames = getfield(1, allModules);
modulesNames(1:2) = [];

modulesTitles = [];
for k=1:size(modulesNames, "*")
  vers = getfield(1, allModules(modulesNames(k)));
  vers = vers(3);
  modulesTitles = [modulesTitles; allModules(modulesNames(k))(vers).Title];
end

// List of modules
// =============================================================================

listboxWidth = 200;
listboxFrameWidth = listboxWidth + 2*margin;
modulesListboxFrame = uicontrol("Parent", atomsfig,..
    "Style", "frame",..
    "Position", [margin margin listboxWidth+2*margin figheight-2*margin],..
    "Background", [1 1 1],..
    "Tag", "modulesListboxFrame");
modulesListboxFrameTitle = uicontrol("Parent", atomsfig,..
    "Style", "text",..
    "Position", [2*margin figheight-2*margin 110 widgetHeight],..
    "HorizontalAlignment", "center",..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Available Modules"), ..
    "Background", [1 1 1],..
    "Tag", "modulesListboxFrameTitle")
modulesListbox = uicontrol("Parent", atomsfig,..
    "Style", "listbox",..
    "Position", [2*margin 2*margin listboxWidth figheight-4*margin],..
    "Background", [1 1 1],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", modulesTitles,..
    "Callback", "cbAtomsGui", ..
    "Min", 1, ..
    "Max", 1, ..
    "Tag", "modulesListbox")

// Description
// =============================================================================

descWidth = figwidth - 7*margin - listboxWidth 
descFrameWidth = descWidth + 2*margin; 
modulesDescFrame = uicontrol("Parent", atomsfig,..
    "Style", "frame",..
    "Background", [1 1 1],..
    "Position", [listboxFrameWidth+2*margin 2*margin+buttonHeight descFrameWidth figheight-3*margin-buttonHeight],..
    "Tag", "modulesDescFrame")
modulesDescFrameTitle = uicontrol("Parent", atomsfig,..
    "Style", "text",..
    "Position", [listboxFrameWidth+3*margin figheight-2*margin 120 widgetHeight],..
    "HorizontalAlignment", "center",..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Module Description"), ..
    "Background", [1 1 1],..
    "Tag", "modulesDescFrameTitle")
modulesDesc = uicontrol("Parent", atomsfig,..
    "VerticalAlignment", "top",..
    "Style", "text",..
    "Position", [listboxFrameWidth+3*margin 3*margin+buttonHeight descWidth figheight-5*margin-buttonHeight],..
    "Background", [1 1 1],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("No module selected"),..
    "Tag", "modulesDesc")

// Buttons
// =============================================================================

buttonWidth = (descFrameWidth - 3*margin) / 4;

// "Remove" Button

removeButton = uicontrol("Parent", atomsfig,..
    "Style", "pushbutton",..
    "Position", [listboxFrameWidth+2*margin margin buttonWidth 20],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Remove"),..
    "Callback", "cbAtomsGui", ..
    "Enable", "off",..
    "Tag", "removeButton")

// "Install" Button

installButton = uicontrol("Parent", atomsfig,..
    "Style", "pushbutton",..
    "Position", [listboxFrameWidth+3*margin+buttonWidth margin buttonWidth widgetHeight],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Install"),..
    "Callback", "cbAtomsGui", ..
    "Enable", "off", ..
    "Tag", "installButton")

// "Update" Button

updateButton = uicontrol("Parent", atomsfig,..
    "Style", "pushbutton",..
    "Position", [listboxFrameWidth+4*margin+2*buttonWidth margin buttonWidth widgetHeight],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Update"),..
    "Callback", "cbAtomsGui", ..
    "Enable", "off", ..
    "Tag", "updateButton")


// "Update" Button

updateButton = uicontrol("Parent", atomsfig,..
    "Style", "pushbutton",..
    "Position", [listboxFrameWidth+5*margin+3*buttonWidth margin buttonWidth widgetHeight],..
    "FontName", defaultFont,..
    "FontSize", defaultFontSize,..
    "String", gettext("Load"),..
    "Callback", "cbAtomsGui", ..
    "Enable", "off", ..
    "Tag", "loadButton")

endfunction