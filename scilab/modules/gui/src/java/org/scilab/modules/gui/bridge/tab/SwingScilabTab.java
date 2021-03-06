/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007-2008 - INRIA - Vincent Couvert
 * Copyright (C) 2007 - INRIA - Bruno JOFRET
 * Copyright (C) 2007 - INRIA - Marouane BEN JELLOUL
 * Copyright (C) 2011 - DIGITEO - Vincent Couvert
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.gui.bridge.tab;

import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_AXES_SIZE__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_CALLBACK__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_CHILDREN__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_ID__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_NAME__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_POSITION__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_SIZE__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_TYPE__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_UICHECKEDMENU__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_UICHILDMENU__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_UIMENU__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_UIPARENTMENU__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_INFO_MESSAGE__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_EVENTHANDLER_NAME__;
import static org.scilab.modules.graphic_objects.graphicObject.GraphicObjectProperties.__GO_EVENTHANDLER_ENABLE__;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.HierarchyBoundsListener;
import java.awt.event.HierarchyEvent;
import java.awt.event.MouseListener;
import java.lang.reflect.InvocationTargetException;
import java.util.Iterator;

import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.SwingUtilities;

import org.flexdock.docking.DockingConstants;
import org.flexdock.docking.DockingPort;
import org.flexdock.docking.activation.ActiveDockableTracker;
import org.flexdock.docking.event.DockingEvent;
import org.flexdock.docking.props.PropertyChangeListenerFactory;
import org.flexdock.view.Titlebar;
import org.flexdock.view.View;
import org.scilab.modules.graphic_objects.figure.Figure;
import org.scilab.modules.graphic_objects.graphicController.GraphicController;
import org.scilab.modules.gui.SwingView;
import org.scilab.modules.gui.SwingViewObject;
import org.scilab.modules.gui.bridge.canvas.SwingScilabCanvas;
import org.scilab.modules.gui.bridge.canvas.SwingScilabCanvasImpl;
import org.scilab.modules.gui.bridge.checkbox.SwingScilabCheckBox;
import org.scilab.modules.gui.bridge.console.SwingScilabConsole;
import org.scilab.modules.gui.bridge.editbox.SwingScilabEditBox;
import org.scilab.modules.gui.bridge.frame.SwingScilabFrame;
import org.scilab.modules.gui.bridge.helpbrowser.SwingScilabHelpBrowser;
import org.scilab.modules.gui.bridge.label.SwingScilabLabel;
import org.scilab.modules.gui.bridge.listbox.SwingScilabListBox;
import org.scilab.modules.gui.bridge.popupmenu.SwingScilabPopupMenu;
import org.scilab.modules.gui.bridge.pushbutton.SwingScilabPushButton;
import org.scilab.modules.gui.bridge.radiobutton.SwingScilabRadioButton;
import org.scilab.modules.gui.bridge.slider.SwingScilabSlider;
import org.scilab.modules.gui.bridge.tree.SwingScilabTree;
import org.scilab.modules.gui.bridge.uidisplaytree.SwingScilabUiDisplayTree;
import org.scilab.modules.gui.bridge.uiimage.SwingScilabUiImage;
import org.scilab.modules.gui.bridge.uitable.SwingScilabUiTable;
import org.scilab.modules.gui.bridge.window.SwingScilabWindow;
import org.scilab.modules.gui.canvas.Canvas;
import org.scilab.modules.gui.checkbox.CheckBox;
import org.scilab.modules.gui.console.Console;
import org.scilab.modules.gui.dockable.Dockable;
import org.scilab.modules.gui.editbox.EditBox;
import org.scilab.modules.gui.events.callback.CommonCallBack;
import org.scilab.modules.gui.events.callback.ScilabCloseCallBack;
import org.scilab.modules.gui.events.ScilabEventListener;
import org.scilab.modules.gui.frame.Frame;
import org.scilab.modules.gui.helpbrowser.HelpBrowser;
import org.scilab.modules.gui.label.Label;
import org.scilab.modules.gui.listbox.ListBox;
import org.scilab.modules.gui.menubar.MenuBar;
import org.scilab.modules.gui.popupmenu.PopupMenu;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.radiobutton.RadioButton;
import org.scilab.modules.gui.slider.Slider;
import org.scilab.modules.gui.tab.SimpleTab;
import org.scilab.modules.gui.textbox.TextBox;
import org.scilab.modules.gui.toolbar.ToolBar;
import org.scilab.modules.gui.tree.Tree;
import org.scilab.modules.gui.uidisplaytree.UiDisplayTree;
import org.scilab.modules.gui.uitable.UiTable;
import org.scilab.modules.gui.utils.BarUpdater;
import org.scilab.modules.gui.utils.Position;
import org.scilab.modules.gui.utils.SciClosingAction;
import org.scilab.modules.gui.utils.SciHelpOnComponentAction;
import org.scilab.modules.gui.utils.SciUndockingAction;
import org.scilab.modules.gui.utils.ScilabSwingUtilities;
import org.scilab.modules.gui.utils.Size;
import org.scilab.modules.gui.utils.ToolBarBuilder;

