/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 05 - Scene Graph with Animation
	Email : 	Tarun.Jain@iiitb.org
	File Name:	model.h
*/
// Header Files
#include "FastTrackball.h"
#include "imageloader.h"

// Macros
#define MAX_OBJECTS 	6					// Maximum Allowed No. of Object

// Global Variables
extern int object_count;					// No. of Objects in Scene

// Class Texture
class Texture
{
	public:
		GLuint texID; 						// ID of the texture
		Image *image;						// Image Loaded	
		GLuint loadTexture(Image* image);			// Load Texture from Image
};

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
		int id;						// ID assigned to Object
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
		
		Object *childs;					// Childs of This object
		Object *parent;					// Parent Object of this Object - Not to Be Used as of Now
		float color[3];					// Color of the Model
		float transx;					// Translation of object along x axis
		float transy;					// Translation of object along y axis
		float transz;					// Translation of object along z axis
		float angle;
		Texture tex;				// Texture For the Object

// TO DO:
// Render Function to update all the things:: Controller is doing a lot. make it less.
		
}extern obj[ MAX_OBJECTS], *root;			// Array to Store Object, Root of Scene




// Class Model
class Model
{
	public:
		static Trackball trackball;			// For Trackball Rotation
		static float Position[3];			// Camera Position
		static float Center[3];				// Center for Camera
		int read( char*, int);				// Read Object From Ply File
		void initNormals( int);				// Find Normals for Each Face of Object
		void drawAxis();				// Draw Axis
		void drawObject( int);				// Draw Object
		void drawBox( int);				// Draw Bounding Box
		void drawFloor();				// Draw Floor
		void neutralize( int);				// Scaling Objects
		
};

