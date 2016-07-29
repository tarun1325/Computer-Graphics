/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 05 - Scene Graph with Animation
	Email : 	Tarun.Jain@iiitb.org
	File Name:	controller.cpp
*/

// Header Files
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "rply.h"
#include "rplyfile.h"

// Global Variables
extern Model model;			// Model Class Object
extern View view;			// View Class Object
extern Controller controller;		// Controller Class Object
int Controller::mState = UP;		// Initial Mouse State
int Controller::oldX = -13;		// Initial Old X Coordinate
int Controller::oldY = -13;		// Initial Old Y Coordinate

float enableAmb = 1;
float track_position[3];		// Temporary Variable
extern int winX;			// Window's Width
extern int winY;			// Window's Height


float speed_A = 0.0, speed_C = 0.0;	// To Control animation speed


float cam2[] = { 0.0, 1.5, -12.0};	// Position of Camera 2
float cam3[] = {0.0, 1.0, 1.0};		// Position of Camera 3
float cam4[] = {10.0, 10.0, 1.0};	// Position of Camera 4	


// Render the Scene
void Controller :: renderScene()
{
	// Lighting
	controller.lighting();

	// Spot Light Indicator
	glColor3f(1,1,1);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(20);
	glBegin(GL_POINTS);
		glVertex3f(0, 2, 0);
	glEnd();
	

	//Setting Camera
	if( view.camNo == 1)
		controller.setCamera( controller.getTrackball() );		// Set Camera According to Mouse
	else if( view.camNo == 2)
		controller.setCamera( cam2);
	else if( view.camNo == 3)
		controller.setCamera( cam3);
	else if( view.camNo == 4)
		controller.setCamera( cam4);
		
	// Draw Axis
	if( view.enableAxis == 1)
		model.drawAxis();
	
	// Draw Floor
	model.drawFloor();

	// Rendering Root Node of Scene Graph
	controller.renderObject(0);
	
	// Render Individual Object 'C'
	if( obj[1].childs == NULL)
	{
		glTranslatef( obj[2].transx, obj[2].transy, obj[2].transz );
		glRotatef(-90, 1, 0, 0);
		glRotatef(90, 0,0,1);
		if( view.enableBox == 1)
				model.drawBox(2);
		glColor3f( obj[2].color[0], obj[2].color[1], obj[2].color[2]);
		model.drawObject(2);
	}
}


// Set Camera Positions
void Controller :: setCamera( float track_position[])
{
	// Updating New Camera Positions
	model.Position[0] = track_position[0];
	model.Position[1] = track_position[1];
	model.Position[2] = track_position[2];
	
	// Place Camera at New Position
	gluLookAt( model.Position[0], model.Position[1], model.Position[2], model.Center[0], model.Center[1], model.Center[2], 0, 1, 0);
}

// Initializing Value for a Object - Color, Textures
void Controller :: initObject( int x)
{
	// Color Assignment to Object
	int l = 1, m = 1, n = 1;
	static int count_color = 0;
	
	// To Assign Color of Your Choice to Each Object
	/*
	if( x%3 == 0)
		{ l = 1; m = 0; n =0;}
	else if(x%3 == 1)
		{ l = 0; m = 1; n =0;}
	else
		{ l = 0; m = 0; n =1;}
	*/
	
	// Set Color
	obj[x].color[0] = l;
	obj[x].color[1] = m;
	obj[x].color[2] = n;
	
	// Set ID of Object
	obj[x].id = x;
	
	// Set Initial Transformation to Zero
	if( x == 0)					// For Object 0
	{
		obj[x].transx = 0;
		obj[x].transy = 0;
		obj[x].transz = 0;
	}
	else if ( x == 1)				// Separation Factor for Object 1
							// Due to Object Rotation - Axis Changed - Specific to Plane
							// x = y axis;		y = z axis;		z = x axis;
	{
		obj[x].transx = 1.5;
		obj[x].transy = 0;
		obj[x].transz = 0;
	}
	else if( x == 2 )				// Separation Factor for Object 2 
							// Normal Coordinate System since initially it is not child of root
	{
		obj[x].transx = -3;
		obj[x].transy = 0.5;
		obj[x].transz = -3;
	
	}
	
	obj[x].angle =0;				// Setting Initial Rotate Angle for all Objects
	
	// Texture Loading
	char img[20];
	if( x == 0)
		strcpy(img, "images/1.bmp");
	if( x == 1)
		strcpy(img, "images/2.bmp");
	if( x ==2)
		strcpy(img, "images/3.bmp");
	
	// Loading Specified Image (BMP format)
	obj[x].tex.image = loadBMP( img );
	// Converting Image to Texture and Creating Texture Id
	obj[x].tex.texID = obj[x].tex.loadTexture(obj[x].tex.image);
}

