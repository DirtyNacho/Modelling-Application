#include "TriangularFaces.h"

using namespace cagd;


TriangularFace& TriangularFace::operator =(const TriangularFace& rhs)
{
    _node[0] = rhs._node[0];
    _node[1] = rhs._node[1];
    _node[2] = rhs._node[2];
    return *this;
}

GLuint TriangularFace::operator [](GLuint i) const
{
    return _node[i];
}

GLuint& TriangularFace::operator [](GLuint i)
{
    return _node[i];
}
