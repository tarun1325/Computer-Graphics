/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 1 Computer Graphics: 2D Rendering.
	File: View.
*/

// Header Files
#include "header.h"
//using namespace std;
// Redraw all points
void redrawPoints ()
{
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(10);
	glBegin (GL_POINTS);
	for(int i=0;i<points.size();i++) 
	{
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd ();
}

// Function to Display on the Screen
void drawScene()
{
	glClear( GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -1.0f);
	
	// Drawing X-axis
	glLineWidth(1.5f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin (GL_LINES);
      		glVertex2f(win_width/2, 0.0f);
     		glVertex2f(-win_width/2, 0.0f);  
   	glEnd ();

	// Drawing Y-axis
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin (GL_LINES);
      		glVertex2f(0.0f, win_height/2);
     		glVertex2f(0.0f, -win_height/2);  
   	glEnd ();
 	
	glPushMatrix();					// Saving the Matrix into stack
	glScalef (zoom[0], zoom[1], zoom[2]);		// Zooming in/out according to scaling values
	glRotatef(-rotAngle, 0.0, 0.0, 0.1);		// Rotation around z-axis according to rotate Angle
	
	if (distPointCount == 2) 
	{
		glColor3f(1.0, 0.0, 1.0);
		glPointSize(10);

		translate[0] = (float)(px2 - px1);
		translate[1] = (float)(py2 - py1);
		distPointCount = 0;
	}
   
	glTranslatef (translate[0], translate[1], translate[2]);
   
	if (isLagrange)
		drawLagrange();

	if (isBezier)
		drawBezier();

	redrawPoints();

	glPopMatrix();
	
	glFlush();
	glutPostRedisplay();
}