// Function to Animate the Objects
void Controller :: animate()
{
	root = &obj[0];					// Making Root
	static int count = 0;				// Temporary Variable Used for Going away and Coming back

	float x,y,z;					// Temporaries to store root's current Position
	x = root -> transx;
	y = root -> transy;
	z = root -> transz;
	
	float distance_to_travel = -10;			// Distance away from initial Distance
	static int makeonce = 0;			// To Make Child Once-  For Manual Jump Off
	static int runonce = 0;				// To run Remove Child only once to avoid inconsistency 
	
	// Animating Entire Scene by Root Node
	if( z > distance_to_travel  && z < 1)		// If root object between initial and final point
	{	
		if (count == 0)				// If Object is Going Away
		{
			if(view.camNo == 3)
			{
				cam3[0] = (( obj[0].leftX + obj[0].rightX ) / 2 ) + obj[0].transx;
				cam3[1] = (( obj[0].topY + obj[0].bottomY ) / 2 )  + obj[0].transy;
				cam3[2] = obj[0].nearZ + obj[0].transz;
				model.Center[0] = 0.0;
				model.Center[1] += 0.05 ;
				model.Center[2] = -12.0;
			}
			else
			{
				model.Center[0] = 0.0;
				model.Center[1] = 0.0;
				model.Center[2] = 0.0;			
			}
			z -= (0.1 + speed_A);			// Move it More far from Center
			if( y > 0 && makeonce == 0)			// If Object Started to Fly
			{
				makeonce = 1;
				
				if(!(obj[1].childs == &obj[2]))
				{
					// Make 3rd Object as Child of 2nd Object
					obj[1].childs = &obj[2];
					// Remove the Old Position of 3rd Object bcoz it is moving with its Parent
					obj[2].transx = 1;	// Separation from parent Object
					obj[2].transy = 0;
					obj[2].transz = 0;
				}
			}
			if( z < -3)			// If Object Started to Take off
			{	
				y += 0.05;		// Elevate it
				z -= (0.1 + speed_A) ;	// Move it More Far - Speed Increased
			}
		}
		else if(count != 0)			// If Object is Coming Back
		{
		
			if(view.camNo == 3)
			{
				cam3[0] = (( obj[0].leftX + obj[0].rightX ) / 2 ) + obj[0].transx;
				cam3[1] = (( obj[0].topY + obj[0].bottomY ) / 2 )  + obj[0].transy;
				cam3[2] = obj[0].farZ  + obj[0].transz;
				model.Center[0] = 0.0;
				model.Center[1] -= 0.05;
				model.Center[2] = 5.0;
			}
			else
			{
				model.Center[0] = 0.0;
				model.Center[1] = 0.0;
				model.Center[2] = 0.0;			
			}
			
			z += (0.1 + speed_A);		// Bring it Closer to Center
			if( y < 0.2 && runonce == 0)	// Once Landing of Object Begins
			{
				runonce = 1;		// Do this only once - so that Object 3 becomes Independent
				if(obj[1].childs == &obj[2])
				{
					obj[1].childs = NULL;	// To Remove Child Object 3 from parent Object 2
					obj[2].transx = 3;	// Set Position so that it can move Independently
					obj[2].transy = 0.5;
					obj[2].transz = -3;
				}
			}
			if(z < -3)			// Until Landing Point is approached
			{
				y -= 0.05;		// Continue gradually decrease in height
				z += (0.1 + speed_A);	// Bring Object Closer to Center
			}
		}
	}
	else if( z < distance_to_travel )		// If Final Point from Center is Reached
	{
		z += 0.2;				// Bring Object Back in Range
		count = 1;				// Change Count -To Avoid Stucking- Starts Coming Back
		root -> angle = 180;			// Rotate Objects Face towards center
		root -> transx -= 2;			// Adjustment for Distortion Bcoz of Rotation of Root
	}
	else
	{
		z = 0.9;				// For Further Rounds - Set Inital Start - To Avoid Stucking
		y -= 0.05;				// Bring Objects Down to Land - Bcoz of Manual Change in Z (Sync)
		count = 0;				// To Allow Going Away Again
		root -> angle = 0;			// Setting Angle to Change Object's Orientation
		root -> transx += 2;			// Reverse of Adjustment for Distortion Bcoz of Rotation of Root
		runonce = 0;				// Reallow to make/remove child in next iteration
		makeonce = 0;
		obj[2].transx = -3;			// Resetting Individual Object's Position
		obj[2].transy = 0.5;
		obj[2].transz = -3;
		speed_A = 0.0;				// Reset Speed in Next Iteration
		speed_C = 0.0;
		if(obj[1].childs == &obj[2])		// Reset Child on New Iteration
			obj[1].childs = NULL;
	}
	
	// Updating Changes to Root Node's Actual Value
	root -> transy = y;
	root -> transz = z;
	
	// Individual Animation of Object 2 when It is not Child in Root's Node
	if( obj[1].childs == NULL)
	{
		obj[2].transx += (0.05 + speed_C);			// Move it horizontally
	}
}

