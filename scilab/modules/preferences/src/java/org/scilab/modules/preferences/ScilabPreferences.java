/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Calixte DENIZET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.preferences;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Class to get the toolboxes informations
 * @author Calixte DENIZET
 */
public class ScilabPreferences {

    private static Map<String, ToolboxInfos> tbxs = new HashMap<String, ToolboxInfos>();

    /**
     * @param name the toolbox name
     * @param path the toolbox path
     * @param prefFile the toolbox preference file path
     */
    public static void addToolboxInfos(String name, String path, String prefFile) {
        tbxs.put(path, new ToolboxInfos(name, path, prefFile));
    }

    /**
     * @return a list of the toolboxes infos
     */
    public static List<ToolboxInfos> getToolboxesInfos() {
        return new ArrayList<ToolboxInfos>(tbxs.values());
    }

    /**
     * @param path the toolbox to remove
     */
    public static void removeToolboxInfos(String path) {
        tbxs.remove(path);
    }

    /**
     * Toolbox infos
     */
    public static class ToolboxInfos {

        private String name;
        private String path;
        private String prefFile;

        /**
         * Default constructor
         * @param name the toolbox name
         * @param path the toolbox path
         * @param prefFile the toolbox preference file path
         */
        public ToolboxInfos(String name, String path, String prefFile) {
            this.name = name;
            this.path = path;
            this.prefFile = prefFile;
        }

        /**
         * @return the toolbox name
         */
        public String getName() {
            return name;
        }

        /**
         * @return the toolbox path
         */
        public String getPath() {
            return path;
        }

        /**
         * @return the toolbox preference file path
         */
        public String getPrefFile() {
            return prefFile;
        }

        /**
         * {@inheritDoc}
         */
        public String toString() {
            return "Toolbox: " + name + "\nPath: "+ path + "\nPreference file: " + prefFile;
        }
    }
}
