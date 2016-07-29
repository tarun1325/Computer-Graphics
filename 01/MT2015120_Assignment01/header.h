/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 1 Computer Graphics: 2D Rendering.
	File: Header File.
*/

// Header Files
#include <stdlib.h>	// for Exit() function
#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>	// GL Library

using namespace std;

// Structure to store Point Co-ordinates, Alias name: Point
typedef struct point 
{
	int x;
	int y;
} Point;

// Global Variables
extern int win_width;			// Width of the Window
extern int win_height;			// Height of the Window
extern float zoom[3];			// Scaling Values
extern float rotAngle;		// For Rotation around Z-axis
extern int distPointCount;		// For the purpose Counting 2 distinct points
extern float translate[3];		// Calculating distance between 2 distinct points

extern bool isLagrange;			// Initially No Lagarange Curve
extern bool isBezier;			// Initially No Bezier Curve
extern bool bTakepoint;			// Start Adding Points
extern bool bDeletepoint;		// Start Deleting Points
extern int pointCount;			// Count no. of points
extern vector<Point> points;		// Vector to store points
extern int px1, px2, py1, py2;		// Co-ordinates of 2 Distinct points
extern int leftX;			// Leftmost Point on Window
extern int rightX;			// Rightmost Point on Window
extern bool bCalDist;			// Start Calculating Distance
extern int shiftX;			// Shifting value along X-Axis
extern int shiftY;			// Shifting value along Y-Axis
extern float distance;			// Distance

// Function Prototype
void initRendering();			// Initialize 3D Rendering
long double fact(int);
long double binCo( int, int);
float computeY (float, int);
void redrawPoints ();			// Redraw all points on any Change
void drawLagrange ();			// Function to Draw Lagrange Curve
void drawBezier ();			// Function to Draw Beizer Curve
void recordPoint (int, int);		// Function to Store the Clicked Point Co-ordinates in the Vector 'points'
void removePoint ( int, int);		// Function to Remove Clicked points
void drawScene();			// Function to Display on the Screen
void handleKeypress(unsigned char,int,int);// Function For Keyboard Inputs
void handleResize( int, int);		// Function to Resize the Window
void onMouseClick(int,int,int,int);	// Function for Mouse Events