// To Set the Animation Relationship - (Static Relation for Now)
void Controller :: setRelations()
{
	root = &obj[0];					// Setting Object one as Root
	obj[0].childs = &obj[1];			// Make first Object Child of zeroth object
}

// Timer Function
void Controller :: update(int value) 
{
	// Call Animate
	controller.animate();
	//Tell GLUT that the display has changed
	glutPostRedisplay();
	//Tell GLUT to call update again in 1 milliseconds
	glutTimerFunc(100, update, 0);
}

// Render Objects
void Controller :: renderObject( int x)
{
	
	Object *traverse = obj[x].childs;		// Temporary Traversal Variable
	glPushMatrix();					// To Make Change to a Certain Things, Push
	
		if( x == 0)
		{
			// Root's Translations
			glTranslatef( obj[x].transx, obj[x].transy, obj[x].transz);
			// Initialize Scene - To Do Initial Transformation and Placing of Objects
			controller.initScene();
			// Root's Rotation
			glRotatef( obj[x].angle, 0,0,1);
		}
		else
		{
			// Individual Object's Transformation - (Separations from Root)
			glTranslatef( obj[x].transx, obj[x].transy, obj[x].transz);
		}
		
		// Draw Bounding Box
		if( view.enableBox == 1)
			model.drawBox(x);
		
		// Initializing Object Display Parameters - Color
		glColor3f( obj[x].color[0], obj[x].color[1], obj[x].color[2] );
		
		// Render Object
		model.drawObject(x);

		// Check for Child of Object
		while( traverse != NULL)
		{
			// Render Child Object
			controller.renderObject(obj[x].childs -> id);
			// Traverse to Next Object in Childs List
			traverse = traverse -> childs;
		}
	glPopMatrix();								// After You are done with those Things, Pop
}

void Controller :: lighting()
{
	if( view.enableLight == 1)
	{
		glEnable(GL_LIGHTING); 							//Enable lighting
		glEnable(GL_LIGHT2);
	
		if( enableAmb == 0)
		{
			//Add ambient light
			GLfloat ambientColor[] = {0.50, 0.50, 0.50, 1.0f}; 			//Color (0.2, 0.2, 0.2)
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		}
	    	
	    	if(view.enableHeadLight == 1)
	    	{
			glEnable(GL_LIGHT0);
			// Spot Light attached to Camera - Head Light
			GLfloat light_position0[] = { model.Position[0], model.Position[1], model.Position[2], 1.0 };
			GLfloat spot_position0[] = { -model.Position[0], -model.Position[1], -model.Position[2] };
		    	GLfloat lightColor0[] = {1.0,1.0,1.0, 1.0f};
		    	GLfloat spec_light0[] = { 1,1,1,1};
		       	glLightfv(GL_LIGHT0, GL_SPECULAR, spec_light0);
		    	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
		    	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0);
		    	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_position0);
		}	    	
	    	
	    	
		// Spot Light on Object C
		GLfloat light_position2[] = {0 , 20, 0, 1.0f };
		GLfloat spot_position2[3];
		if( obj[1].childs == NULL)
		{
			spot_position2[0] = obj[2].transx ;
			spot_position2[1] = obj[2].transy - 20;
			spot_position2[2] = obj[2].transz - 3;

		}
		else
		{
			spot_position2[0] = obj[0].transx ;
			spot_position2[1] = obj[0].transy - 15;
			spot_position2[2] = obj[0].transz - 3;
		}
	    	GLfloat lightColor2[] = {1.0,1.0,1.0, 1.0f};
	    	GLfloat spec_light2[] = { 1,1,1,1};
	       	glLightfv(GL_LIGHT2, GL_SPECULAR, spec_light2);
	    	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5.0);
	    	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
	    	glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spot_position2);
	    	
	}
	else
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT2);		
		//glDisable(GL_LIGHTING);			// Do this if you want no Lighting concept
	}
}

