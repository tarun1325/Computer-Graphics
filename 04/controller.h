/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	controller.h
*/

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
		static void update(int value);		// Timer Function
};
