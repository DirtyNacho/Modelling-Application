#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = -TWO_PI;
GLdouble spiral_on_cone::u_max = +TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}


//torus_knot

GLdouble torus_knot::u_min = 0;
GLdouble torus_knot::u_max = 6.0* PI;

DCoordinate3 torus_knot::d0(GLdouble u)
{
    GLdouble c = (2.0*u/3.0);
    return DCoordinate3((2+cos(c))*cos(u), (2+cos(c))*sin(u), sin(c));
}

DCoordinate3 torus_knot::d1(GLdouble u)
{
    GLdouble c = (2.0*u/3.0), s = sin(u) , cu=cos(u);
    return DCoordinate3((cos(c)+2)*(-s) - ((2.0/3.0)*sin(c))*cu, (cos(c)+2.0) * cu -(2.0*sin(c)*s/3.0) ,
                        2.0*cos(c)/3.0);
}

DCoordinate3 torus_knot::d2(GLdouble u)
{
    GLdouble c = (2.0*u/3.0), s = sin(u) , cu=cos(u);
    return DCoordinate3(((12.0*sin(c)*s+(-13.0*cos(c) - 18.0)*cu))/9.0,
            ((13.0*cos(c)+18.0)*s+12.0*sin(c)*cu)/-9.0,
            4*sin(c)/(-9.0));
}

//ellipsoid_curve

GLdouble ellipsoid_curve::u_min = 0;
GLdouble ellipsoid_curve::u_max = 2.0* PI;
GLdouble ellipsoid_curve::a = PI;
GLdouble ellipsoid_curve::b = PI/2.0;
GLdouble ellipsoid_curve::c = PI;

DCoordinate3 ellipsoid_curve::d0(GLdouble u)
{
    return DCoordinate3(a*cos(u)*sin(u), b*sin(u)*sin(u), c*cos(u));
}

DCoordinate3 ellipsoid_curve::d1(GLdouble u)
{
    GLdouble sin2u = sin(u)*sin(u),cos2u=cos(u)*cos(u);
    return DCoordinate3(-1.0*a*(sin2u - cos2u), 2.0*b*cos(u)*sin(u), -1.0*c*sin(u));
}

DCoordinate3 ellipsoid_curve::d2(GLdouble u)
{
    GLdouble sin2u = sin(u)*sin(u),cos2u=cos(u)*cos(u);
    return DCoordinate3(-4.0*a*sin(u)*cos(u), -2.0*b*(sin2u - cos2u), -1.0*c*cos(u));
}

//cylinder_curve
GLdouble cylinder_curve::u_min = 0;
GLdouble cylinder_curve::u_max = 3.0 * PI;
GLdouble cylinder_curve::r=0.7;

DCoordinate3 cylinder_curve::d0(GLdouble u)
{
    return DCoordinate3(r*cos(u), r*sin(u), u);
}

DCoordinate3 cylinder_curve::d1(GLdouble u)
{
    return DCoordinate3(-1.0*r*sin(u), r*cos(u), 1.0);
}

DCoordinate3 cylinder_curve::d2(GLdouble u)
{
    return DCoordinate3(-1.0*r*cos(u), -1.0*r*sin(u),0.0);
}

//hypocycloid curve
GLdouble hypocycloid_curve::u_min = 0;
GLdouble hypocycloid_curve::u_max = R*PI;
GLdouble hypocycloid_curve::R=4.0;
GLdouble hypocycloid_curve::r=1.0;

DCoordinate3 hypocycloid_curve::d0(GLdouble u)
{
    GLdouble Rminr = R-r;
    return DCoordinate3(Rminr*cos(u)+r*cos(Rminr/r*u), Rminr*sin(u)-r*sin(Rminr/r*u), 0.0);
}

DCoordinate3 hypocycloid_curve::d1(GLdouble u)
{
    GLdouble Rminr = R-r;
    return DCoordinate3(-Rminr*(sin(Rminr*u/r)+sin(u)), -Rminr*(cos(Rminr*u/r)-cos(u)), 0.0);
}

DCoordinate3 hypocycloid_curve::d2(GLdouble u)
{
    GLdouble Rminr = R-r;
    GLdouble sinr = sin(Rminr*u/r);
    GLdouble cosr = cos(Rminr*u/r);
    return DCoordinate3(-Rminr*(cos(u) + Rminr*cosr/r), -Rminr*(sin(u) - Rminr*sinr/r),0.0);
}

//Lissajous curve

GLdouble lissajous_curve::u_min = 0;
GLdouble lissajous_curve::u_max = 2.0*PI;
GLdouble lissajous_curve::a=2.0;
GLdouble lissajous_curve::b=1.0;
GLdouble lissajous_curve::c=1.0;
GLdouble lissajous_curve::n=3.0;

DCoordinate3 lissajous_curve::d0(GLdouble u)
{
    return DCoordinate3(a*sin(u*n+c), b*sin(u), u);
}

DCoordinate3 lissajous_curve::d1(GLdouble u)
{
    return DCoordinate3(a*n*cos(u*n+c), b*cos(u), 1.0);
}

DCoordinate3 lissajous_curve::d2(GLdouble u)
{
    return DCoordinate3(-a*n*n*sin(n*u+c), -b*sin(u),0.0);
}


//Ellipse curve

GLdouble ellipse_curve::u_min = 0;
GLdouble ellipse_curve::u_max = 2.0*PI;
GLdouble ellipse_curve::a = 4.0;
GLdouble ellipse_curve::b = 1.5;

DCoordinate3 ellipse_curve::d0(GLdouble u)
{
    return DCoordinate3(a*cos(u),b*sin(u),0.0);
}

DCoordinate3 ellipse_curve::d1(GLdouble u)
{
    return DCoordinate3(-a*sin(u), b*cos(u), 0.0);
}

DCoordinate3 ellipse_curve::d2(GLdouble u)
{
    return DCoordinate3(-a*cos(u), -b*sin(u),0.0);
}
