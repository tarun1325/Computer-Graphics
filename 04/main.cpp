/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	main.cpp
*/

// Header Files
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "model.h"
#include "view.h"
#include "controller.h"
#include "rply.h"
#include "rplyfile.h"

// Namespace
using namespace std;

// Global Variables
int winX = 1200;		// Window's Width
int winY = 1200;		// Window's Height
Model model;			// Model Class Object
View view;			// View Class Object

// Main Function
int main(int argc,char* argv[])
{
	// Checking the Number of Arguments for Ply File 
	if (argc < 3 )
	{
		cout<<"Main.cpp : Enter Atleast 1 Ply File Name>"<<endl;
		exit(-1);
	}
	
	// Controller Class Object
	Controller controller;
	// Initialize GLUT
	glutInit( &argc, argv);
	// Setting Display Mode - Double Buffer / Depth Buffer / RGBA Buffer
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	// Setting Window Size
	glutInitWindowSize( winX, winY);
	// Setting Window Initial Position
	glutInitWindowPosition( 50, 50);
	//Create the window
	glutCreateWindow( argv[1]);
	
	// Run The Project
	controller.run( argv, argc-1);
	return 0;	
}

