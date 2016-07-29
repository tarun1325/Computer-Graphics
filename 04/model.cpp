/*
	Author: 	Tarun Jain
	Roll Number: 	MT2015120
	Project: 	Assignment 04 - Lighting Models + Texture Mapping + Refining MVC
	Email : 	Tarun.Jain@iiitb.org
	File Name:	model.cpp
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
int count_vertex;			// Temporary Variable
int count_face;				// Temporary Variable
extern int winX;			// Window's Width
extern int winY;			// Window's Height
Object obj[ MAX_OBJECTS];		// Array to Store Objects
Texture texture[MAX_OBJECTS];		// Array to Store Texture
int object_count = 0;			// No. of Objects in Scene
int obj_mapsize[MAX_OBJECTS] = {30,30,30,30,1};

// Getter Function
double Point :: getter( int i)
{
	if( i == 0)
		return x;
	if( i == 1)
		return y;
	if( i == 2)
		return z;
}

// Setter_vertex Function
void Point :: setter_vertex(int i, double value)
{
	if( i == 0)
		x = value;
	if( i == 1)
		y = value;
	if( i == 2)
		z = value;
}

// Callback Function for Vertex - "RPLY LIBRARY BY DIEGO NEHAB"
int vertex_cb(p_ply_argument argument) 
{
	// Temporary Variables
	static int index = 0;
	long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	double temp = ply_get_argument_value(argument);
	
	// Finding Extreme Coordinates
	if( index == 0 )
	{
		if( obj[object_count].leftX > temp)
			obj[object_count].leftX = temp;
		if( obj[object_count].rightX < temp)
			obj[object_count].rightX = temp;
	}
	if( index == 1 )
	{
		if( obj[object_count].topY < temp)
			obj[object_count].topY = temp;
		if( obj[object_count].bottomY > temp)
			obj[object_count].bottomY = temp;
	}
	if( index == 2 )
	{
		if( obj[object_count].nearZ > temp)
			obj[object_count].nearZ = temp;
		if( obj[object_count].farZ < temp)
			obj[object_count].farZ = temp;
	}
	
	// Finding Maximum and Minimum Values for x,y,z coordinates
	if( index == 0 )
	{
		if(!count_vertex)
		{
			obj[object_count].max[0] = temp;
			obj[object_count].min[0] = temp;
		}
		if( obj[object_count].max[0] < temp)
			obj[object_count].max[0] = temp;
		if( obj[object_count].min[0] > temp)
			obj[object_count].min[0] = temp;
	}
	if( index == 1 )
	{
		if(!count_vertex)
		{
			obj[object_count].max[1] = temp;
			obj[object_count].min[1] = temp;
		}
		if( obj[object_count].max[1] < temp)
			obj[object_count].max[1] = temp;
		if( obj[object_count].min[1] > temp)
			obj[object_count].min[1] = temp;
	}
	if( index == 2 )
	{
		if(!count_vertex)
		{
			obj[object_count].max[2] = temp;
			obj[object_count].min[2] = temp;
		}
		if( obj[object_count].max[2] < temp)
			obj[object_count].max[2] = temp;
		if( obj[object_count].min[2] > temp)
			obj[object_count].min[2] = temp;
	}
	
	// Reading Value of Vertex
	obj[object_count].vertices[count_vertex].setter_vertex( index++, temp); 
	
	if (eol) 
	{
		index = 0;
		count_vertex++;
	}
	return 1;
}

// Callback Function for Faces - "RPLY LIBRARY BY DIEGO NEHAB"
int face_cb(p_ply_argument argument) 
{
	// Temporary Variables
	long length, value_index;
	static int index = 0;
	ply_get_argument_property(argument, NULL, &length, &value_index);
	double temp;
	
	// Reading Face Vertices
	switch (value_index) 
	{
		case 0:
	        case 1: 
			temp = ply_get_argument_value(argument);
	        	obj[object_count].faces[ count_face].setter_vertex( index++, temp);
        		break;
	        case 2:
			temp = ply_get_argument_value(argument);
	        	obj[object_count].faces[ count_face].setter_vertex( index++, temp);
	        	index = 0;
	        	count_face++;
        		break;
		default:
			break;
    	}
    	return 1;
}
int Model :: read( char *name, int x) 
{
	// Resetting Temporary Variables
	count_vertex = 0;
	count_face = 0;
	
	// Initializing Object Variables
	obj[object_count].leftX = winX /2;
	obj[object_count].rightX = -winX /2;
	obj[object_count].topY = -winY /2;
	obj[object_count].bottomY = winY /2;
	obj[object_count].nearZ = 1000.0;
	obj[object_count].farZ = -1000.0;
	
	// Temporary Variable
	long nvertices, ntriangles;
	
	// Open Ply File and Get Handle
	p_ply ply = ply_open(name, NULL, 0, NULL);
	
	// not a ply file
	if (!ply) 
		return 1;
	// Parse Header
	if (!ply_read_header(ply)) 
		return 1;

	// Read Element type and specified properties
	nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, 1);
	
	// Update No. of Vertices in Object
	obj[x].obj_nov = nvertices;

	// Read 2nd Element type and specified properties
	ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);

	// Update No. of Faces in Object	
	obj[x].obj_nof = ntriangles;
	
	// Getting Memory for Vertices, Faces, Normals
	obj[x].vertices = ( Point *) malloc ( sizeof(Point) * obj[x].obj_nov);
	obj[x].faces = ( Point *) malloc ( sizeof(Point) * obj[x].obj_nof);
	obj[x].normals = ( Point *) malloc ( sizeof(Point) * obj[x].obj_nof);
	
	// Read all vertices and faces
	if (!ply_read(ply)) 
		return 1;
		
	// Close Ply File
	ply_close(ply);
	
	// Increment Object Count for next Object, if any
	object_count++;
	return 0;
}

// Neutralizing Scaling Function
void Model :: neutralize( int x)
{

	float factor = obj[x].max[0];
	for(int k =1; k < 3; k++)
	{
		if( factor < obj[x].max[k] )
			factor = obj[x].max[k];
	}	
	for(int i = 0; i < obj[x].obj_nov; i++)
	{
		for(int j =0; j < 3; j++)
		{
			obj[x].vertices[i].setter_vertex(j, (obj[x].vertices[i].getter(j) / (factor)));
			//if( x == 4)
				//std::cout << obj[x].vertices[i].getter(j) << " ";
		}
	}
}

// Normal Function
void Model :: initNormals( int x)
{
	int i;
	double s[3], t[3], v[3], length;
	
	for( i = 0; i < obj[x].obj_nof; i++)
	{
	// Finding Vectors
	s[0] = obj[x].vertices[(int)obj[x].faces[i].getter(1)].getter(0) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(0);
	s[1] = obj[x].vertices[(int)obj[x].faces[i].getter(1)].getter(1) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(1);
	s[2] = obj[x].vertices[(int)obj[x].faces[i].getter(1)].getter(2) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(2);
	
	t[0] = obj[x].vertices[(int)obj[x].faces[i].getter(2)].getter(0) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(0);
	t[1] = obj[x].vertices[(int)obj[x].faces[i].getter(2)].getter(1) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(1);
	t[2] = obj[x].vertices[(int)obj[x].faces[i].getter(2)].getter(2) - obj[x].vertices[(int)obj[x].faces[i].getter(0)].getter(2);
		
	// Cross Product
	v[0] = s[1] * t[2] - t[1] * s[2]; 
	v[1] = s[2] * t[0] - t[2] * s[0];
	v[2] = s[0] * t[1] - t[0] * s[1];
		
	// Normalization Factor
	length = sqrt( ( v[0] * v[0] ) + (v[1] * v[1]) + (v[2] * v[2]) );
		
	obj[x].normals[i].setter_vertex(0 , (v[0] / length));
	obj[x].normals[i].setter_vertex(1 , (v[1] / length));
	obj[x].normals[i].setter_vertex(2 , (v[2] / length));
	}
}

// Load Texture from Image
GLuint Texture :: loadTexture(Image* image) 
{
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,                		//Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, 			//GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, 		//GL_UNSIGNED_BYTE, because pixels are stored
				                   		//as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

// Texture Loading Function
void Texture :: callToTexture( int x)
{
	char tex_obj[15];
	// Assigning Texture File for Different Object
	switch( x)
	{
		case 0:
			strcpy(tex_obj,"obj1.bmp");
			break;
		case 1:
			strcpy(tex_obj,"obj2.bmp");
			break;
		case 2:
			strcpy(tex_obj,"obj3.bmp");
			break;
		case 3:
			strcpy(tex_obj,"obj4.bmp");
			break;
		case 4:
			strcpy(tex_obj,"obj5.bmp");
			break;
	
		case 5:
			strcpy(tex_obj,"floor.bmp");
			break;
	}
	// Loading Specified Image (BMP format)
	texture[x].image = loadBMP(tex_obj);
	// Converting Image to Texture and Creating Texture Id
	tex = texture[x].loadTexture(texture[x].image);
}
// Rendering Reference Axis
void Model :: drawAxis()
{
	glBegin(GL_LINES);
		float axis = 2;
		//drawing x -axis
		glColor4f(0, 0, 1, 0);
		glVertex3f( axis, 0, 0);
		glVertex3f(-axis, 0, 0);
	
		//drawing y -axis
		glColor4f(0, 1, 0, 0);
		glVertex3f(0, axis, 0);
		glVertex3f(0, -axis,0);
		
		//drawing z -axis
		glColor4f(1, 0, 0, 0);
		glVertex3f(0, 0, axis);
		glVertex3f(0, 0, -axis);
		
		glColor3f(1.0,1.0,1.0);
	glEnd();
}

// Draw Floor
void Model :: drawFloor()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);						
	glBindTexture(GL_TEXTURE_2D, texture[5].tex);
	
	// Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	
	//glColor3f(1.0,1.0,0.0);

	glTranslatef( 0.0, 0.02, 0.0);		// Translating Floor
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glTranslatef( 0.0, -0.02, 0.0);		// Translating Back to avoid other distortion
	
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
// Draw Fire on Lamp
void Model :: drawFire()
{
	Texture fire;
	fire.image = loadBMP("fire.bmp");
	fire.tex = fire.loadTexture(fire.image);
	


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);						// Enable Texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);						
	
	glBindTexture(GL_TEXTURE_2D, fire.tex);				// Selecting Texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glRotatef(view.angle, 0, 1, 0);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(0.5,1.0);
		glVertex3f(0.0,0.15,0.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(0.02,0.09,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-0.02,.09,0.0);
		
		glTexCoord2f(0.5,1.0);
		glVertex3f(0.0,0.15,0.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(0.02,0.09,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(0.0,0.09,0.00);
		
		glTexCoord2f(0.5,1.0);
		glVertex3f(0.0,0.15,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-0.02,.09,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(0.0,0.09,0.0);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);		// Disable Texture
	glPopMatrix();
	
}

// Drawing Bounding Box
void Model :: drawBox( int x)
{
	glColor3f(1.0, 1.0, 0.0);
	// Getting Object's Extreme Coordinates
	float minx = obj[x].leftX;
	float maxx = obj[x].rightX;
	float maxy = obj[x].topY;
	float miny = obj[x].bottomY;
	float maxz = obj[x].farZ;
	float minz = obj[x].nearZ;
	

	// Drawing Bounding Box using Extreme Coordinates
	glBegin(GL_LINES);
		glVertex3f(minx, miny, minz);
		glVertex3f(maxx, miny, minz);
	
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, maxy, minz);
	
		glVertex3f(maxx, maxy, minz);
		glVertex3f(minx, maxy, minz);
	
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, miny, minz);
	
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(minx, miny, maxz);
		glVertex3f(maxx, miny, maxz);
	
		glVertex3f(maxx, miny, maxz);
		glVertex3f(maxx, maxy, maxz);
	
		glVertex3f(maxx, maxy, maxz);
		glVertex3f(minx, maxy, maxz);
	
		glVertex3f(minx, maxy, maxz);
		glVertex3f(minx, miny, maxz);
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(minx, miny, minz);
		glVertex3f(minx, miny, maxz);
	
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, maxz);
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(minx, maxy, minz);
		glVertex3f(minx, maxy, maxz);
	
		glVertex3f(maxx, maxy, minz);
		glVertex3f(maxx, maxy, maxz);

	glColor3f(1.0, 1.0, .0);
	glEnd();
	
}

// Draw Object
void Model :: drawObject(int x)
{
	glPushMatrix();
	glRotatef(view.angle, 0 , 1, 0);
	glColor3f(0.5450,0.2,0.0);
	if( x == 4)
		glColor3f(1.0,1.0,1.0);
	
	/*----Calculating Centroid----*/
	float centroid[3];
	centroid[0] = ( obj[x].max[0] + obj[x].min[0] ) / 2.0;
	centroid[1] = ( obj[x].max[1] + obj[x].min[1] ) / 2.0;
	centroid[2] = ( obj[x].max[2] + obj[x].min[2] ) / 2.0;	
	
	/*-----Spherical Co-ordinates-*/
	float s, r, phi;
	float a,b,c;
	
	float mag;
	/*----------------------------*/
	
	// Rendering All Faces of Object
	for(int n =0; n < obj[x].obj_nof; n++)
	{
		// Texture
		glEnable(GL_TEXTURE_2D);						// Enable Texture
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);						
		glBindTexture(GL_TEXTURE_2D, texture[x].tex);				// Selecting Texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Rendering Face Begins ...
		glBegin(GL_TRIANGLES);
		
		// Setting Normal for Face - Used in Lighting
		glNormal3f( obj[x].normals[n].getter(0),obj[x].normals[n].getter(1), obj[x].normals[n].getter(2) );
		int face_no = obj[x].faces[n].getter(0);

		if( view.enableTexture == 1)
		{
			// Cylindrical Mapping
			if( x < 4)
			{
				a =  obj[x].vertices[face_no].getter(0);
				b =  obj[x].vertices[face_no].getter(1);
				c =  obj[x].vertices[face_no].getter(2);
				
				s = b/obj[x].max[1];
				r = (atan2f(c, a)  + 3.14)/(2*3.14);
				
				glTexCoord2f( r, s);
				//glTexCoord2f(obj_mapsize[x] * a, obj_mapsize[x] * b  );
			}
			// Spherical Mapping
			else
			{
				a =  obj[x].vertices[face_no].getter(0) - centroid[0];
				b =  obj[x].vertices[face_no].getter(1) - centroid[1];
				c =  obj[x].vertices[face_no].getter(2) - centroid[2];
		
				mag =  sqrt( (a*a) + (b*b) + (c*c) );
				r = (float) (atan2f( c/mag, a/mag) / M_PI);
				phi =  (float) (asinf( b / mag ) / M_PI) - 0.5;
				glTexCoord2f(-r, phi);
			}

		}
		glVertex3f( obj[x].vertices[face_no].getter(0), obj[x].vertices[face_no].getter(1), obj[x].vertices[face_no].getter(2)); 
		
		face_no = obj[x].faces[n].getter(1);

		if( view.enableTexture == 1)
		{
			// Cylindrical Mapping
			if( x < 4)
			{
				a =  obj[x].vertices[face_no].getter(0);
				b =  obj[x].vertices[face_no].getter(1);
				c =  obj[x].vertices[face_no].getter(2);
				s = b/obj[x].max[1];
				r = (atan2f(c, a)  + 3.14)/(2*3.14);
				
				glTexCoord2f( r, s);
				//glTexCoord2f(obj_mapsize[x] * a, obj_mapsize[x] * b  );
			}
			// Spherical Mapping
			else
			{
				a =  obj[x].vertices[face_no].getter(0) - centroid[0];
				b =  obj[x].vertices[face_no].getter(1) - centroid[1];
				c =  obj[x].vertices[face_no].getter(2) - centroid[2];
		
				mag =  sqrt( (a*a) + (b*b) + (c*c) );
				r = (float) (atan2f( c/mag, a/mag) / M_PI);
				phi =  (float) (asinf( b / mag ) / M_PI) - 0.5;
				glTexCoord2f(-r, phi);
			}

		}
		glVertex3f( obj[x].vertices[face_no].getter(0), obj[x].vertices[face_no].getter(1), obj[x].vertices[face_no].getter(2)); 

		face_no = obj[x].faces[n].getter(2);

		if( view.enableTexture == 1)
		{
			// Cylindrical Mapping
			if( x < 4)
			{
				a =  obj[x].vertices[face_no].getter(0);
				b =  obj[x].vertices[face_no].getter(1);
				c =  obj[x].vertices[face_no].getter(2);
				s = b/obj[x].max[1];
				r = (atan2f(c, a)  + 3.14)/(2*3.14);
				
				glTexCoord2f( r, s);
				//glTexCoord2f(obj_mapsize[x] * a, obj_mapsize[x] * b  );
			}
			// Spherical Mapping
			else
			{
				a =  obj[x].vertices[face_no].getter(0) - centroid[0];
				b =  obj[x].vertices[face_no].getter(1) - centroid[1];
				c =  obj[x].vertices[face_no].getter(2) - centroid[2];
		
				mag =  sqrt( (a*a) + (b*b) + (c*c) );
				r = (float) (atan2f( c/mag, a/mag) / M_PI);
				phi =  (float) (asinf( b / mag ) / M_PI) - 0.5;
				glTexCoord2f(-r, phi);
			}

		}
		glVertex3f( obj[x].vertices[face_no].getter(0), obj[x].vertices[face_no].getter(1), obj[x].vertices[face_no].getter(2)); 

		glEnd();

		glDisable(GL_TEXTURE_2D);		// Disable Texture
	}
	glPopMatrix();
}
