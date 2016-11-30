//
// Created by tadeze on 10/28/16.
//

#ifndef PROJECT4_MAIN_H
#define PROJECT4_MAIN_H

/*
Code is in the textureMapping function.
*/

#pragma region headers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include "glew.h"
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
//#include "bmptotexture.cpp"
#pragma endregion headers

//	This is a sample OpenGL / GLUT program
//
//	The objective is to draw a 3d object and change the color of the axes
//		with a glut menu
//
//	The left mouse button does rotation
//	The middle mouse button does scaling
//	The user interface allows:
//		1. The axes to be turned on and off
//		2. The color of the axes to be changed
//		3. Debugging to be turned on and off
//		4. Depth cueing to be turned on and off
//		5. The projection to be changed
//		6. The transformations to be reset
//		7. The program to quit
//
//	Author:			Joe Graphics

// NOTE: There are a lot of good reasons to use const variables instead
// of #define's.  However, Visual C++ does not allow a const variable
// to be used as an array size or as the case in a switch( ) statement.  So in
// the following, all constants are const variables except those which need to
// be array sizes or cases in switch( ) statements.  Those are #defines.


#pragma region declaration
// title of these windows:

const char *WINDOWTITLE = { "OpenGL / GLUT Sample -- Joe Graphics" };
const char *GLUITITLE   = { "User Interface Window" };


// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };


// the escape key:

#define ESCAPE		0x1b


// initial window size:

const int INIT_WINDOW_SIZE = { 600 };


// size of the box:

const float BOXSIZE = { 2.f };



// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };


// minimum allowable scale factor:

const float MINSCALE = { 0.05f };


// active mouse buttons (or them together):

const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };


// which projection:

enum Projections
{
    ORTHO,
    PERSP
};

// Distortion
enum Distortion{
    NOTEXTURE,
    TEXTUREIMAGE,
    DISTORTIONIMAGE
};
// which button:

enum ButtonVals
{
    RESET,
    QUIT
};


// window background color (rgba):

const GLfloat BACKCOLOR[ ] = { 0., 0., 0., 1. };


// line width for the axes:

const GLfloat AXES_WIDTH   = { 3. };


// the color numbers:
// this order must match the radio button order

enum Colors
{
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE,
    BLACK
};

char * ColorNames[ ] =
        {
                "Red",
                "Yellow",
                "Green",
                "Cyan",
                "Blue",
                "Magenta",
                "White",
                "Black"
        };


// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] =
        {
                { 1., 0., 0. },		// red
                { 1., 1., 0. },		// yellow
                { 0., 1., 0. },		// green
                { 0., 1., 1. },		// cyan
                { 0., 0., 1. },		// blue
                { 1., 0., 1. },		// magenta
                { 1., 1., 1. },		// white
                { 0., 0., 0. },		// black
        };


// fog parameters:

const GLfloat FOGCOLOR[4] = { .0, .0, .0, 1. };
const GLenum  FOGMODE     = { GL_LINEAR };
const GLfloat FOGDENSITY  = { 0.30f };
const GLfloat FOGSTART    = { 1.5 };
const GLfloat FOGEND      = { 4. };


// non-constant global variables:

int		ActiveButton;			// current button that is down
GLuint	AxesList;				// list to hold the axes
int		AxesOn;					// != 0 means to draw the axes
int		DebugOn;				// != 0 means to print debugging info
int		DepthCueOn;				// != 0 means to use intensity depth cueing
GLuint	BoxList;				// object display list
int		MainWindow;				// window id for main graphics window
float	Scale;					// scaling factor
int		WhichColor;				// index into Colors[ ]
int		WhichProjection;		// ORTHO or PERSP
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot;				// rotation angles in degrees
int Distortion;
bool Frozen = false;
bool Light0On,Light1On,Light2On;

#pragma endregion declaration
// function prototypes:
#pragma region func_prot
void    rotateObject();
void	Animate( );
void	Display( );
void	DoAxesMenu( int );
void	DoColorMenu( int );
void	DoDepthMenu( int );
void	DoDebugMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoDistortionMenu(int);
void    DoLight0Menu(int);
void    DoLight1Menu(int);
void    DoLight2Menu(int);

void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );
void	Axes( float );
void	HsvRgb( float[3], float [3] );
void textureMapping();
#pragma endregion func_prot
// main program:
//
#pragma region readbmp

int
ReadInt(FILE *fp)
{
    unsigned char b3, b2, b1, b0;
    b0 = fgetc(fp);
    b1 = fgetc(fp);
    b2 = fgetc(fp);
    b3 = fgetc(fp);
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}


