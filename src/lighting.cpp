//
// Created by tadeze on 10/28/16.
//

//#include "lighting.h"
#include "lighting.h"
#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
float White[] ={1.,1.,1.};
float Grey[]= {0.82,0.82,0.82};
void
SetMaterial( float r, float g, float b,  float shininess )
{
    glMaterialfv( GL_BACK, GL_EMISSION, Array3( 0., 0., 0. ) );
    glMaterialfv( GL_BACK, GL_AMBIENT, MulArray3( .4f, Grey ) );
    glMaterialfv( GL_BACK, GL_DIFFUSE, MulArray3( 1., Grey ) );
    glMaterialfv( GL_BACK, GL_SPECULAR, Array3( 0., 0., 0. ) );
    glMaterialf ( GL_BACK, GL_SHININESS, 5.f );

    glMaterialfv( GL_FRONT, GL_EMISSION, Array3( 0., 0., 0. ) );
    glMaterialfv( GL_FRONT, GL_AMBIENT, Array3( r, g, b ) );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, Array3( r, g, b ) );
    glMaterialfv( GL_FRONT, GL_SPECULAR, MulArray3( .8f, White ) );
    glMaterialf ( GL_FRONT, GL_SHININESS, shininess );
}


void
SetPointLight( int ilight, float x, float y, float z,  float r, float g, float b )
{
    glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
    glLightfv( ilight, GL_AMBIENT,   Array3( 0., 0., 0. ) );
    glLightfv( ilight, GL_DIFFUSE,   Array3( r, g, b ) );
    glLightfv( ilight, GL_SPECULAR,  Array3( r, g, b ) );
    glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
    glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
    glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
    glEnable( ilight );
}


void
SetSpotLight( int ilight, float x, float y, float z,  float xdir, float ydir, float zdir, float r, float g, float b )
{
    glLightfv( ilight, GL_POSITION,  Array3( x, y, z ) );
    glLightfv( ilight, GL_SPOT_DIRECTION,  Array3(xdir,ydir,zdir) );
    glLightf(  ilight, GL_SPOT_EXPONENT, 1. );
    glLightf(  ilight, GL_SPOT_CUTOFF, 45. );
    glLightfv( ilight, GL_AMBIENT,   Array3( 0., 0., 0. ) );
    glLightfv( ilight, GL_DIFFUSE,   Array3( r, g, b ) );
    glLightfv( ilight, GL_SPECULAR,  Array3( r, g, b ) );
    glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
    glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
    glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
    glEnable( ilight );
}

float *
Array3( float a, float b, float c )
{
    static float array[4];

    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = 1.;
    return array;
}

float *
Array4( float a, float b, float c, float d )
{
    static float array[4];

    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = d;
    return array;
}

float *
BlendArray3( float factor, float array0[3], float array1[3] )
{
    static float array[4];

    array[0] = factor * array0[0]  +  ( 1.f - factor ) * array1[0];
    array[1] = factor * array0[1]  +  ( 1.f - factor ) * array1[1];
    array[2] = factor * array0[2]  +  ( 1.f - factor ) * array1[2];
    array[3] = 1.;
    return array;
}

float *
MulArray3( float factor, float array0[3] )
{
    static float array[4];

    array[0] = factor * array0[0];
    array[1] = factor * array0[1];
    array[2] = factor * array0[2];
    array[3] = 1.;
    return array;
}