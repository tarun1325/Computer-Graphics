/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	model.h
*/
// Header Files
#include "imageloader.h"
// Macros
#define MAX_OBJECTS 	6					// Maximum Allowed No. of Object

// Global Variables
extern int object_count;					// No. of Objects in Scene

// Class to Store Point
class Point
{
	private:
		double x;					// X - Coordinate of Point
		double y;					// Y - Coordinate of Point
		double z;					// Z - Coordinate of Point
	public:
		double getter(int i);				// Get 'i'th Coordinate of Point
		void setter_vertex( int i , double value);	// Set 'i'th Coordinate of Point to 'value'
};

// Class to Store Object
class Object
{
	public:
		int obj_nov;					// No. of Vertices
		int obj_nof;					// No. of Faces
		float max[3];					// Storing maximum value for x,y,z coordinates
		float min[3];					// Storing minimum value for x,y,z coordinates
		float 	leftX, 					// Extreme Vertex in Negative X-axis
			rightX, 				// Extreme Vertex in  Positive X-axis
			topY, 					// Extreme Vertex in  Positive Y-axis
			bottomY, 				// Extreme Vertex in Negative Y-axis
			nearZ, 					// Extreme Vertex in Negative Z-axis
			farZ;					// Extreme Vertex in  Positive Z-axis
		Point *vertices;				// All Vertices in Object
		Point *faces;					// All Faces in Object
		Point *normals;					// Normals of All Faces in Object
}extern obj[ MAX_OBJECTS];					// Array to Store Object

// Class Texture
class Texture
{
	public:
	GLuint tex; 						// ID of the texture
	Image *image;						// Image Loaded	
	GLuint loadTexture(Image* image);			// Load Texture from Image
	void callToTexture( int);				// Texture Loading Function
}extern texture[MAX_OBJECTS];					// Objects to Store Texture
/* 6Th Object as Floor */

// Class Model
class Model
{
	public:
		int read( char*, int);				// Read Object From Ply File
		void initNormals( int);				// Find Normals for Each Face of Object
		void drawAxis();				// Draw Axis
		void drawObject( int);				// Draw Object
		void drawBox( int);				// Draw Bounding Box
		void drawFloor();				// Draw Floor
		void drawFire();				// Draw Fire on Lamp
		void neutralize( int);			// Scaling Objects
};