short
ReadShort(FILE *fp)
{
    unsigned char b1, b0;
    b0 = fgetc(fp);
    b1 = fgetc(fp);
    return (b1 << 8) | b0;
}

struct bmfh
{
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} FileHeader;

struct bmih
{
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} InfoHeader;

const int birgb = { 0 };



///**
//** read a BMP file into a Texture:
//**/

unsigned char *
BmpToTexture(char *filename, int *width, int *height)
{

    int s, t, e;		// counters
    int numextra;		// # extra bytes each line in the file is padded with
    FILE *fp;
    unsigned char *texture;
    int nums, numt;
    unsigned char *tp;


    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open Bmp file '%s'\n", filename);
        return NULL;
    }

    FileHeader.bfType = ReadShort(fp);


    // if bfType is not 0x4d42, the file is not a bmp:

    if (FileHeader.bfType != 0x4d42)
    {
        fprintf(stderr, "Wrong type of file: 0x%0x\n", FileHeader.bfType);
        fclose(fp);
        return NULL;
    }


    FileHeader.bfSize = ReadInt(fp);
    FileHeader.bfReserved1 = ReadShort(fp);
    FileHeader.bfReserved2 = ReadShort(fp);
    FileHeader.bfOffBits = ReadInt(fp);


    InfoHeader.biSize = ReadInt(fp);
    InfoHeader.biWidth = ReadInt(fp);
    InfoHeader.biHeight = ReadInt(fp);

    nums = InfoHeader.biWidth;
    numt = InfoHeader.biHeight;

    InfoHeader.biPlanes = ReadShort(fp);
    InfoHeader.biBitCount = ReadShort(fp);
    InfoHeader.biCompression = ReadInt(fp);
    InfoHeader.biSizeImage = ReadInt(fp);
    InfoHeader.biXPelsPerMeter = ReadInt(fp);
    InfoHeader.biYPelsPerMeter = ReadInt(fp);
    InfoHeader.biClrUsed = ReadInt(fp);
    InfoHeader.biClrImportant = ReadInt(fp);


    // fprintf( stderr, "Image size found: %d x %d\n", ImageWidth, ImageHeight );


    texture = new unsigned char[3 * nums * numt];
    if (texture == NULL)
    {
        fprintf(stderr, "Cannot allocate the texture array!\b");
        return NULL;
    }


    // extra padding bytes:

    numextra = 4 * (((3 * InfoHeader.biWidth) + 3) / 4) - 3 * InfoHeader.biWidth;


    // we do not support compression:

    if (InfoHeader.biCompression != birgb)
    {
        fprintf(stderr, "Wrong type of image compression: %d\n", InfoHeader.biCompression);
        fclose(fp);
        return NULL;
    }



    rewind(fp);
    fseek(fp, 14 + 40, SEEK_SET);

    if (InfoHeader.biBitCount == 24)
    {
        for (t = 0, tp = texture; t < numt; t++)
        {
            for (s = 0; s < nums; s++, tp += 3)
            {
                *(tp + 2) = fgetc(fp);		// b
                *(tp + 1) = fgetc(fp);		// g
                *(tp + 0) = fgetc(fp);		// r
            }

            for (e = 0; e < numextra; e++)
            {
                fgetc(fp);
            }
        }
    }

    fclose(fp);

    *width = nums;
    *height = numt;
    return texture;
}





#pragma endregion readbmp

#pragma region sphere
bool	Distort;		// global -- true means to distort the texture

struct point {
    float x, y, z;		// coordinates
    float nx, ny, nz;	// surface normal
    float s, t;		// texture coords
};

int		NumLngs, NumLats;
struct point *	Pts;

struct point *
PtsPointer(int lat, int lng)
{
    if (lat < 0)	lat += (NumLats - 1);
    if (lng < 0)	lng += (NumLngs - 1);
    if (lat > NumLats - 1)	lat -= (NumLats - 1);
    if (lng > NumLngs - 1)	lng -= (NumLngs - 1);
    return &Pts[NumLngs*lat + lng];
}



void
DrawPoint(struct point *p)
{
    glNormal3f(p->nx, p->ny, p->nz);
    glTexCoord2f(p->s, p->t);
    glVertex3f(p->x, p->y, p->z);
}