/**
 * Swing implementation for Scilab tabs in GUIs
 * This implementation uses FlexDock package
 * @author Bruno JOFRET
 * @author Vincent COUVERT
 * @author Marouane BEN JELLOUL
 * @author Jean-Baptiste SILVY
 */
public class SwingScilabTab extends View implements SwingViewObject, SimpleTab, FocusListener {

    /** Use to put a component above any other object within its layer */
    private static final int TOP_POSITION = 0;
    /** Use to put a component below any other object within its layer */
    private static final int BOTTOM_POSITION = -1;

    private static final Image SCILAB_ICON = new ImageIcon(ScilabSwingUtilities.findIcon("scilab", "256x256")).getImage();

    private static final long serialVersionUID = 1L;

    private static final int VIEWPORT_SIZE = 4;

    private static final String UNDOCK = "undock";
    private static final String HELP = "help";

    public static final String GRAPHICS_TOOLBAR_DESCRIPTOR = System.getenv("SCI") + "/modules/gui/etc/graphics_toolbar.xml";

    private String id;

    static {
        PropertyChangeListenerFactory.addFactory(new BarUpdater.UpdateBarFactory());
    }

    private String parentWindowId;
    private MenuBar menuBar;
    private ToolBar toolBar;
    private TextBox infoBar;
    private String helpID;

    /** Contains the canvas and widgets */
    private SwingScilabAxes contentPane;

    /** Scroll the axes */
    private ScilabScrollPane scrolling;

    private Image icon;

    private Action closeAction;

    /** The listener for event handling */
    private ScilabEventListener eventHandler;

    /** A reference to the canvas used for event handling management */
    SwingScilabCanvas contentCanvas;

    /**
     * Constructor
     * @param name the name of the tab
     * @param uuid an uuid to identify the tab
     */
    public SwingScilabTab(String name, String uuid) {
        super(uuid, name, name);
        //This button is "overloaded" when we add a callback
        //this.addAction(DockingConstants.CLOSE_ACTION);
        // Removed because make JOGL crash when "Unpin"
        //this.addAction(DockingConstants.PIN_ACTION);
        this.addAction(DockingConstants.ACTIVE_WINDOW);

        // no need for an axes
        contentPane = null;
        scrolling = null;

        this.setVisible(true);

        getTitlebar().addFocusListener(this);
        addFocusListener(this);
        setCallback(null);
    }

    /**
     * Create a graphic tab used to display a figure with 3D graphics and/or UIcontrols
     * @param name name of the tab
     * @param figureId id of the displayed figure
     */
    public SwingScilabTab(String name, int figureId) {
        super(name, name, name);

        // This button is "overloaded" when we add a callback
        //this.addAction(DockingConstants.CLOSE_ACTION);
        // Removed because make JOGL crash when "Unpin"
        //this.addAction(DockingConstants.PIN_ACTION);
        this.addAction(DockingConstants.ACTIVE_WINDOW);

        // create the panel in which all the uiobjects will lie.
        //contentPane = new SwingScilabAxes(figureId);

        // add it inside a JSCrollPane
        //scrolling = new SwingScilabScrollPane(contentPane);
        //scrolling.setBackground(1, 0, 0);
        // put in in the back of the tab
        //setContentPane(scrolling.getAsContainer());

        this.setVisible(true);

        getTitlebar().addFocusListener(this);
        addFocusListener(this);
        setCallback(null);
    }

    /**
     * Constructor
     * @param name the name of the tab (used to identify it)
     */
    public SwingScilabTab(String name) {
        this(name, name);
    }

    /**
     * Set the associated help page
     * @param helpID the xml id of the associated help page
     */
    public void setAssociatedXMLIDForHelp(String helpID) {
        this.helpID = helpID;
    }

    /**
     * Get the associated help page
     * @return the xml id of the associated help page
     */
    public String getAssociatedXMLIDForHelp() {
        return helpID;
    }

    public static void removeActions(SwingScilabTab tab) {
        tab.setActionBlocked(DockingConstants.CLOSE_ACTION, true);
        tab.setActionBlocked(UNDOCK, true);
        tab.getTitlebar().revalidate();
    }

    public static void addActions(SwingScilabTab tab) {
        tab.setActionBlocked(DockingConstants.CLOSE_ACTION, false);
        tab.setActionBlocked(UNDOCK, false);
        tab.getTitlebar().revalidate();
    }

