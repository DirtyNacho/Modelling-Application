#include "TCoordinates4.h"

using namespace cagd;

GLfloat TCoordinate4::operator[](GLuint rhs) const
{
    return _data[rhs];
}

GLfloat& TCoordinate4::operator[](GLuint rhs)
{
    return _data[rhs];
}

GLfloat TCoordinate4::s() const
{
    return _data[0];
}

GLfloat& TCoordinate4::s()
{
    return _data[0];
}

GLfloat TCoordinate4::t() const
{
    return _data[1];
}

GLfloat& TCoordinate4::t()
{
    return _data[1];
}

GLfloat TCoordinate4::r() const
{
    return _data[2];
}

GLfloat& TCoordinate4::r()
{
    return _data[2];
}

GLfloat TCoordinate4::q() const
{
    return _data[3];
}

GLfloat& TCoordinate4::q()
{
    return _data[3];
}
