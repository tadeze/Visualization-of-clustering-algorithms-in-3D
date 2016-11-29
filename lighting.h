//
// Created by tadeze on 10/28/16.
//

#ifndef PROJECT4_LIGHTING_H
#define PROJECT4_LIGHTING_H


float *
MulArray3( float factor, float array0[3] );
float *
BlendArray3( float factor, float array0[3], float array1[3] );

float *
Array4( float a, float b, float c, float d );

float *
Array3( float a, float b, float c );
void
SetSpotLight( int ilight, float x, float y, float z,  float xdir, float ydir, float zdir, float r, float g, float b )
;

void
SetPointLight( int ilight, float x, float y, float z,  float r, float g, float b );
void
SetMaterial( float r, float g, float b,  float shininess );




#endif //PROJECT4_LIGHTING_H