    public SwingScilabTab(String figureTitle, int figureId, Figure figure) {
        this(figureTitle, figureId);
        /* OpenGL context */
        SwingScilabCanvas canvas = new SwingScilabCanvas(figureId, figure);
        contentCanvas = canvas;
        setContentPane(canvas);
        canvas.setVisible(true);

        /* Manage figure_position property */
        addHierarchyBoundsListener(new HierarchyBoundsListener() {
            public void ancestorResized(HierarchyEvent arg0) {
            }

            public void ancestorMoved(HierarchyEvent e) {
                if (e.getChanged() instanceof SwingScilabWindow) {
                    Position parentPosition =  SwingScilabWindow.allScilabWindows.get(parentWindowId).getPosition();
                    Integer[] newPosition = new Integer[2];
                    newPosition[0] = parentPosition.getX();
                    newPosition[1] = parentPosition.getY();
                    GraphicController.getController().setProperty(id, __GO_POSITION__, newPosition);
                }
            }
        });

        /* Manage figure_size property */
        addComponentListener(new ComponentListener() {

            public void componentShown(ComponentEvent arg0) {
            }

            public void componentResized(ComponentEvent arg0) {
                /* Update the figure_size property */
                Size parentSize =  SwingScilabWindow.allScilabWindows.get(parentWindowId).getDims();
                Integer[] newSize = new Integer[2];
                newSize[0] = parentSize.getWidth();
                newSize[1] = parentSize.getHeight();
                GraphicController.getController().setProperty(id, __GO_SIZE__, newSize);
                /* Update the axes_size property */
                Dimension contentPaneSize = getContentPane().getSize();
                Integer[] newAxesSize = new Integer[2];
                newAxesSize[0] = contentPaneSize.width;
                newAxesSize[1] = contentPaneSize.height;
                GraphicController.getController().setProperty(id, __GO_AXES_SIZE__, newAxesSize);
            }

            public void componentMoved(ComponentEvent arg0) {
            }

            public void componentHidden(ComponentEvent arg0) {
            }
        });
    }

    /**
     * @param e the FocusEvent
     */
    @Override
    public void focusGained(FocusEvent e) {
        //ActiveDockableTracker.requestDockableActivation(this);
        if (contentPane != null) {
            contentPane.requestFocus();
        } else if (getContentPane() != null) {
            getContentPane().requestFocus();
        } else {
            SwingScilabTab.this.requestFocusInWindow();
        }
    }

    /**
     * Call when the tab restoration is ended.
     */
    public void endedRestoration() { }

    /**
     * @return the window icon associated with this tab
     */
    public Image getWindowIcon() {
        if (icon == null) {
            return SCILAB_ICON;
        } else {
            return icon;
        }
    }

    /**
     * @param icon the window icon associated with this tab
     */
    public void setWindowIcon(Image icon) {
        this.icon = icon;
    }

    /**
     * @param the window icon associated with this tab
     */
    public void setWindowIcon(String iconName) {
        setWindowIcon(new ImageIcon(ScilabSwingUtilities.findIcon(iconName, "256x256")).getImage());
    }

    /**
     * @param e the FocusEvent
     */
    @Override
    public void focusLost(FocusEvent e) { }

    /**
     * {@inheritDoc}
     */
    @Override
    public void dockingComplete(DockingEvent evt) {
        super.dockingComplete(evt);
        DockingPort port = evt.getNewDockingPort();
        Iterator iter = port.getDockables().iterator();

        if (port.getDockables().size() > 1) {
            while (iter.hasNext()) {
                Object d = iter.next();
                if (d instanceof SwingScilabTab) {
                    SwingScilabTab view = (SwingScilabTab) d;
                    addActions(view);
                }
            }
        } else {
            removeActions(this);
        }
    }

    /**
     * Sets the Name of a swing Scilab tab
     * @param newTabName the Name of the tab
     * @see org.scilab.modules.gui.tab.Tab#setName()
     */
    @Override
    public void setName(String newTabName) {
        setTitle(newTabName, true);
        getTitlePane().repaint();
        SwingUtilities.getAncestorOfClass(SwingScilabWindow.class, this).setName(newTabName);
    }

    /**
     * @return the UUID of the parent window
     */
    public String getParentWindowUUID() {
        return ((SwingScilabWindow) SwingUtilities.getAncestorOfClass(SwingScilabWindow.class, this)).getUUID();
    }

    /**
     * Gets the title of a swing Scilab tab
     * @return the title of the tab
     * @see org.scilab.modules.gui.tab.Tab#getTitle()
     */
    @Override
    public String getName() {
        return this.getTitle();
    }

    /**
     * Paint immediately this component
     */
    public void paintImmediately() {
        // paint all
        paintImmediately(0, 0, getWidth(), getHeight());
    }

