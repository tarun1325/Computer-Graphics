/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 1 Computer Graphics: 2D Rendering.
	File: Model.
*/

// Header Files
#include "header.h"

// Initializing Global Variables
int win_width = 500;			// Width of the Window
int win_height = 500;			// Height of the Window
float zoom[3] = {1.0f, 1.0f, 1.0f};		// Scaling Values
float rotAngle = 0.0f;			// For Rotation around Z-axis
int distPointCount = 0;			// For the purpose Counting 2 distinct points
float translate[3] = {0.0, 0.0, 0.0};		// Calculating distance between 2 distinct points
bool isLagrange = false;			// Initially No Lagarange Curve
bool isBezier = false;			// Initially No Bezier Curve
bool bTakepoint = false;			// Start Adding Points
bool bDeletepoint = false;			// Start Deleting Points
int pointCount = 0;				// Count no. of points
int leftX = 250;				// Leftmost Point on Window
int rightX = -250;				// Rightmost Point on Window
bool bCalDist = false;			// Start Calculating Distance
int shiftX = 0;				// Shifting value along X-Axis
int shiftY = 0;				// Shifting value along Y-Axis
float distance = 0.0;				// Distance
vector<Point> points;		// Vector to store points
int px1, px2, py1, py2;		// Co-ordinates of 2 Distinct points


// Initialize 3D Rendering
void initRendering()
{
	
}

long double fact(int x)
{
	long double fact=1;
	int p=1;
	if(x==0 || x==1)
	{
		return 1;
	}
	else
	{
		while(p<=x)
		{
			fact*=p;
			p++;
		}
	}
	return fact;
}

long double binCo( int f, int n)
{
	return (fact(n)/(fact(f)*fact(n-f)));
}

float computeY (float x, int count )
{

	float num = 1.0, den = 1.0;
	float sum = 0.0;

	for ( int i = 0; i < count; ++i )
	{
		num = den = 1.0;
		for ( int j = 0; j < count; ++j )
		{
			if ( j == i ) 
				continue;
			num = num * ( x - points[j].x );
		}

		for ( int j = 0; j < count; ++j )
		{
			if ( j == i ) 
				continue;
			den = den * ( points[i].x - points[j].x );
		}
		sum += num / den * points[i].y;
	}

	return sum;
}

// Function to Store the Clicked Point Co-ordinates in the Vector 'points'
void recordPoint (int x, int y) 
{

	// Translating Points according to Window
	int X = (GLfloat)x - 250;
	int Y = 250 - (GLfloat)y;

	// Creating a Space in the Vector 'points' by just Passing Structure type.
	// It will create space for int x and int y.
	points.push_back( Point());

	// In the Vector accessing the position of x and y for the current point and inserting their values.
	points[ pointCount].x = X;
	points[ pointCount++].y = Y;
	
	// Getting Leftmost Point
	if ( X >= -250 && X < leftX) 
	{
		leftX = X;
	}
	// Getting Rightmost Point
	if ( X <= 250 && X > rightX) 
	{
		rightX = X;
	}
}

// Function to Remove Clicked points
void removePoint ( int x, int y)
{
	int X = (GLfloat)x - 250;
	int Y = 250 - (GLfloat)y;
	int delP = 0;

	// Searching for Clicked point in the entire Vector 'points'
	for ( int i = 0; i < pointCount; i++)
	{
		// Checking x coordinate of selected point considering point size
		if ( X < points[i].x + 10 && X > points[i].x - 10) 
		{
			// Checking y coordinate of selected point considering point size
			if ( Y < points[i].y + 10 && Y > points[i].y - 10) 
			{
				delP = points[i].x;			// Getting Deleting point's X co-ordinate
				points.erase( points.begin() + i);	// Erasing Point values from the Vector
				pointCount--;				// Decrementing the Point Count
				break;					// out of current for loop
			}
		}
	}
	if ( pointCount > 0)
	{
		if ( delP == leftX)					// If leftmost point is deleted
		{
			leftX = 250;
			for ( int i = 0; i < pointCount; i++)		// Search the new Leftmost point by traversing entire Vector
			{
				X = points[i].x;
				if ( X >= -250 && X < leftX)
				{
					leftX = X;
				}
			}
		}
		else if ( delP == rightX) 				// If rightmost point is deleted
		{
			rightX = -250;
			for ( int i = 0; i < pointCount; i++)		// Search the new Rightmost point by traversing entire Vector
			{
				X = points[i].x;
				if ( X <= 250 && X > rightX)
				{
					rightX = X;
				}
			}
		}
	}
}

// Function to Resize the Window
void handleResize( int w, int h)
		// Resized Width = w, Resized Height = h
{
	glViewport( 0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective( 45.0, (double)w/(double)h, 1.0, 200.0);
	
	 if (w <= h) 
      gluOrtho2D (-250.0, 250.0, 
         -250.0*(GLfloat)h/(GLfloat)w, 250.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (-250.0*(GLfloat)w/(GLfloat)h, 
         250.0*(GLfloat)w/(GLfloat)h, -250.0, 250.0);
         
         glMatrixMode(GL_MODELVIEW);
         
	win_width = w;
	win_height = h;
}

// Main Function
int main( int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB);
	glutInitWindowSize( win_width, win_height);
	glutCreateWindow("TJ - 01 - Beizer | Lagarange Curves");
	initRendering(); //-  Not Needed Right now because this project is in 2D only. 
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}
