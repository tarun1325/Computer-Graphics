/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 05 - Scene Graph with Animation
	Email : 	Tarun.Jain@iiitb.org
	File Name:	view.h
*/


// Class View
class View
{
	public:

		static int enableBox;						// To Enable Bounding Box
		static int enableAxis;						// To Enable/Disable Axis
		static int enableLight;						// To Enable/Disable All Lights
		static int camNo;						// Current Camera's Number
		static int maxCam;						// Maximum Number of Camera in Scene
		static int enableHeadLight;
		static int enableSpot;						// To Enable/Disable Spot
		static int enableTexture;					// To Enable/Disable  Texture
		
		// Member Functions
		static void initRendering();					// Initialize Rendering Parameters
		static void handleResize(int, int);				// Window Resize Function
		static void drawScene();					// Display/Rendering Function
};