void
MjbSphere(float radiusX, float radiusY,float radiusZ, int slices, int stacks)
{
    struct point top, bot;		// top, bottom points
    struct point *p;

    // set the globals:

    NumLngs = slices;
    NumLats = stacks;

    if (NumLngs < 3)
        NumLngs = 3;

    if (NumLats < 3)
        NumLats = 3;


    // allocate the point data structure:

    Pts = new struct point[NumLngs * NumLats];


    // fill the Pts structure:

    for (int ilat = 0; ilat < NumLats; ilat++)
    {
        float lat = -M_PI / 2. + M_PI * (float)ilat / (float)(NumLats - 1);
        float xz = cos(lat);
        float y = sin(lat);
        for (int ilng = 0; ilng < NumLngs; ilng++)
        {
            float lng = -M_PI + 2. * M_PI * (float)ilng / (float)(NumLngs - 1);
            float x = xz * cos(lng);
            float z = -xz * sin(lng);
            p = PtsPointer(ilat, ilng);
            p->x = radiusX * x;
            p->y = radiusY * y;
            p->z = radiusZ * z;
            p->nx = x;
            p->ny = y;
            p->nz = z;
            if (Distort)
            {
                p->s = 2.4*(lng + M_PI) / (2.*M_PI);
                p->t = 1.3*(lat + M_PI / 2.) / M_PI;
                //p->s = ? ? ? ? ?
                //p->t = ? ? ? ? ?
            }
            else
            {
                p->s = (lng + M_PI) / (2.*M_PI);
                p->t = (lat + M_PI / 2.) / M_PI;
            }
        }
    }

    top.x = radiusX;		top.y = radiusY;	top.z = radiusZ;
    top.nx = 0.;		top.ny = 1.;		top.nz = 0.;
    top.s = 0.;		top.t = 1.;

    bot.x =-radiusX;	bot.y = -radiusY;	bot.z = -radiusZ;//0.;
    bot.nx = 0.;		bot.ny = -1.;		bot.nz = 0.;
    bot.s = 0.;		bot.t = 0.;


    // connect the north pole to the latitude NumLats-2:

    glBegin(GL_LINE_STRIP);
    for (int ilng = 0; ilng < NumLngs - 1; ilng++)
    {
        p = PtsPointer(NumLats - 1, ilng);
        DrawPoint(p);

        p = PtsPointer(NumLats - 2, ilng);
        DrawPoint(p);

        p = PtsPointer(NumLats - 2, ilng + 1);
        DrawPoint(p);

        p = PtsPointer(NumLats - 1, ilng + 1);
        DrawPoint(p);
    }
    glEnd();

    // connect the south pole to the latitude 1:

    glBegin(GL_LINE_STRIP);
    for (int ilng = 0; ilng < NumLngs - 1; ilng++)
    {
        p = PtsPointer(0, ilng);
        DrawPoint(p);

        p = PtsPointer(0, ilng + 1);
        DrawPoint(p);

        p = PtsPointer(1, ilng + 1);
        DrawPoint(p);

        p = PtsPointer(1, ilng);
        DrawPoint(p);
    }
    glEnd();


    // connect the other 4-sided polygons:

    glBegin(GL_LINE_STRIP);
    for (int ilat = 2; ilat < NumLats - 1; ilat++)
    {
        for (int ilng = 0; ilng < NumLngs - 1; ilng++)
        {
            p = PtsPointer(ilat - 1, ilng);
            DrawPoint(p);

            p = PtsPointer(ilat - 1, ilng + 1);
            DrawPoint(p);

            p = PtsPointer(ilat, ilng + 1);
            DrawPoint(p);

            p = PtsPointer(ilat, ilng);
            DrawPoint(p);
        }
    }
    glEnd();

    delete[] Pts;
    Pts = NULL;
}

#pragma endregion sphere





