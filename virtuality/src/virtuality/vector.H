/*
 * $Id$
 *
 * The Virtuality Renderer
 * Copyright (C) 2001 Alex Sandro Queiroz e Silva
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * To contact the author send eletronic mail to asandro@lcg.dc.ufc.br
 */

#ifndef __VIRTUALITY_VECTOR_H__
#define __VIRTUALITY_VECTOR_H__

#include <math.H>
#include <point.H>

namespace Virtuality {

class Vector {
public:
	// constructor / destructor
	Vector(double x = 0.0, double y = 0.0, double z = 0.0)
		: _x(x), _y(y), _z(z) {}
	// accessing components
	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }

	// vector length
	double length() const;

	// returns this vector normalised
	Vector normalise() const;

	// scaling
	Vector& operator*=(double);

	// adding and subtracting
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);

	// cross product
	Vector& operator^=(const Vector&);

private:
	// vector components
	double _x, _y, _z;
};

inline double Vector::length() const
{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

inline Vector Vector::normalise() const
{
	double mag = length();
	if(mag > 0.0001) {
		return Vector(_x/mag, _y/mag, _z/mag);
	} else {
		return Vector();
	}
}

inline Vector& Vector::operator*=(double d)
{
	_x *= d;
	_y *= d;
	_z *= d;

	return *this;
}

inline Vector& Vector::operator+=(const Vector& v)
{
	_x += v._x;
	_y += v._y;
	_z += v._z;

	return *this;
}

inline Vector& Vector::operator-=(const Vector& v)
{
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;

	return *this;
}

inline Vector& Vector::operator^=(const Vector& v)
{
	double x, y, z;

	x = this->_y * v._z - this->_z * v._y;
	y = this->_z * v._x - this->_x * v._z;
	z = this->_x * v._y - this->_y * v._x;

	this->_x = x; this->_y = y; this->_z = z;
	return *this;
}

inline bool operator==(const Vector& v1, const Vector& v2)
{
	return v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z();
}

inline Vector operator-(const Vector& v)
{
	return Vector(-v.x(), -v.y(), -v.z());
}

inline Vector operator*(double d, const Vector& v)
{
	Vector r  = v;
	return r *= d;
}

inline Vector operator+(const Vector& v1, const Vector& v2)
{
	Vector r  = v1;
	return r += v2;
}

inline Vector operator-(const Vector& v1, const Vector& v2)
{
	Vector r  = v1;
	return r -= v2;
}

// dot product
inline double operator*(const Vector& v1, const Vector& v2)
{
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline Vector operator^(const Vector& v1, const Vector& v2)
{
	Vector r  = v1;
	return r ^= v2;
}

inline Vector operator-(const Point& p1, const Point&p2)
{
	return Vector(p1.x()-p2.x(), p1.y()-p2.y(), p1.z()-p2.z());
}

inline Point operator+(const Point& p, const Vector& v)
{
	return Point(p.x()+v.x(), p.y()+v.y(), p.z()+v.z());
}

inline Point operator-(const Point& p, const Vector& v)
{
	return Point(p.x()-v.x(), p.y()-v.y(), p.z()-v.z());
}

}

#endif // __VIRTUALITY_VECTOR_H__
