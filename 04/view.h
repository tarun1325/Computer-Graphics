/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	view.h
*/
#include "FastTrackball.h"

// Class View
class View
{
	static Trackball trackball;						// For Trackball Rotation
	public:
		static float Position[3];					// Camera Position Vector
		static float transx, transy, transz;				// Translation Variables
		static float  scale, angle;					// Rotation and Scaling Variables
		static int enableBox;						// To Enable Bounding Box
		static int enableTexture;					// To Enable Texture
		static int enableAxis;
		static int enableSpot;
		static int enableHeadLight;
		static int enableLight;
		static void initRendering();					// Initialize Rendering Parameters
		static void handleResize(int, int);				// Window Resize Function
		static void drawScene();					// Display/Rendering Function
		static void rotate(float x1, float y1, float x2, float y2);	// Rotate Function
};