// Initialize Scene
void Controller :: initScene()
{
	glTranslatef(1, 0.3, 0);				// Object's Translation
	glRotatef(-90, 1,0,0);					// Object's Rotation
	glRotatef(180, 0, 0 ,1);
}


// Get Calculated TrackBall Positions
float* Controller :: getTrackball()
{
	static float rotation_transform[4][4];					// Rotation Matrix Variable
	
	/* ---Camera Positioning--- */
	// Initial Camera Positions
	model.Position[0] = 0.0;
	model.Position[1] = 1.0;
	model.Position[2] = 4.0;

	model.trackball.rotationMatrix( rotation_transform );				// Filling Rotation Matrix by using TrackBall

	// Multiplying Position Matrix with Rotation Matrix
	track_position[0] = model.Position[0] * rotation_transform[0][0] + model.Position[1] * rotation_transform[0][1] + model.Position[2] * rotation_transform[0][2] 
	+ rotation_transform[0][3];
		
	track_position[1] = model.Position[0] * rotation_transform[1][0] + model.Position[1] * rotation_transform[1][1] + model.Position[2] * rotation_transform[1][2] 
	+ rotation_transform[1][3];
		
	track_position[2] = model.Position[0] * rotation_transform[2][0] + model.Position[1] * rotation_transform[2][1] + model.Position[2] * rotation_transform[2][2] 
	+ rotation_transform[2][3];

	return track_position;
}

// Trackball Rotate Function
void Controller :: trackball_rotate(float oldx, float oldy, float x, float y)
{
	// Call Trackball Rotate
	model.trackball.rotate((2.0*oldx - winX)/(float)winX,
			(winY - 2.0*oldy)/(float)winY,
			(2.0*x - winX)/(float)winX,
			(winY - 2.0*y)/(float)winY);
}

// Special Keyboard Keys Function
void Controller::SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)				// Left Arrow Key
	{
		// Increase C's Speed
		speed_C += 0.1;
	}
	else if (key == GLUT_KEY_UP)				// Up Arrow Key
	{
		// Increase A's Speed
		speed_A += 0.1;
	}
	else if (key == GLUT_KEY_RIGHT)				// Right Arrow Key
	{
		// Decrease C's Speed
		speed_C -= 0.1;
	}
	else if (key == GLUT_KEY_DOWN)				// Down Arrow Key
	{
		// Decrease A's Speed
		speed_A -= 0.1;
	}
	// Re-display the Scene
	glutPostRedisplay();
}

