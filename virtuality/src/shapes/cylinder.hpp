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

#ifndef __VIRTUALITY_CYLINDER_H__
#define __VIRTUALITY_CYLINDER_H__

#include <shape.hpp>

namespace Virtuality {

class Cylinder : public Shape {
public:
	//! Constructor
	Cylinder(double radius, const Point& point1, const Point& point2);

	//! Destructor
	~Cylinder();

	//! Queries if ray hits this shape
	virtual void hit(const Ray& r, SpanList* sl) const;

	//! Queries the surface normal at intersection point
	virtual Vector normal(const Point& P) const;

private:
	// base point
	Point _base;
	// axis
	Vector _axis;
	// radius
	double _radius;
	// length
	double _length;
	// clips the infinite cylinder
	bool clip(const Ray& r, double in, double out,
					double* min, double* max) const;
};

inline Cylinder::Cylinder(double r, const Point& p1, const Point& p2)
	: _base(p1), _radius(r)
{
	_axis = p2 - p1;
	_length = _axis.length();
	_axis = _axis.normalise();
}

inline Cylinder::~Cylinder()
{
}

}

#endif  // __VIRTUALITY_CYLINDER_H__
