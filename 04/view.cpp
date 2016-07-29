/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
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
float View::transx = 0.0;		// Translation Factor in X Axis
float View::transy = 0.0;		// Translation Factor in Y Axis
float View::transz = 0.0;		// Translation Factor in Z Axis
float View::Position[3] = {.0, 1.5, 4};// Initialize Position Vector of Camera
int View::enableBox = 1;		// Initially Enable Bounding Box
int View::enableTexture = 1;
int View::enableAxis = 1;
int View::enableSpot = 1;
int View::enableHeadLight = 1;
int View::enableLight = 1;
float View::scale = 5;			// Initial Scaling Factor
extern int winX;			// Window's Width
extern int winY;			// Window's Height
Trackball View::trackball;		// TrackBall for Rotation through Mouse
float View::angle = 0.0;

GLUquadricObj *IDquadric;		// For Quadratic Object

// Initialize Rendering Function
void View :: initRendering()
{
	// Loading Textures
	for( int g = 0; g < object_count; g++)
		texture[g].callToTexture(g);
		
	// Creating Quadratic Object
	IDquadric=gluNewQuadric();
 	gluQuadricNormals(IDquadric, GLU_SMOOTH);
  	gluQuadricTexture(IDquadric, GL_TRUE);
	
	/*---LIGHTING INITIALIZATION---*/
   	glEnable(GL_LIGHTING);
   	glEnable(GL_LIGHT0);
   	glEnable(GL_LIGHT1);
   	glEnable(GL_LIGHT2);
   	glEnable(GL_LIGHT3);
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
	gluPerspective( 60.0, (float)winX / (float)winY, 0.1, 10.0 );		// Camera - ViewAngle, Viewport, nearZ, farZ
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
	gluPerspective( 60.0, (float)winX / (float)winY, 0.1, 10.0 );		// Camera - ViewAngle, Viewport, nearZ, farZ
	glMatrixMode(GL_MODELVIEW);						// Entering Viewing Mode
	glLoadIdentity();							// Reset View Matrix
}

