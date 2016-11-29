//
// Created by tadeze on 11/18/16.
//

#ifndef PROJECT4_GEOMETRY_H
#define PROJECT4_GEOMETRY_H


struct Point
{
    float x0, y0, z0;       // initial coordinates
    float x,  y,  z;        // animated coordinates
};

struct Curve
{
    float r, g, b;
    Point p0, p1, p2, p3;
};

Curve Curves[NUMCURVES];		// if you are creating a pattern of curves
Curve Stem;
void
RotateX( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x;
    float yp = y*cos(rad) - z*sin(rad);
    float zp = y*sin(rad) + z*cos(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}
void
RotateY( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp =  x*cos(rad) + z*sin(rad);
    float yp =  y;
    float zp = -x*sin(rad) + z*cos(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}
void
RotateZ( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x*cos(rad) - y*sin(rad);
    float yp = x*sin(rad) + y*cos(rad);
    float zp = z;

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}
#endif //PROJECT4_GEOMETRY_H
