/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.ui_data.variableeditor.actions;

import java.awt.Component;
import java.util.HashMap;
import java.util.Map;

import javax.swing.ImageIcon;
import javax.swing.JPopupMenu;
import javax.swing.JTable;

import org.scilab.modules.gui.bridge.menuitem.SwingScilabMenuItem;
import org.scilab.modules.gui.bridge.pushbutton.SwingScilabPushButton;
import org.scilab.modules.gui.events.callback.CommonCallBack;
import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.gui.menuitem.ScilabMenuItem;
import org.scilab.modules.gui.pushbutton.PushButton;
import org.scilab.modules.gui.pushbutton.ScilabPushButton;
import org.scilab.modules.gui.utils.ScilabSwingUtilities;
import org.scilab.modules.ui_data.EditVar;
import org.scilab.modules.ui_data.datatable.SwingEditvarTableModel;
import org.scilab.modules.ui_data.variableeditor.SwingScilabVariableEditor;

/**
 * RefreshAction class
 * @author Calixte DENIZET
 */
public final class PlotAction extends CommonCallBack {

    public static final int PLOT2D = 0;
    public static final int MATPLOT = 1;
    public static final int GRAYPLOT = 2;
    public static final int SGRAYPLOT = 3;
    public static final int CHAMP = 4;
    public static final int HISTPLOT = 5;
    public static final int MESH = 6;
    public static final int SURF = 7;
    public static final int HIST3D = 8;
    public static final int CONTOUR2D = 9;
    public static final int PIE = 10;

    private static final Map<String, Integer> map = new HashMap<String, Integer>();
    static {
        map.put("plot2d", 0);
        map.put("Matplot", 1);
        map.put("grayplot", 2);
        map.put("Sgrayplot", 3);
        map.put("champ", 4);
        map.put("histplot", 5);
        map.put("mesh", 6);
        map.put("surf", 7);
        map.put("hist3d", 8);
        map.put("contour2d", 9);
        map.put("pie", 10);
    }

    private static final String COM_PLOT2D = "plot2d(%s)";
    private static final String COM_MATPLOT = "Matplot(%s)";
    private static final String COM_GRAYPLOT = "grayplot(1:%s,1:%s,%s)";
    private static final String COM_SGRAYPLOT = "Sgrayplot(1:%s,1:%s,%s)";
    private static final String COM_CHAMP = "champ(1:%s,1:%s,real(%s),imag(%s))";
    private static final String COM_HISTPLOT = "histplot(10,%s)";
    private static final String COM_MESH = "mesh(%s)";
    private static final String COM_SURF = "surf(%s)";
    private static final String COM_HIST3D = "hist3d(%s)";
    private static final String COM_CONTOUR2D = "L?8625083632641564278=xget(\"fpf\");xset(\"fpf\",\" \");contour2d(1:%s,1:%s,%s,10);xset(\"fpf\",L?8625083632641564278);clear(\"L?8625083632641564278\")";
    private static final String COM_PIE = "L?8625083632641564278=%s;pie(L?8625083632641564278(find(L?8625083632641564278>0&L?8625083632641564278<>%%inf&L?8625083632641564278<>%%nan)))";

    private static final String[] COMMANDS = new String[]{COM_PLOT2D, COM_MATPLOT, COM_GRAYPLOT, COM_SGRAYPLOT, COM_CHAMP, COM_HISTPLOT, COM_MESH, COM_SURF, COM_HIST3D, COM_CONTOUR2D, COM_PIE};
    private static final String[] IMG = new String[] {
            "application-x-scilab-plot2d",
            "application-x-scilab-Matplot",
            "application-x-scilab-grayplot",
            "application-x-scilab-Sgrayplot",
            "application-x-scilab-champ",
            "application-x-scilab-histplot",
            "application-x-scilab-mesh",
            "application-x-scilab-surf",
            "application-x-scilab-hist3d",
            "application-x-scilab-contour2d",
            "application-x-scilab-pie" };

    private static final String CREATE = "Create";

    private final SwingScilabVariableEditor editor;
    private final int type;
    private final boolean onSelection;