// Display/Rendering Function
void View :: drawScene()
{
	//glColor3f(1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear Depth and Color Buffer
	glMatrixMode( GL_MODELVIEW );						// Switching to Viewing Mode
	glLoadIdentity();							// Reset View Matrix

	float x,y,z;								// Temporary Variables
	static float rotation_transform[4][4];					// Rotation Matrix Variable
	
	/* ---Camera Positioning--- */
	// Initial Camera Positions
	Position[0] = 0.0;
	Position[1] = 1.5;
	Position[2] = 4.0;

	trackball.rotationMatrix( rotation_transform );				// Filling Rotation Matrix by using TrackBall

	// Multiplying Position Matrix with Rotation Matrix
	x= Position[0] * rotation_transform[0][0] + Position[1] * rotation_transform[0][1] + Position[2] * rotation_transform[0][2] 
	+ rotation_transform[0][3];
		
	y = Position[0] * rotation_transform[1][0] + Position[1] * rotation_transform[1][1] + Position[2] * rotation_transform[1][2] 
	+ rotation_transform[1][3];
		
	z = Position[0] * rotation_transform[2][0] +Position[1] * rotation_transform[2][1] + Position[2] * rotation_transform[2][2] 
	+ rotation_transform[2][3];

	// Updating New Camera Positions
	Position[0] =x;
	Position[1] =y;
	Position[2] =z;
	
	// Place Camera at New Position
	gluLookAt( Position[0], Position[1], Position[2], 0., 0., 0, 0, 1, 0);
	
	// Draw Axis
	if( enableAxis == 1)
		model.drawAxis();
	
	// Draw Floor
	texture[5].callToTexture(5);						// 6th Texture is Floor
	model.drawFloor();
	
	/* ---Light Positions ---*/
	// Light at Right Front of Apple
  	
	GLfloat light_position0[] = { 0.3, 0.0, 0.3, 1.0 };
  	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    	GLfloat lightColor0[] = {1, 1, 1, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    
    	// Light at Left Front of Apple
    	GLfloat light_position1[] = { -0.3, 0.0, -0.3, 1.0 };
  	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    	GLfloat lightColor1[] = {1, 1, 1, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	
	// Spot Light attached to Camera - Head Light
	GLfloat light_position2[] = { Position[0], Position[1], Position[2], 1.0 };
	GLfloat spot_position2[] = { -Position[0], -Position[1], -Position[2] };
    	GLfloat lightColor2[] = {1.0,1.0,0.0, 1.0f};
    	GLfloat spec_light2[] = { 1,1,1,1};
       	glLightfv(GL_LIGHT2, GL_SPECULAR, spec_light2);
    	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
    	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spot_position2);

	// Spot Light on Apple
	GLfloat light_position3[] = {0.0, 1.6, 0, 1.0 };
    	GLfloat lightColor3[] = {1, 1 ,1, 1.0f};
    	GLfloat spot_position3[] = { 0.0, -1.0,  0.0};
    	GLfloat spec_light3[] = { 1,1,1,1};
    	
    	glLightfv(GL_LIGHT3, GL_SPECULAR, spec_light3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
    	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor3);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
    	glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,spot_position3);

	// Spot Light Indicator
	glColor3f(1,1,1);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(20);
	glBegin(GL_POINTS);
		glVertex3f(0, 2, 0);
	glEnd();

    	glPushMatrix();
    	
		glScalef(scale, scale, scale);
		glTranslatef(transx, transy, transz);				// Translate Entire Scene

		// To Draw All Objects
		for( int j = 0; j < object_count; j++)
		{
			int angle_for_fire = 45;
			// Placing Objects in Scene
			if(j == 0)
			{
				glTranslatef( 0.3, 0.1, 0.3);
				model.drawFire();
				for( int u = 1; u < 4; u++)
				{	glRotatef(angle_for_fire, 0,1,0);
					model.drawFire();
				}
				glRotatef(-135, 0,1,0);
			}
			if(j == 1)
			{
				glTranslatef(-0.6, 0.0, 0.0);
				model.drawFire();
				for( int u = 1; u < 4; u++)
				{	glRotatef(angle_for_fire, 0,1,0);
					model.drawFire();
				}
				glRotatef(-135, 0,1,0);
			}
			if(j == 2)
			{
				glTranslatef(0.6, 0.0, -0.6);
				model.drawFire();
				for( int u = 1; u < 4; u++)
				{	glRotatef(angle_for_fire, 0,1,0);
					model.drawFire();
				}
				glRotatef(-135, 0,1,0);
			}
			if(j == 3)
			{
				glTranslatef(-0.6, 0.0, 0.0);
				model.drawFire();
				for( int u = 1; u < 4; u++)
				{	glRotatef(angle_for_fire, 0,1,0);
					model.drawFire();
				}
				glRotatef(-135, 0,1,0);
			}
			if(j == 4)
			{
				glTranslatef(0.3, -0.095, 0.3);
				glScalef(2,2,2);
			}
			// If Bounding Box is Enabled - Draw Bounding Box
			if(enableBox)
				model.drawBox(j);

			model.drawObject(j);				// Draw Object
		}
	
	if(enableSpot)
	{
	// Drawing Cone for SPOT Lighting Effect
	//glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	Texture spotLight;
	spotLight.image = loadBMP("spotlight.bmp");
	spotLight.tex = spotLight.loadTexture(spotLight.image);
	glRotatef(-90, 1,0,0);
	glColor4f(1.0f, 0.0f, 0.0f, 0.4f); 
	glRotatef(angle, 0,0,1);
	//GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	//GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
	GLfloat mat_transparent[] = { 1,0,0, 0.6 };
	GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
		
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_TEXTURE_2D);	
	glBindTexture ( GL_TEXTURE_2D, spotLight.tex);
	gluCylinder(IDquadric, 0.08, 0.001f, 0.2 ,32,32);
	glDisable(GL_TEXTURE_2D);
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);
	glColor3f(1,1,1);
	}
	
	glPopMatrix();
	
	// Swap Buffers to Display Changes
	glutSwapBuffers();
}

// Rotate Function
void View :: rotate(float oldx, float oldy, float x, float y)
{
	// Call Trackball Rotate
	trackball.rotate((2.0*oldx - winX)/(float)winX,
			(winY - 2.0*oldy)/(float)winY,
			(2.0*x - winX)/(float)winX,
			(winY - 2.0*y)/(float)winY);
}
