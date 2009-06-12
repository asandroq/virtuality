/*
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

#ifndef __VIRTUALITY_RAY_H_
#define __VIRTUALITY_RAY_H_

#include <matrix.hpp>

namespace Virtuality {

class Ray {
public:
	//! Constructor
	Ray(const Point& origin = Point(), const Vector& direction = Vector())
		: _origin(origin), _direction(direction.normalise()) {}

	//! Destructor
	~Ray() {}

	//! Queries the origin of the ray
	Point origin() const { return _origin; }

	//! Queries the direction of the ray
	Vector direction() const { return _direction; }

	//! Returns a point along the ray
	Point pointOnRay(double t) const;

	//! Transforms the ray
	Ray transform(const Matrix& m, double* t) const;

private:
	// ray's origin
	Point _origin;
	// ray's direction
	Vector _direction;
};

inline Point Ray::pointOnRay(double t) const
{
	return _origin + t * _direction;
}

inline Ray Ray::transform(const Matrix& m, double* t) const
{
	// transforming direction
	Vector v = m * _direction;
	// computing factor
	*t = 1.0 / v.length();
	// returning transformed ray
	return Ray(m * _origin, v);
}

inline bool operator==(const Ray& r1, const Ray& r2)
{
	return r1.origin() == r2.origin() && r1.direction() == r2.direction();
}

}

#endif  // __VIRTUALITY_RAY_H_
