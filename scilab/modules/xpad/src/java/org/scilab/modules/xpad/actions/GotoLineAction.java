/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Bruno JOFRET
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

package org.scilab.modules.xpad.actions;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.KeyStroke;

import org.scilab.modules.gui.menuitem.MenuItem;
import org.scilab.modules.xpad.Xpad;
import org.scilab.modules.xpad.style.ScilabStyleDocument;

public class GotoLineAction extends DefaultAction {
	
	private static boolean windowAlreadyExist ;

	private JFrame mainFrame ;
	private JTextField enterLineNumberField ;
	private JButton okButton ;
	
	private GotoLineAction(Xpad editor) {

    		super("Goto Line...", editor);

	}
	
	public static MenuItem createMenu(Xpad editor) {
		return createMenu("Goto Line...", null, new GotoLineAction(editor), KeyStroke.getKeyStroke(KeyEvent.VK_G, ActionEvent.CTRL_MASK));
	 }

	 @Override
	public void doAction() {
	    	if (!GotoLineAction.windowAlreadyExist ){
	    		GotoLineAction.windowAlreadyExist= true ;
	    		gotoLineBox ();
	    	}
	}
	
	public void gotoLineBox (){

	        mainFrame = new JFrame();
	        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	      
	        mainFrame.setLayout(new GridBagLayout());



	        JLabel label = new JLabel("Enter line number");

	         enterLineNumberField = new JTextField( );
	        
	        JButton cancelButton = new JButton("Cancel");
	         okButton = new JButton("Ok");
	        okButton.setPreferredSize(cancelButton.getPreferredSize());

	        GridBagConstraints gbc = new GridBagConstraints();

	        gbc.gridx = gbc.gridy = 0;
	        gbc.gridheight = gbc.gridwidth = 1;
	        gbc.insets = new Insets(0, 10, 0, 0);




	        gbc.gridx = 0;
	        gbc.gridy = 4;
	        gbc.gridheight = gbc.gridwidth = 1;
	        gbc.fill = GridBagConstraints.NONE;
	        gbc.insets = new Insets(0, 10, 0, 0);
	        mainFrame.add( label, gbc);

	        gbc.gridx = 1;
	        gbc.gridwidth = GridBagConstraints.REMAINDER;
	        gbc.fill = GridBagConstraints.HORIZONTAL;
	        gbc.insets = new Insets(5, 10, 0, 10);
	        mainFrame.add(enterLineNumberField, gbc);


	        gbc.gridx = 1;
	        gbc.gridy = 5;
	        gbc.gridheight = gbc.gridwidth = 1;
	        gbc.weightx = 1.;
	        gbc.fill = GridBagConstraints.NONE;
	        gbc.insets = new Insets(5, 0, 10, 5);
	        mainFrame.add(cancelButton, gbc);


	        gbc.gridx = 2;
	        gbc.weightx = 0.;
	        gbc.insets = new Insets(5, 0, 10, 10);
	        mainFrame.add(okButton, gbc);

		
			cancelButton.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent e) {
					GotoLineAction.windowAlreadyExist= false ;
					mainFrame.dispose();
				}
			});
	        
			okButton.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent e) {
					
					updateCaretPosition();
					getEditor().getTextPane().setFocusable(true);
					GotoLineAction.windowAlreadyExist= false ;
					mainFrame.dispose();
				}
			});
			
			enterLineNumberField.addKeyListener(new KeyListener(){
				public void keyTyped(KeyEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void keyPressed(KeyEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void keyReleased(KeyEvent arg0) {
					updateCaretPosition();
					
				}
				
				
			} );
			
	        
		//display the frame and set some properties
			
			mainFrame.addWindowListener( new WindowListener(){
				public void windowClosed(WindowEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void windowDeiconified(WindowEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void windowActivated(WindowEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void windowClosing(WindowEvent arg0) {
					GotoLineAction.windowAlreadyExist = false ;
					mainFrame.dispose();
					
				}
				public void windowDeactivated(WindowEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				public void windowIconified(WindowEvent arg0) {
					
				};
				public void windowOpened(WindowEvent arg0) {
					// TODO Auto-generated method stub
					
				}
				
			} );
			
			
	        mainFrame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	        mainFrame.setTitle("Go to line ...");
	        mainFrame.pack();
	        mainFrame.setLocationRelativeTo(null);
	        mainFrame.setVisible(true);	
	}

	private void updateCaretPosition(){
		if (  enterLineNumberField.getText().length() != 0){
			
			   // if the input is not a integer..
			   Pattern p = Pattern.compile("\\D");
			   Matcher m = p.matcher(enterLineNumberField.getText());

			   if (m.find()){
				   //... we disable okbutton
				   okButton.setEnabled(false);
				   
			   }else{
				   okButton.setEnabled(true);
			
				   
				   int lineNumber = Integer.decode(enterLineNumberField.getText()) -1;
				   int maxLineNumber = ((ScilabStyleDocument) getEditor().getTextPane().getStyledDocument()).getDefaultRootElement().getElementCount();
					
				   // avoid too big or too small number
				   if (lineNumber <= 0)
					   lineNumber = 0 ;
				   if (lineNumber >= maxLineNumber)
					   lineNumber = maxLineNumber -1;
				
				    // we get the offset of the line we want
					int start = ((ScilabStyleDocument) getEditor().getTextPane().getStyledDocument()).getDefaultRootElement().getElement(lineNumber).getStartOffset();
					getEditor().getTextPane().setCaretPosition(start);

			   }
			
		}else{
			 okButton.setEnabled(true);
		}
		
		
	}

}