    /**
     * Draws a swing Scilab tab
     * @see org.scilab.modules.gui.uielement.UIElement#draw()
     */
    @Override
    public void draw() {
        if (SwingUtilities.isEventDispatchThread()) {
            setVisible(true);
            paintImmediately();
        } else {
            try {
                SwingUtilities.invokeAndWait(new Runnable() {
                    @Override
                    public void run() {
                        setVisible(true);
                        paintImmediately();
                    }
                });
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
        }

    }

    /**
     * Gets the dimensions (width and height) of a swing Scilab tab
     * @return the dimensions of the tab
     * @see org.scilab.modules.gui.uielement.UIElement#getDims()
     */
    @Override
    public Size getDims() {
        return new Size(this.getSize().width, this.getSize().height);
    }

    /**
     * Get the size for the axes
     * @return size of the axes in pixels
     */
    @Override
    public Size getAxesSize() {
        return new Size(contentPane.getWidth(), contentPane.getHeight());
    }

    /**
     * @param newSize new size to set for the axes
     */
    @Override
    public void setAxesSize(Size newSize) {
        contentPane.setSize(new Dimension(newSize.getWidth(), newSize.getHeight()));
    }

    /**
     * Gets the position (X-coordinate and Y-coordinate) of a swing Scilab tab
     * @return the position of the tab
     * @see org.scilab.modules.gui.uielement.UIElement#getPosition()
     */
    @Override
    public Position getPosition() {
        return new Position(this.getX(), this.getY());
    }

    /**
     * Sets the dimensions (width and height) of a swing Scilab tab
     * @param newSize the dimensions we want to set to the tab
     * @see org.scilab.modules.gui.uielement.UIElement#setDims(org.scilab.modules.gui.utils.Size)
     */
    @Override
    public void setDims(Size newSize) {
        this.setSize(newSize.getWidth(), newSize.getHeight());
    }

    /**
     * Sets the position (X-coordinate and Y-coordinate) of a swing Scilab tab
     * @param newPosition the position we want to set to the tab
     * @see org.scilab.modules.gui.uielement.UIElement#setPosition(org.scilab.modules.gui.utils.Position)
     */
    @Override
    public void setPosition(Position newPosition) {
        this.setLocation(newPosition.getX(), newPosition.getY());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(Canvas member) {
        int result;

        if (SwingScilabCanvasImpl.isGLCanvasEnabled()) {
            int[] currentView = getViewingRegion();
            final SwingScilabTab thisF = this;
            try {
                SwingUtilities.invokeAndWait(new Runnable() {
                    @Override
                    public void run() {
                        scrolling = new AwtScilabScrollPane(contentPane, thisF);
                        setContentPane(scrolling.getAsContainer());
                        revalidate();

                    }
                });
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.getCause().printStackTrace();
            }
            // set the canvas after doing every thing
            result = contentPane.addMember(member);
            // set the same viewport as before
            setViewingRegion(currentView[0], currentView[1], currentView[2], currentView[2 + 1]);
        } else {
            result = contentPane.addMember(member);
        }
        return result;
    }

    /**
     * We want to be able to remove directly a Canvas from a Tab.
     * @param member canvas to remove
     */
    @Override
    public void removeMember(Canvas member) {
        contentPane.removeMember(member);
        if (SwingScilabCanvasImpl.isGLCanvasEnabled()) {
            try {
                SwingUtilities.invokeAndWait(new Runnable() {
                    @Override
                    public void run() {
                        scrolling = new SwingScilabScrollPane(contentPane);
                        setContentPane(scrolling.getAsContainer());
                        revalidate();
                    }
                });
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.getCause().printStackTrace();
            }
        }
    }

    /**
     * Add a SwingViewObject (from SwingView.java) to container and returns its index
     * @param member the member to add
     */
    public void addMember(SwingViewObject member) {
        if (member instanceof SwingScilabFrame) {
            this.add((Component) member, BOTTOM_POSITION);
        } else {
            this.add((Component) member, TOP_POSITION);
        }
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(Console member) {
        return this.addMember((SwingScilabConsole) member.getAsSimpleConsole());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabConsole member) {
        // replace the current content pane
        this.setContentPane(member);
        return this.getComponentZOrder(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(HelpBrowser member) {
        return this.addMember((SwingScilabHelpBrowser) member.getAsSimpleHelpBrowser());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabHelpBrowser member) {
        // replace the current content pane
        this.setContentPane(member);
        return this.getComponentZOrder(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(Frame member) {
        return this.addMember((SwingScilabFrame) member.getAsSimpleFrame());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabFrame member) {
        return contentPane.addFrame(member);
    }

    /**
     * Remove a Frame from its container
     * @param member the Frame to remove
     */
    @Override
    public void removeMember(Frame member) {
        this.removeMember((SwingScilabFrame) member.getAsSimpleFrame());
    }

    /**
     * Remove a Frame from its container
     * @param member the Frame to remove
     */
    private void removeMember(SwingScilabFrame member) {
        contentPane.removeFrame(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(PushButton member) {
        return this.addMember((SwingScilabPushButton) member.getAsSimplePushButton());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabPushButton member) {
        int res = contentPane.addWidget(member);
        repaint();
        return res;
    }

    /**
     * Remove a PushButton from its container
     * @param member the PushButton to remove
     */
    @Override
    public void removeMember(PushButton member) {
        this.removeMember((SwingScilabPushButton) member.getAsSimplePushButton());
    }

    /**
     * Remove a PushButton from its container
     * @param member the PushButton to remove
     */
    private void removeMember(SwingScilabPushButton member) {
        contentPane.remove(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(EditBox member) {
        return this.addMember((SwingScilabEditBox) member.getAsSimpleEditBox());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabEditBox member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove an EditBox from its container
     * @param member the EditBox to remove
     */
    @Override
    public void removeMember(EditBox member) {
        this.removeMember((SwingScilabEditBox) member.getAsSimpleEditBox());
    }

    /**
     * Remove an EditBox from its container
     * @param member the EditBox to remove
     */
    private void removeMember(SwingScilabEditBox member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(Label member) {
        return this.addMember((SwingScilabLabel) member.getAsSimpleLabel());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabLabel member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a Label from its container
     * @param member the Label to remove
     */
    @Override
    public void removeMember(Label member) {
        this.removeMember((SwingScilabLabel) member.getAsSimpleLabel());
    }

    /**
     * Remove a Label from its container
     * @param member the Label to remove
     */
    private void removeMember(SwingScilabLabel member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(CheckBox member) {
        return this.addMember((SwingScilabCheckBox) member.getAsSimpleCheckBox());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabCheckBox member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a CheckBox from its container
     * @param member the CheckBox to remove
     */
    @Override
    public void removeMember(CheckBox member) {
        this.removeMember((SwingScilabCheckBox) member.getAsSimpleCheckBox());
    }

    /**
     * Remove a CheckBox from its container
     * @param member the CheckBox to remove
     */
    private void removeMember(SwingScilabCheckBox member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(RadioButton member) {
        return this.addMember((SwingScilabRadioButton) member.getAsSimpleRadioButton());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabRadioButton member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a RadioButton from its container
     * @param member the RadioButton to remove
     */
    @Override
    public void removeMember(RadioButton member) {
        this.removeMember((SwingScilabRadioButton) member.getAsSimpleRadioButton());
    }

    /**
     * Remove a RadioButton from its container
     * @param member the RadioButton to remove
     */
    private void removeMember(SwingScilabRadioButton member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabUiImage member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a Image from its container
     * @param member the Image to remove
     */
    private void removeMember(SwingScilabUiImage member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addMember(UiDisplayTree member) {
        return this.addMember((SwingScilabUiDisplayTree) member.getAsSimpleUiDisplayTree());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabUiDisplayTree member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a Tree from its container
     * @param member the Tree to remove
     */
    public void removeMember(UiDisplayTree member) {
        this.removeMember((SwingScilabUiDisplayTree) member.getAsSimpleUiDisplayTree());
    }

    /**
     * Remove a Tree from its container
     * @param member the Tree to remove
     */
    private void removeMember(SwingScilabUiDisplayTree member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addMember(UiTable member) {
        return this.addMember((SwingScilabUiTable) member.getAsSimpleUiTable());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabUiTable member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a UiTable from its container
     * @param member the UiTable to remove
     */
    public void removeMember(UiTable member) {
        this.removeMember((SwingScilabUiTable) member.getAsSimpleUiTable());
    }

    /**
     * Remove a UiTable from its container
     * @param member the UiTable to remove
     */
    private void removeMember(SwingScilabUiTable member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addMember(Slider member) {
        return this.addMember((SwingScilabSlider) member.getAsSimpleSlider());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabSlider member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a Slider from its container
     * @param member the Slider to remove
     */
    @Override
    public void removeMember(Slider member) {
        this.removeMember((SwingScilabSlider) member.getAsSimpleSlider());
    }

    /**
     * Remove a Slider from its container
     * @param member the Slider to remove
     */
    private void removeMember(SwingScilabSlider member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(ListBox member) {
        return this.addMember((SwingScilabListBox) member.getAsSimpleListBox());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabListBox member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a ListBox from its container
     * @param member the ListBox to remove
     */
    @Override
    public void removeMember(ListBox member) {
        this.removeMember((SwingScilabListBox) member.getAsSimpleListBox());
    }

    /**
     * Remove a ListBox from its container
     * @param member the ListBox to remove
     */
    private void removeMember(SwingScilabListBox member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(PopupMenu member) {
        return this.addMember((SwingScilabPopupMenu) member.getAsSimplePopupMenu());
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    private int addMember(SwingScilabPopupMenu member) {
        return contentPane.addWidget(member);
    }

    /**
     * Remove a PopupMenu from its container
     * @param member the PopupMenu to remove
     */
    @Override
    public void removeMember(PopupMenu member) {
        this.removeMember((SwingScilabPopupMenu) member.getAsSimplePopupMenu());
    }

    /**
     * Remove a PopupMenu from its container
     * @param member the PopupMenu to remove
     */
    private void removeMember(SwingScilabPopupMenu member) {
        contentPane.removeWidget(member);
    }

    /**
     * Add a Tree member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    @Override
    public int addMember(Tree member) {
        return this.addMember((SwingScilabTree) member.getAsSimpleTree());
    }

    /**
     * Add a Tree member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addMember(SwingScilabTree member) {
        return contentPane.addWidget(member.getAsComponent());
    }

    /**
     * Add a Tree member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addTree(SwingScilabTree member) {
        this.setContentPane(member.getAsComponent());
        return this.getComponentZOrder(member.getAsComponent());
    }

    /**
     * Remove a PopupMenu from its container
     * @param member the PopupMenu to remove
     */
    @Override
    public void removeMember(Tree member) {
        this.removeMember((SwingScilabTree) member.getAsSimpleTree());
    }

    /**
     * Remove a PopupMenu from its container
     * @param member the PopupMenu to remove
     */
    private void removeMember(SwingScilabTree member) {
        contentPane.removeTree(member);
    }

    /**
     * Add a member (dockable element) to container and returns its index
     * @param member the member to add
     * @return index of member in ArrayList
     */
    public int addMember(Dockable member) {
        // TODO Auto-generated method stub
        return 0;
    }

    /**
     * Get the current status of the Tab in its parent
     * @return true is the tab is the tab currently "on top" in its parent
     */
    @Override
    public boolean isCurrentTab() {
        // TODO should not always return TRUE
        return true;
    }

    /**
     * Get the parent window id for this tab
     * @return the id of the parent window
     */
    @Override
    public String getParentWindowId() {
        return this.parentWindowId;
    }

    /**
     * Set the parent window id for this tab
     * @param id the id of the parent window
     */
    @Override
    public void setParentWindowId(String id) {
        this.parentWindowId = id;
    }

    /**
     * Setter for MenuBar
     * @param newMenuBar : the MenuBar to set.
     * @see org.scilab.modules.gui.tab.SimpleTab#setMenuBar(org.scilab.modules.gui.menubar.MenuBar)
     */
    @Override
    public void setMenuBar(MenuBar newMenuBar) {
        this.menuBar = newMenuBar;
    }


    /**
     * Getter for MenuBar
     * @return MenuBar : the MenuBar associated to the Tab.
     * @see org.scilab.modules.gui.tab.SimpleTab#getMenuBar()
     */
    @Override
    public MenuBar getMenuBar() {
        return this.menuBar;
    }

    /**
     * Setter for ToolBar
     * @param newToolBar : the ToolBar to set.
     * @see org.scilab.modules.gui.tab.SimpleTab#setToolBar(org.scilab.modules.gui.toolbar.ToolBar)
     */
    @Override
    public void setToolBar(ToolBar newToolBar) {
        this.toolBar = newToolBar;
    }

    /**
     * Getter for ToolBar
     * @return ToolBar : the ToolBar associated to the Tab.
     * @see org.scilab.modules.gui.tab.SimpleTab#getToolBar()
     */
    @Override
    public ToolBar getToolBar() {
        return this.toolBar;
    }

    /**
     * Setter for InfoBar
     * @param newInfoBar the InfoBar to set.
     */
    @Override
    public void setInfoBar(TextBox newInfoBar) {
        this.infoBar = newInfoBar;
    }

    /**
     * Getter for InfoBar
     * @return the InfoBar associated to the Tab.
     */
    @Override
    public TextBox getInfoBar() {
        return this.infoBar;
    }

    /**
     * Set the callback of the tab
     * @param callback the callback to set.
     */
    @Override
    public void setCallback(CommonCallBack callback) {

        if (closeAction != null) {
            this.getTitlebar().removeAction(closeAction);
        }

        if (callback != null) {
            closeAction = new SciClosingAction(this, callback);
        } else {
            closeAction = new SciClosingAction(this);
        }

        closeAction.putValue(Action.NAME, DockingConstants.CLOSE_ACTION);
        ((Titlebar) getTitlePane()).removeAction(DockingConstants.CLOSE_ACTION);
        addAction(closeAction);

        /* Undock button */
        SciUndockingAction undockAction = new SciUndockingAction(this);
        undockAction.putValue(Action.NAME, UNDOCK);
        ((Titlebar) getTitlePane()).removeAction(UNDOCK);
        addAction(undockAction);

        /* Help button */
        SciHelpOnComponentAction helpAction = new SciHelpOnComponentAction(this);
        helpAction.putValue(Action.NAME, HELP);
        ((Titlebar) getTitlePane()).removeAction(HELP);
        addAction(helpAction);
    }

    /**
     * Set this tab as the current tab of its parent Window
     */
    @Override
    public void setCurrent() {
        ActiveDockableTracker.requestDockableActivation(this);
    }

    /**
     * Set the background color of the tab.
     * @param red red channel of the color
     * @param green green channel
     * @param blue blue channel
     */
    @Override
    public void setBackground(double red, double green, double blue) {
        Color newColor = new Color((float) red, (float) green, (float) blue);
        contentPane.setBackground(red, green, blue);
        scrolling.setBackground(red, green, blue);
        setBackground(newColor);
    }

    /**
     * Get the part of the axes which is currently viewed
     * @return [x,y,w,h] array
     */
    @Override
    public int[] getViewingRegion() {
        return scrolling.getViewingRegion();
    }

    /**
     * Specify a new viewport for the axes
     * For SwingScilabCanvas viewport can not be modified
     * since it match the parent tab size
     * @param posX X coordinate of upper left point of the viewport within the axes
     * @param posY Y coordinate of upper left point of the viewport within the axes
     * @param width width of the viewport
     * @param height height of the viewport
     */
    @Override
    public void setViewingRegion(int posX, int posY, int width, int height) {
        // Check that the canvas can be resized
        if (!scrolling.getAutoResizeMode()) {
            // don't set viewport size here it should always fit parent tab size
            // It seems that we must check the viewport size and positions
            // to get coherent values, otherwise the setViewPosition hangs...
            // there are three checks that must be performed for the two dimensions
            // - be sure that viewport position is greater than 0.
            // - if the viewport is larger than the canvas, then it can't be moved
            // - if the viewport is smaller than the canvas, then it should remains
            //   inside the canvas

            int canvasWidth = contentPane.getWidth();
            int canvasHeight = contentPane.getHeight();
            int[] curViewedRegion = getViewingRegion();
            int viewportPosX = curViewedRegion[0];
            int viewPortPosY = curViewedRegion[1];
            int viewportWidth = curViewedRegion[2];
            int viewportHeight = curViewedRegion[VIEWPORT_SIZE - 1];

            // use previous values as default ones
            int realPosX = 0;
            int realPosY = 0;


            if (viewportWidth <= canvasWidth) {
                // viewport smaller than the canvas
                // check that the viewport stays in the canvas
                // the left most position is canvasWidth - viewporwidth
                realPosX = Math.min(posX, canvasWidth - viewportWidth);
            } else {
                // viewport larger than the canvas
                // get previous position (should be 0)
                realPosX = viewportPosX;
            }
            // last check, greater than 0
            realPosX = Math.max(0, realPosX);

            if (viewportHeight <= canvasHeight) {
                realPosY = Math.min(posY, canvasHeight - viewportHeight);
            } else {
                realPosY = viewPortPosY;
            }
            realPosY = Math.max(0, realPosY);

            // must be called on the Swing thread otherwise some JOGL corruption may appear
            final Point realPos = new Point(realPosX, realPosY);
            try {
                SwingUtilities.invokeAndWait(new Runnable() {
                    @Override
                    public void run() {
                        scrolling.setViewPosition(realPos.x, realPos.y);
                    }
                });
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.getCause().printStackTrace();
            }


        }
    }

    /**
     * Set the event handler of the Canvas
     * @param funName the name of the Scilab function to call
     */
    public void setEventHandler(String funName) {
        disableEventHandler();
        Integer figureId = (Integer) GraphicController.getController().getProperty(getId(), __GO_ID__);
        eventHandler = new ScilabEventListener(funName, figureId);
    }

    /**
     * Set the status of the event handler of the Canvas
     * @param status is true to set the event handler active
     */
    public void setEventHandlerEnabled(boolean status) {
        if (status) {
            enableEventHandler();
        } else {
            disableEventHandler();
        }
    }

    /**
     * Specify whether the canvas should fit the parent tab size
     * (and consequently the scrollpane size) or not
     * @param onOrOff true to enable autoresize mode
     */
    @Override
    public void setAutoResizeMode(boolean onOrOff) {
        scrolling.setAutoResizeMode(onOrOff);
    }

    /**
     * @return whether the resize mode is on or off
     */
    @Override
    public boolean getAutoResizeMode() {
        return scrolling.getAutoResizeMode();
    }

    /**
     * Get the displacement in pixel that should be used for rotating axes
     * @param displacement out parameter, [x,y] array of displacement in pixels
     * @return true if the displacement recording continue, false otherwise
     */
    @Override
    public boolean getRotationDisplacement(int[] displacement) {
        return contentPane.getRotationDisplacement(displacement);
    }

    /**
     * Close the tab and disable it.
     */
    public void close() {
        setMenuBar(null);
        setToolBar(null);
        setInfoBar(null);
        setTitlebar(null);
        removeAll();
        setActive(false);

        scrolling = null;
        contentPane = null;

        // without this children canvas are not released.
        Container dummyContainer = new Container();
        this.setContentPane(dummyContainer);
    }

    /**
     * Asynchronous stop of rotation tracking.
     */
    @Override
    public void stopRotationRecording() {
        contentPane.stopRotationRecording();
    }

    /**
     * Redefine paint children to be sure that AWT components are well painted.
     *  @param g a Graphics
     */
    @Override
    public void paintChildren(Graphics g) {
        Component[] children = getComponents();
        for (int i = 0; i < children.length; i++) {
            // AWT children don't draw themselves automatically
            // so force their draw
            if (!children[i].isLightweight()) {
                children[i].paint(g);
            }
        }
        super.paintChildren(g);
    }

    /**
     * Update the tab after a modification of its properties
     * @param property the property name
     * @param value the property value
     * @see org.scilab.modules.gui.SwingViewObject#update(java.lang.String, java.lang.Object)
     */
    public void update(String property, Object value) {
        if (property.equals(__GO_NAME__)) {
            String name = ((String) value);
            Integer figureId = (Integer) GraphicController.getController().getProperty(getId(), __GO_ID__);
            updateTitle(name, figureId);
        } else if (property.equals(__GO_ID__)) {
            /* Update title */
            Integer figureId = ((Integer) value);
            String name = (String) GraphicController.getController().getProperty(getId(), __GO_NAME__);
            updateTitle(name, figureId);

            /** Update tool bar */
            setToolBar(ToolBarBuilder.buildToolBar(GRAPHICS_TOOLBAR_DESCRIPTOR, figureId));
            SwingScilabWindow parentWindow = SwingScilabWindow.allScilabWindows.get(getParentWindowId());
            parentWindow.addToolBar(getToolBar());

            /* Update callback */
            String closingCommand =
                "if (get_figure_handle(" + figureId + ") <> []) then"
                +      "  if (get(get_figure_handle(" + figureId + "), 'event_handler_enable') == 'on') then"
                +      "    execstr(get(get_figure_handle(" + figureId + "), 'event_handler')+'(" + figureId + ", -1, -1, -1000)', 'errcatch', 'm');"
                +      "  end;"
                +      "  delete(get_figure_handle(" + figureId + "));"
                +      "end;";
            setCallback(null);
            setCallback(ScilabCloseCallBack.create(getId(), closingCommand));
            /* Update menus callbacks */
            String[] children = (String[]) GraphicController.getController().getProperty(getId(), __GO_CHILDREN__);
            updateChildrenCallbacks(children, figureId);
        } else if (property.equals(__GO_SIZE__)) {
            Integer[] size = (Integer[]) value;
            SwingScilabWindow.allScilabWindows.get(parentWindowId).setDims(new Size(size[0], size[1]));
        } else if (property.equals(__GO_POSITION__)) {
            Integer[] position = (Integer[]) value;
            SwingScilabWindow.allScilabWindows.get(parentWindowId).setPosition(new Position(position[0], position[1]));
        } else if (property.equals(__GO_AXES_SIZE__)) {
            Integer[] axesSize = (Integer[]) value;
            Dimension oldAxesSize = getContentPane().getSize();
            if (oldAxesSize.getWidth() != axesSize[0] || oldAxesSize.getHeight() != axesSize[1]) {
                // Autoresize == "on" management
                // TODO manage scrolling in with autoresize mode set to "off"
                // TODO manage tabs when there are docked (do not change the window size if more than one tab docked)
                int deltaX = axesSize[0] - (int) oldAxesSize.getWidth();
                int deltaY = axesSize[1] - (int) oldAxesSize.getHeight();
                Size parentWindowSize = SwingScilabWindow.allScilabWindows.get(parentWindowId).getDims();
                SwingScilabWindow.allScilabWindows.get(parentWindowId).setDims(
                    new Size(parentWindowSize.getWidth() + deltaX, parentWindowSize.getHeight() + deltaY));
            }
        } else if (property.equals(__GO_INFO_MESSAGE__)) {
            getInfoBar().setText((String) value);
        } else if (property.equals(__GO_EVENTHANDLER_ENABLE__)) {
            Boolean enabled = (Boolean) GraphicController.getController().getProperty(getId(), __GO_EVENTHANDLER_ENABLE__);
            setEventHandlerEnabled(enabled);
        } else if (property.equals(__GO_EVENTHANDLER_NAME__)) {
            String eventHandlerName = (String) GraphicController.getController().getProperty(getId(), __GO_EVENTHANDLER_NAME__);
            setEventHandler(eventHandlerName);
        }
    }

    /**
     * Update the menus callbacks when they are linked to the figure ID
     * @param children the children UID
     * @param parentFigureId the figure ID
     */
    private void updateChildrenCallbacks(String[] children, int parentFigureId) {
        for (int kChild = 0; kChild < children.length; kChild++) {
            String childType = (String) GraphicController.getController().getProperty(children[kChild], __GO_TYPE__);
            if (childType.equals(__GO_UIMENU__)
                    || childType.equals(__GO_UIPARENTMENU__)
                    || childType.equals(__GO_UICHILDMENU__)
                    || childType.equals(__GO_UICHECKEDMENU__)) {
                String cb = (String) GraphicController.getController().getProperty(children[kChild], __GO_CALLBACK__);
                SwingView.getFromId(children[kChild]).update(__GO_CALLBACK__, replaceFigureID(cb, parentFigureId));
                String[] menuChildren = (String[]) GraphicController.getController().getProperty(children[kChild], __GO_CHILDREN__);
                updateChildrenCallbacks(menuChildren, parentFigureId);
            }
        }
    }

    /**
     * Replace pattern [SCILAB_FIGURE_ID] by the figure index
     * @param initialString string read in XML file
     * @param parentFigureId the figure ID
     * @return callback string
     */
    private String replaceFigureID(String initialString, Integer parentFigureId) {
        return initialString.replaceAll("\\[SCILAB_FIGURE_ID\\]", Integer.toString(parentFigureId));
    }

    /**
     * Update the title of the Tab
     * @param figureName figure_name property
     * @param figureId figure_id property
     */
    private void updateTitle(String figureName, Integer figureId) {
        if ((figureName != null) && (figureId != null)) {
            String figureTitle = figureName.replaceFirst("%d", figureId.toString());
            setName(figureTitle);
        }
    }

    /**
     * Get the tab UID
     * @return the UID
     * @see org.scilab.modules.gui.SwingViewObject#getId()
     */
    public String getId() {
        return id;
    }

    /**
     * Set the tab UID
     * @param id the UID
     * @see org.scilab.modules.gui.SwingViewObject#setId(java.lang.String)
     */
    public void setId(String id) {
        this.id = id;
    }

    /**
     * Turn on event handling.
     */
    private void enableEventHandler() {
        contentCanvas.addEventHandlerKeyListener(eventHandler);
        contentCanvas.addEventHandlerMouseListener(eventHandler);
        contentCanvas.addEventHandlerMouseMotionListener(eventHandler);
    }

    /**
     * Turn off event handling.
     */
    private void disableEventHandler() {
        if (eventHandler != null) {
            contentCanvas.removeEventHandlerKeyListener(eventHandler);
            contentCanvas.removeEventHandlerMouseListener(eventHandler);
            contentCanvas.removeEventHandlerMouseMotionListener(eventHandler);
        }
    }
}
