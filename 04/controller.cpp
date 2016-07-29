/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	controller.cpp
*/

// Header Files
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "rply.h"
#include "rplyfile.h"

// Global Variables
extern Model model;			// Model Class Object
extern View view;			// View Class Object
int Controller::mState = UP;		// Initial Mouse State
int Controller::oldX = -13;		// Initial Old X Coordinate
int Controller::oldY = -13;		// Initial Old Y Coordinate

// Keyboard Function
void Controller::keyboard(unsigned char key, int x, int y)
{
	// Key = Pressed Button on Keyboard
	switch(key)
	{
		// Enable or Disable Bounding Box - Press 'b'
		case 'b':
		case 'B':
			if(view.enableBox == 1) 
				view.enableBox = 0; 
			else
				view.enableBox = 1;
			break;
		// Enable or Disable Texture - Press 't'
		case 't':
		case 'T':
			if(view.enableTexture == 1) 
				view.enableTexture = 0; 
			else
				view.enableTexture = 1;
			break;
		// Enable or Disable Axis - Press 'a'
		case 'a':
		case 'A':
			if(view.enableAxis == 1) 
				view.enableAxis = 0; 
			else
				view.enableAxis = 1;
			break;
		// Enable or Disable HeadLight attached with Camera - Press 'h'
		case 'h':
		case 'H':
			if(view.enableHeadLight == 1) 
			{
				view.enableHeadLight = 0;
				glDisable(GL_LIGHT2);
				//glEnable(GL_LIGHT3);
			}
			else
			{
				view.enableHeadLight = 1;
				glEnable(GL_LIGHT2);
				//glEnable(GL_LIGHT3);
			}
			break;
		// Enable or Disable Spot Light on Apple - Press 's'
		case 's':
		case 'S':
			if(view.enableSpot == 1) 
			{
				view.enableSpot = 0;
				glDisable(GL_LIGHT3);
				//glEnable(GL_LIGHT2);
			}
			else
			{
				view.enableSpot = 1;
				//glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
			}
			break;
		// Enable or Disable Lighting - Press 'l'
		case 'l':
		case 'L':
			if(view.enableLight == 1)
			{
				view.enableSpot = 0;
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glDisable(GL_LIGHT3);
				view.enableLight = 0;
			}
			else
			{
				view.enableSpot = 1;
				view.enableLight =1 ;
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
			}
			break;
		// Enable Good Looking Lighting - Press 'g'
		case 'g':
		case 'G':
			view.enableSpot = 0;
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			break;
		case 'i':
			view.transz += 0.1;
			break;
		case 'o':
			view.transz -= 0.1;
			break;
		// To Exit - Press 'ESC'
		case 27:
			std::cout<<"Quiting ..."<<std::endl;
			exit(-1);
			break;
	}
	
	// Render the Scene with Updated Changes
	glutPostRedisplay();
}

// Mouse Motion Function
void Controller::glutMotion(int x, int y)
{
	// When Mouse Button is Pressed and Mouse Dragged
	if (mState == DOWN)
    	{
    		// Rotate the Camera Through TrackBall
		view.rotate(oldX, oldY, x, y);
		// Re-display Scene
		glutPostRedisplay();
    	}
    	// Update Old Co-ordinates to Current Coordinates after Rotation
   	oldX = x;
    	oldY = y;
}

// Mouse Function
void Controller::glutMouse(int button, int state, int x, int y)
{
	// When Mouse Button Pressed
	if(state == GLUT_DOWN)
    	{
    		// Check the button pressed
        	switch(button)
        	{
        		// Right Button pressed
        	    case GLUT_RIGHT_BUTTON:
			oldX = x;
        		oldY = y;
        	        break;
        	        // Left Button pressed
        	    case GLUT_LEFT_BUTTON:
			mState = DOWN;				// Update Mouse State when Left Button pressed
        	        oldX = x;
        	        oldY = y;
        		break;
        	}	
    	}
    	// When Mouse Button is Not pressed or released
    	else if (state == GLUT_UP)
    	{
        	mState = UP;					// Update Mouse State
        	switch(button)
        	{
        	    case GLUT_RIGHT_BUTTON:
			oldX = x;
        	        oldY = y;
        	        break;
        	    case GLUT_LEFT_BUTTON:
			view.rotate(0, 0, 0, 0);		// Rotation Stops - Reinitialize it
			break;
        	}
       	 	// Re-display the Scene      
       		glutPostRedisplay();
	}
}

// Special Keyboard Keys Function
void Controller::SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)				// Left Arrow Key
	{
		view.transx-=0.1;				// Translate in -X axis
	}
	else if (key == GLUT_KEY_UP)				// Up Arrow Key
	{
		view.transy+=0.1;				// Translate in +Y axis
	}
	else if (key == GLUT_KEY_RIGHT)				// Right Arrow Key
	{
		view.transx+=0.1;				// Translate in +X axis
	}
	else if (key == GLUT_KEY_DOWN)				// Down Arrow Key
	{
		view.transy-=0.1;				// Translate in -Y axis
	}
	// Re-display the Scene
	glutPostRedisplay();
}

// Timer Function
void Controller :: update(int value) 
{
	view.angle += 2.0f;
	if (view.angle > 360) 
	{
		view.angle -= 360;
	}
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 1 milliseconds
	glutTimerFunc(1, update, 0);
}


// Run Function To Demonstrate Project
void Controller :: run( char* argv[], int number)
{
	// For Each Ply File
	for(int k = 2; k <= number; k++)
	{
		// Reading Ply File : Assigning Object Number
		model.read(argv[k], k - 2);
		// Scaling Object to Fit the Scene
		//model.neutralize( k-2);
		// Calculating Normals for Object
		model.initNormals( k-2);
	}
	
	view.initRendering(); //Initialize rendering
	//Set handler function for drawing
	glutDisplayFunc(view.drawScene);
	//Set handler function for window resize
	glutReshapeFunc(view.handleResize);
	//Set handler function for keypress
	glutKeyboardFunc(keyboard);
	//Set handler function for Special keypress
	glutSpecialFunc(SpecialKeys);
	//Set handler function for Mouse Motion
	glutMotionFunc(glutMotion);
	//Set handler function for Mouse
	glutMouseFunc(glutMouse);
	// Set handler function for Timer
	glutTimerFunc(1, update, 0);
	//Start the main loop
	glutMainLoop(); 
}