    /**
     * Constructor
     * @param editor the editor
     * @param name the name of the action
     */
    private PlotAction(SwingScilabVariableEditor editor, String name, boolean onSelection) {
        super(name);
        this.editor = editor;
        this.type = map.get(name);
        this.onSelection = onSelection;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void callBack() {
        JTable table = editor.getCurrentTable();
        SwingEditvarTableModel model = (SwingEditvarTableModel) table.getModel();
        String datas = null;
        int rowC = 0;
        int colC = 0;

        if (!onSelection) {
            rowC = model.getScilabMatrixRowCount();
            colC = model.getScilabMatrixColCount();
            datas = model.getVarName();
        } else {
            int[] cols = table.getSelectedColumns();
            int[] rows = table.getSelectedRows();
            if (cols == null || cols.length == 0 || rows == null || rows.length == 0) {
                rowC = model.getScilabMatrixRowCount();
                colC = model.getScilabMatrixColCount();
                datas = model.getVarName();
            } else {
                if (model.getType().equals(EditVar.STRING)) {
                    return;
                }

                int[] rowSize = new int[1];
                int[] colSize = new int[1];
                datas = model.getScilabSubMatrix(rows, cols, rowSize, colSize);
                if (datas == null) {
                    return;
                }
                rowC = rowSize[0];
                colC = colSize[0];
            }
        }

        if (rowC == 0 || colC == 0) {
            return;
        }

        if (!model.getType().equals(EditVar.DOUBLE)) {
            datas = "double(" + datas + ")";
        }

        String com = COMMANDS[type];
        switch (type) {
        case 0:
        case 1:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
            com = String.format(com, datas);
            break;
        case 2:
        case 3:
            com = String.format(com, rowC, colC, datas);
            break;
        case 4:
            com = String.format(com, rowC, colC, datas, datas);
            break;
        case 9:
            if (rowC >= 2 && colC >= 2) {
                com = String.format(com, rowC, colC, datas);
            } else {
                return;
            }
            break;
        }

        model.execCommand("clf();" + com);
    }

    /**
     * Create a button for a tool bar
     * @param editor the associated editor
     * @param title tooltip for the button
     * @return the button
     */
    public static PushButton createButton(SwingScilabVariableEditor editor, String title) {
        final PushButton button = ScilabPushButton.createPushButton();
        button.setToolTipText(title);
        ImageIcon imageIcon = new ImageIcon(ScilabSwingUtilities.findIcon("plot"));
        ((SwingScilabPushButton) button.getAsSimplePushButton()).setIcon(imageIcon);

        final JPopupMenu popup = new JPopupMenu() {
                @Override
                public void show(Component c, int x, int y) {
                    SwingScilabPushButton but = (SwingScilabPushButton) button.getAsSimplePushButton();
                    super.show(but, 0, but.getBounds(null).height);
                }
            };
        popup.setBorderPainted(true);

        popup.add(PlotAction.createJMenuItem(editor, "plot2d", true));
        popup.add(PlotAction.createJMenuItem(editor, "Matplot", true));
        popup.add(PlotAction.createJMenuItem(editor, "grayplot", true));
        popup.add(PlotAction.createJMenuItem(editor, "Sgrayplot", true));
        popup.add(PlotAction.createJMenuItem(editor, "champ", true));
        popup.add(PlotAction.createJMenuItem(editor, "histplot", true));
        popup.add(PlotAction.createJMenuItem(editor, "mesh", true));
        popup.add(PlotAction.createJMenuItem(editor, "surf", true));
        popup.add(PlotAction.createJMenuItem(editor, "hist3d", true));
        popup.add(PlotAction.createJMenuItem(editor, "contour2d", true));
        popup.add(PlotAction.createJMenuItem(editor, "pie", true));

        popup.pack();

        ((SwingScilabPushButton) button.getAsSimplePushButton()).addActionListener(new CommonCallBack(null) {
                @Override
                public void callBack() {
                    if (!popup.isVisible()) {
                        popup.show(null, 0, 0);
                    } else {
                        popup.setVisible(false);
                    }
                }
            });

        return button;
    }

    /**
     * Create a menu item
     * @param editor the associated editor
     * @param title the menu title
     * @return the menu item
     */
    public static MenuItem createMenuItem(SwingScilabVariableEditor editor, String title, boolean onSelection) {
        MenuItem menu = ScilabMenuItem.createMenuItem();
        menu.setCallback(new PlotAction(editor, title, onSelection));
        menu.setText(title);
        ((SwingScilabMenuItem) menu.getAsSimpleMenuItem()).setIcon(new ImageIcon(ScilabSwingUtilities.findIcon(IMG[map.get(title)])));

        return menu;
    }

    /**
     * Create a menu item as a SwingScilabMenuItem
     * @param editor the associated editor
     * @param title the menu title
     * @return the menu item
     */
    public static SwingScilabMenuItem createJMenuItem(SwingScilabVariableEditor editor, String title, boolean onSelection) {
        return (SwingScilabMenuItem) createMenuItem(editor, title, onSelection).getAsSimpleMenuItem();
    }
}
