/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 05 - Scene Graph with Animation
	Email : 	Tarun.Jain@iiitb.org
	File Name:	controller.h
*/
#include "FastTrackball.h"

// Class Controller
class Controller
{
	static int mState;							// To Store Mouse State - UP/DOWN
	static int oldX, oldY;							// To Store Mouse Coordinates before Rotation Begins
	enum {UP = 1, DOWN, };							// Mouse State Values

	public:
		void run(char**, int);						// Run Project
		static void SpecialKeys(int key, int x, int y);			// For Special Keys Actions
		static void glutMotion(int x, int y);				// For Mouse Motion Actions
		static void glutMouse(int button, int state, int x, int y);	// For Mouse Actions
		static void keyboard(unsigned char key, int x, int y);		// For Keyboard Actions
		static void update(int value);					// Timer Function
		static void setCamera( float []);				// To Update Camera Position
		static float* getTrackball();					// To Get Trackball positions
		static void trackball_rotate(float x1, float y1, float x2, float y2);	// Rotate Function
		static void renderScene();					// Renders Entire Scene Graph
		static void renderObject( int x);				// Renders Individual Scene Nodes
		static void initObject( int x);					// Initialize a Object with Parameters
		static void lighting();						// Set Lighting in the Scene
		static void setRelations();					// Set Graph Relations
		static void initScene();					// Set Initial Positions of Objects
		static void animate();						// To Animate the Scene
};

