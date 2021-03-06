/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Pierre Lando
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 */
package org.scilab.modules.gui.graphicWindow;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.LayoutManager;
import java.io.Serializable;

/**
 * @author Pierre Lando
 */
public class PanelLayout implements LayoutManager, Serializable{

    public static final String GL_CANVAS = "GL_CANVAS";
    public static final String UI_CONTROL = "UI_CONTROL";
    private Component canvas;

    @Override
    public void addLayoutComponent(String name, Component comp) {
        if (GL_CANVAS.equals(name)) {
            canvas = comp;
        }
    }

    @Override
    public void removeLayoutComponent(Component comp) {
    }

    @Override
    public Dimension preferredLayoutSize(Container parent) {
        return null;
    }

    @Override
    public Dimension minimumLayoutSize(Container parent) {
        return null;
    }

    @Override
    public void layoutContainer(Container parent) {
        for (Component child : parent.getComponents()) {
            if (child.equals(canvas)) {
                child.setBounds(0, 0, parent.getWidth(), parent.getHeight());
                parent.setComponentZOrder(child, parent.getComponentCount() - 1);
            }

            /* Here you can perform the layout of UI object.
            if (child instanceof SwingViewObject) {
                String id = ((SwingViewObject) child).getId());
            }
            */
        }
    }
}
