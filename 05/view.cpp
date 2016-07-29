/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 05 - Scene Graph with Animation
	Email : 	Tarun.Jain@iiitb.org
	File Name:	view.cpp
*/

// Header Files
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "rply.h"
#include "rplyfile.h"

// Global Variables
extern Model model;			// Model Class Object
extern View view;			// View Class Object
extern Controller controller;		// Controller Class Object

int View::camNo = 1;			// Camera Number
int View::maxCam = 4;
int View::enableAxis = 1;		// Enable Axis
int View::enableBox = 1;		// Initially Enable Bounding Box
int View::enableLight = 1;		// Enable Light
int View::enableTexture = 1;

extern int winX;			// Window's Width
extern int winY;			// Window's Height
extern float cam2[];			// Camera 2 Position
extern float cam3[];
extern float cam4[];
int View::enableSpot = 1;
int View::enableHeadLight = 1;


// Initialize Rendering Function
void View :: initRendering()
{
	
	// Initialize all Objects
	for( int g = 0; g < object_count; g++)
		controller.initObject(g);
	
	controller.setRelations();
	
	// To use glNormal*() Function
   	glEnable(GL_NORMALIZE);
 
	// Get Window Size
	winX = glutGet( GLUT_WINDOW_WIDTH );
	winY = glutGet( GLUT_WINDOW_HEIGHT );
	
	glViewport(0, 0, winX, winY);						// Set the Viewing Window
	
	glShadeModel( GL_SMOOTH );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	
	glEnable(GL_DEPTH_TEST);						// Enable Depth Buffer Updation
	glClearColor(0.0, 0.0, 0.0, 0.0);					// Set Background Color to Black
	glMatrixMode( GL_PROJECTION );						// Entering Camera Mode
	glLoadIdentity();							// Reset the Camera Matrix
	gluPerspective( 70.0, (float)winX / (float)winY, 0.1, 50.0 );		// Camera - ViewAngle, Viewport, nearZ, farZ
	glMatrixMode(GL_MODELVIEW);						// Entering Viewing Mode
	glLoadIdentity();							// Reset View Matrix
}

// Resize Window Function
void View :: handleResize(int wt, int ht)
{
	if (ht  == 0)
		ht = 1;
	winX = wt;								// Update Window's Width to New Width
	winY = ht;								// Update Window's Height to New Height
	glViewport(0,0, wt, ht);						// Set the Viewing Window
	glMatrixMode(GL_PROJECTION); 						//Switch to setting the camera perspective
	glLoadIdentity(); 							//Reset the camera
	gluPerspective( 70.0, (float)winX / (float)winY, 0.1, 50.0 );		// Camera - ViewAngle, Viewport, nearZ, farZ
	glMatrixMode(GL_MODELVIEW);						// Entering Viewing Mode
	glLoadIdentity();							// Reset View Matrix
}

// Display/Rendering Function
void View :: drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear Depth and Color Buffer
	glMatrixMode( GL_MODELVIEW );						// Switching to Viewing Mode
	glLoadIdentity();							// Reset View Matrix

	// Rendering The Scene
	controller.renderScene();	
	
	// Swap Buffers to Display Changes
	glutSwapBuffers();
}