// Keyboard Function
void Controller::keyboard(unsigned char key, int x, int y)
{
	// Key = Pressed Button on Keyboard
	switch(key)
	{
		// To Change Camera
		case 'c':
		case 'C':
			view.camNo++;
			if(view.camNo > view.maxCam) 
				view.camNo = 1;
			break;
		// Enable or Disable Bounding Box - Press 'b'
		case 'b':
		case 'B':
			if(view.enableBox == 1) 
				view.enableBox = 0; 
			else
				view.enableBox = 1;
			break;
		
		// Enable or Disable Entire Lighting - Press 'l'
		case 'l':
		case 'L':
			if(view.enableLight == 1) 
				view.enableLight = 0; 
			else
				view.enableLight = 1;
			break;
		case 'p':
		case 'P':
			if(enableAmb == 1) 
				enableAmb = 0; 
			else
				enableAmb = 1;
			break;
		case 'h':
		case 'H':
			if(view.enableHeadLight == 1) 
			{
				glDisable(GL_LIGHT0);
				view.enableHeadLight = 0; 
			}
			else
			{
				glEnable(GL_LIGHT0);
				view.enableHeadLight = 1;
			}
			break;
		case 'j':
		case 'J':
			if (obj[1].childs == &obj[2])
			{
				obj[1].childs = NULL;		// To Remove Child Object 3 from parent Object 2
				obj[2].transx = obj[0].transx;	// Set Position so that it can move Independently
				obj[2].transy = obj[0].transy;
				obj[2].transz = obj[0].transz;
			}
			//Again Make the Child
			else if(!(obj[1].childs == &obj[2]))
			{
				// Make 3rd Object as Child of 2nd Object
				obj[1].childs = &obj[2];
				// Remove the Old Position of 3rd Object bcoz it is moving with its Parent
				obj[2].transx = 1;	// Separation from parent Object
				obj[2].transy = 0;
				obj[2].transz = 0;
			}
			break;
		// Enable or Disable Texture - Press 't'
		case 't':
		case 'T':
			if(view.enableTexture == 1) 
				view.enableTexture = 0; 
			else
				view.enableTexture = 1;
			break;

		// Enable or Disable Axis - Press 'a'
		case 'a':
		case 'A':
			if(view.enableAxis == 1) 
				view.enableAxis = 0; 
			else
				view.enableAxis = 1;
			break;
		// To Exit - Press 'ESC'
		case 27:
			std::cout<<"Quiting ..."<<std::endl;
			exit(-1);
			break;
	}
	
	// Render the Scene with Updated Changes
	glutPostRedisplay();
}

// Mouse Motion Function
void Controller::glutMotion(int x, int y)
{
	// When Mouse Button is Pressed and Mouse Dragged
	if (mState == DOWN)
    	{
    		// Rotate the Camera Through TrackBall
		trackball_rotate(oldX, oldY, x, y);
		// Re-display Scene
		glutPostRedisplay();
    	}
    	// Update Old Co-ordinates to Current Coordinates after Rotation
   	oldX = x;
    	oldY = y;
}

// Mouse Function
void Controller::glutMouse(int button, int state, int x, int y)
{
	// When Mouse Button Pressed
	if(state == GLUT_DOWN)
    	{
    		// Check the button pressed
        	switch(button)
        	{
        		// Right Button pressed
        	    case GLUT_RIGHT_BUTTON:
			oldX = x;
        		oldY = y;
        	        break;
        	        // Left Button pressed
        	    case GLUT_LEFT_BUTTON:
			mState = DOWN;				// Update Mouse State when Left Button pressed
        	        oldX = x;
        	        oldY = y;
        		break;
        	}	
    	}
    	// When Mouse Button is Not pressed or released
    	else if (state == GLUT_UP)
    	{
        	mState = UP;					// Update Mouse State
        	switch(button)
        	{
        	    case GLUT_RIGHT_BUTTON:
			oldX = x;
        	        oldY = y;
        	        break;
        	    case GLUT_LEFT_BUTTON:
			trackball_rotate(0, 0, 0, 0);		// Rotation Stops - Reinitialize it
			break;
        	}
       	 	// Re-display the Scene      
       		glutPostRedisplay();
	}
}

// Run Function To Demonstrate Project
void Controller :: run( char* argv[], int number)
			// Name of Ply Files, No. of Ply Files
{
	// For Each Ply File
	for(int k = 2; k <= number; k++)
	{
		// Reading Ply File : Assigning Object Number
		model.read(argv[k], k - 2);
		// Scaling Object to Fit the Scene
		model.neutralize( k-2);
		// Calculating Normals for Object
		model.initNormals( k-2);
	}
	
	view.initRendering(); //Initialize rendering
	//Set handler function for drawing
	glutDisplayFunc(view.drawScene);
	//Set handler function for window resize
	glutReshapeFunc(view.handleResize);
	//Set handler function for keypress
	glutKeyboardFunc(keyboard);
	//Set handler function for Special keypress
	glutSpecialFunc(SpecialKeys);
	//Set handler function for Mouse Motion
	glutMotionFunc(glutMotion);
	//Set handler function for Mouse
	glutMouseFunc(glutMouse);
	// Set handler function for Timer
	glutTimerFunc(100, update, 0);
	//Start the main loop
	glutMainLoop(); 
}
