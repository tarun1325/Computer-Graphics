/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 1 Computer Graphics: 2D Rendering.
	File: Controller.
*/

// Header Files
#include "header.h"
//using namespace std;
// Function to Draw Lagrange Curve
void drawLagrange ()
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);

	for (int i = leftX; i <= rightX; i++)
	{
		float x = (float) i;
		float y = computeY( x, pointCount);
		glVertex2f ( x, y);
	}
	glEnd();
}

// Function to Draw Beizer Curve
void drawBezier () 
{
   glColor3f(1.0, 0.0, 1.0);

   glBegin(GL_LINE_STRIP);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   for (float t = 0.0; t <= 1.0; t+= 0.02) {
      float t1 = 1.0f - t;
      float x = 0;
      float y = 0;
      
      for (int i = 0; i < pointCount; i++ ) {
         float coeff = binCo (i, pointCount - 1);
         float pow_t1 = pow(t1, pointCount - i - 1);
         float pow_t = pow (t, i);

         x += coeff * pow_t1 * pow_t * points[i].x;
         y += coeff * pow_t1 * pow_t * points[i].y;
      }
      glVertex2f ( x, y);
   }

   glEnd();
}

// Function For Keyboard Inputs
void handleKeypress( unsigned char key, int x, int y)
		// key = key pressed, x and y are mouse co-ordinates
{
	switch(key)
	{
		case 'r':			// Rotate Right along Z-Axis
			rotAngle += 20.0;
			break;

		case 'l':			// Rotate Left along Z-Axis
			rotAngle += -20.0;
         		break;

		case '+':			// Zoom In
			zoom[0] += 1;
			zoom[1] += 1;
			zoom[2] += 1;
			break;

		case '-':			// Zoom Out
			zoom[0] -= 0.5;
			zoom[1] -= 0.5;
			zoom[2] -= 0.5;
			break;

		case 'a':			// Translate along -X axis
			translate[0] += -2.0;
			shiftX -= 2;
			break;

		case 'w':			// Translate along +Y axis
			translate[1] += 2.0;
			break;

		case 'd':			// Translate along +X axis
			translate[0] += 2.0;
			shiftY += 2;
			break;

		case 's':			// Translate along -Y axis
			translate[1] += -2.0;
			break;

		case 'L':			// Draw Lagrange Curve
			isLagrange = true;
			break;

		case 'b':			// Draw Beizer Curve 
			isBezier = true;
			break;

		case 'v':			// Adding Point Enabled
			bTakepoint = true;
			bDeletepoint = false;
			break;

		case 'c':			// Deleting Point Enabled
			bTakepoint = false;
			bDeletepoint = true;
			break;

		case 'q':			
			bTakepoint = false;
			bDeletepoint = false;
			bCalDist = true;
			break;

		case 27:  			// Escape Key
			exit(0);
			break;
      
		default:
			break;
	}
}

// Function for Mouse Events
void onMouseClick(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 		// if Left mouse button is pressed down
	{
		if (bTakepoint) 					// if adding point is enabled by pressing 'v'
		{
			recordPoint (x, y);				// Record Point Function
		}
   	}
   	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 	// if Right mouse button is pressed down
   	{
		if (bDeletepoint) 					// if deleting point is enabled by pressing 'c'
		{
			removePoint (x, y);				// Remove Point Function
		}
		else if (bCalDist) 					// if Distance Calculation is enabled by pressing 'q'
		{
			if (distPointCount == 0) 
			{
				px1 = x;
				py1 = y;
				distPointCount++;
			}
			else 
			{
				px2 = x;
				py2 = y;
				distPointCount++;
         		}
      		}
   	}
}

