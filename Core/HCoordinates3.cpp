#include "HCoordinates3.h"

using namespace cagd;

//homework: get components by value
 GLfloat HCoordinate3::operator[](GLuint rhs) const
{
    return _data[rhs];
}

 GLfloat& HCoordinate3::operator[](GLuint rhs)
{
    return _data[rhs];
}

 GLfloat HCoordinate3::x()const
{
    return _data[0];
}

 GLfloat& HCoordinate3::x()
{
    return _data[0];
}


 GLfloat HCoordinate3::y()const
{
    return _data[1];
}

 GLfloat& HCoordinate3::y()
{
    return _data[1];
}

 GLfloat HCoordinate3::z()const
{
    return _data[2];
}

 GLfloat& HCoordinate3::z()
{
    return _data[2];
}

 GLfloat HCoordinate3::w()const
{
    return _data[3];
}

 GLfloat& HCoordinate3::w()
{
    return _data[3];
}

// add
 const HCoordinate3 HCoordinate3::operator +(const HCoordinate3& rhs) const
{
    return HCoordinate3(
            rhs.w() * x() + w() * rhs.x(),
            rhs.w() * y() + w() * rhs.y(),
            rhs.w() * z() + w() * rhs.z(),
            w() * rhs.w());
}

 HCoordinate3& HCoordinate3::operator+=(const HCoordinate3 &rhs)
{
    _data[0] = rhs._data[3] * _data[0] + _data[3] * rhs._data[0];
    _data[1] = rhs._data[3] * _data[1] + _data[3] * rhs._data[1];
    _data[2] = rhs._data[3] * _data[2] + _data[3] * rhs._data[2];
    _data[3] = _data[3] * rhs._data[3];
    return *this;
}

 const HCoordinate3 HCoordinate3::operator-(const HCoordinate3 &rhs) const
{
    return HCoordinate3(
            rhs.w() * x() - w() * rhs.x(),
            rhs.w() * y() - w() * rhs.y(),
            rhs.w() * z() - w() * rhs.z(),
            w() * rhs.w());
}

 HCoordinate3& HCoordinate3::operator-=(const HCoordinate3 &rhs)
{
    _data[0] = rhs._data[3] * _data[0] - _data[3] * rhs._data[0];
    _data[1] = rhs._data[3] * _data[1] - _data[3] * rhs._data[1];
    _data[2] = rhs._data[3] * _data[2] - _data[3] * rhs._data[2];
    _data[3] = _data[3] * rhs._data[3];
    return *this;
}

 GLfloat HCoordinate3::operator*(const HCoordinate3 &rhs) const
{
    GLfloat temp = _data[3] * rhs._data[3];
    return (_data[0] * rhs._data[0] / temp)+
           (_data[1] * rhs._data[1] / temp)+
           (_data[2] * rhs._data[2] / temp);
}

const HCoordinate3 HCoordinate3::operator^(const HCoordinate3 &rhs) const
{
    return HCoordinate3(
            _data[1] *rhs._data[2] - _data[2] *rhs._data[1],
            _data[2] *rhs._data[0] - _data[0] *rhs._data[2],
            _data[0] *rhs._data[1] - _data[1] *rhs._data[0],
            _data[3] *rhs._data[3]
                );
}

 HCoordinate3& HCoordinate3::operator ^=(const HCoordinate3& rhs) {
    GLfloat temp_x = y() * rhs.z() - z() * rhs.y();
    GLfloat temp_y = z() * rhs.x() - x() * rhs.z();

    z() = x() * rhs.y() - y() * rhs.x();
    w() = w() * rhs.w();

    x() = temp_x;
    y() = temp_y;

    return *this;
}

 const HCoordinate3 HCoordinate3::operator *(GLfloat rhs) const {
    return HCoordinate3(_data[0]*rhs, _data[1]*rhs, _data[2]*rhs, _data[3]);
}

// homework: scale from left with a scalar
 const HCoordinate3 operator *(GLfloat lhs, const HCoordinate3& rhs){
    return HCoordinate3(rhs.x()*lhs, rhs.y()*lhs, rhs.z()*lhs, rhs.w());
}

 HCoordinate3& HCoordinate3::operator *=(GLfloat rhs) {
    _data[0] *= rhs;
    _data[1] *= rhs;
    _data[2] *= rhs;

    return *this;
}

const HCoordinate3 HCoordinate3::operator /(GLfloat rhs) const {
    return HCoordinate3(_data[0], _data[1], _data[2], _data[3]*rhs);
};

 HCoordinate3& HCoordinate3::operator /=(GLfloat rhs) {
    _data[3] *= rhs;

    return *this;
}

 GLfloat HCoordinate3::length() const {
    return std::sqrt((*this) * (*this));
}

 HCoordinate3& HCoordinate3::normalize() {
    GLfloat l = length();

    if (l && l != 1.0)
        *this /= l;

    return *this;
}