#pragma region doMenu
void
DoAxesMenu( int id )
{
    AxesOn = id;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

void
DoColorMenu( int id )
{
    WhichColor = id - RED;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}
void DoDistortionMenu(int id)
{
    Distortion = id;

    glutSetWindow(MainWindow);
    glutPostRedisplay();
}

void
DoDebugMenu( int id )
{
    DebugOn = id;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


void
DoDepthMenu( int id )
{
    DepthCueOn = id;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// main menu callback:

void
DoMainMenu( int id )
{
    switch( id )
    {
        case RESET:
            Reset( );
            break;

        case QUIT:
            // gracefully close out the graphics:
            // gracefully close the graphics window:
            // gracefully exit the program:
            glutSetWindow( MainWindow );
            glFinish( );
            glutDestroyWindow( MainWindow );
            exit( 0 );
            break;

        default:
            fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
    }

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
    WhichProjection = id;

    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
    glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );

    char c;			// one character to print
    for( ; ( c = *s ) != '\0'; s++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
    }
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
    glPushMatrix( );
    glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
    float sf = ht / ( 119.05f + 33.33f );
    glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
    char c;			// one character to print
    for( ; ( c = *s ) != '\0'; s++ )
    {
        glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
    }
    glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
    // get # of milliseconds since the start of the program:

    int ms = glutGet( GLUT_ELAPSED_TIME );

    // convert it to seconds:

    return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
    glutSetWindow( MainWindow );

    int numColors = sizeof( Colors ) / ( 3*sizeof(int) );
    int colormenu = glutCreateMenu( DoColorMenu );
    for( int i = 0; i < numColors; i++ )
    {
        glutAddMenuEntry( ColorNames[i], i );
    }

    int axesmenu = glutCreateMenu( DoAxesMenu );
    glutAddMenuEntry( "Off",  0 );
    glutAddMenuEntry( "On",   1 );

    int depthcuemenu = glutCreateMenu( DoDepthMenu );
    glutAddMenuEntry( "Off",  0 );
    glutAddMenuEntry( "On",   1 );

    int debugmenu = glutCreateMenu( DoDebugMenu );
    glutAddMenuEntry( "Off",  0 );
    glutAddMenuEntry( "On",   1 );
    int projmenu = glutCreateMenu( DoProjectMenu );
    glutAddMenuEntry( "Orthographic",  ORTHO );
    glutAddMenuEntry( "Perspective",   PERSP );

    int distormenu = glutCreateMenu(DoDistortionMenu);
    glutAddMenuEntry("BLOB", NOTEXTURE);
    glutAddMenuEntry("Texture", TEXTUREIMAGE);
    glutAddMenuEntry("Distortion Texture", DISTORTIONIMAGE);





    int mainmenu = glutCreateMenu( DoMainMenu );
    glutAddSubMenu(   "Axes",          axesmenu);
    glutAddSubMenu(   "Colors",        colormenu);
    glutAddSubMenu(   "Depth Cue",     depthcuemenu);
    glutAddSubMenu(  "Projection",    projmenu );
    glutAddSubMenu("Distortion",	distormenu);
    glutAddMenuEntry( "Reset",         RESET );
    glutAddSubMenu(   "Debug",         debugmenu);
    glutAddMenuEntry( "Quit",          QUIT );

// attach the pop-up menu to the right mouse button:

    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

#pragma endregion doMenu

// initialize the glut and OpenGL libraries:
//	also setup display lists and callback functions

void
InitGraphics( )
{
    // request the display modes:
    // ask for red-green-blue-alpha color, double-buffering, and z-buffering:

    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    // set the initial window configuration:

    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );

    // open the window and set its title:

    MainWindow = glutCreateWindow( WINDOWTITLE );
    glutSetWindowTitle( WINDOWTITLE );

    // set the framebuffer clear values:

    glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );

    // setup the callback functions:
    // DisplayFunc -- redraw the window
    // ReshapeFunc -- handle the user resizing the window
    // KeyboardFunc -- handle a keyboard input
    // MouseFunc -- handle the mouse button going down or up
    // MotionFunc -- handle the mouse moving with a button down
    // PassiveMotionFunc -- handle the mouse moving with a button up
    // VisibilityFunc -- handle a change in window visibility
    // EntryFunc	-- handle the cursor entering or leaving the window
    // SpecialFunc -- handle special keys on the keyboard
    // SpaceballMotionFunc -- handle spaceball translation
    // SpaceballRotateFunc -- handle spaceball rotation
    // SpaceballButtonFunc -- handle spaceball button hits
    // ButtonBoxFunc -- handle button box hits
    // DialsFunc -- handle dial rotations
    // TabletMotionFunc -- handle digitizing tablet motion
    // TabletButtonFunc -- handle digitizing tablet button hits
    // MenuStateFunc -- declare when a pop-up menu is in use
    // TimerFunc -- trigger something to happen a certain time from now
    // IdleFunc -- what to do when nothing else is going on

    glutSetWindow( MainWindow );
    glutDisplayFunc( Display );
    glutReshapeFunc( Resize );
    glutKeyboardFunc( Keyboard );
    glutMouseFunc( MouseButton );
    glutMotionFunc( MouseMotion );
    glutPassiveMotionFunc( NULL );
    glutVisibilityFunc( Visibility );
    glutEntryFunc( NULL );
    glutSpecialFunc( NULL );
    glutSpaceballMotionFunc( NULL );
    glutSpaceballRotateFunc( NULL );
    glutSpaceballButtonFunc( NULL );
    glutButtonBoxFunc( NULL );
    glutDialsFunc( NULL );
    glutTabletMotionFunc( NULL );
    glutTabletButtonFunc( NULL );
    glutMenuStateFunc( NULL );
    glutTimerFunc( -1, NULL, 0 );
    glutIdleFunc( NULL );

    // init glew (a window must be open to do this):

#ifdef WIN32
    GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

}
#endif //PROJECT4_MAIN_H
