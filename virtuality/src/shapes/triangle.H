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

#ifndef __VIRTUALITY_TRIANGLE_H__
#define __VIRTUALITY_TRIANGLE_H__

#include <shape.H>

namespace Virtuality {

class Triangle : public Shape {
public:
	//! Constructor
	Triangle(const Point& p1, const Point& p2, const Point& p3);

	//! Destructor
	~Triangle();

	//! Queries triangle vertices
	Point point1() const;
	Point point2() const;
	Point point3() const;

	//! Queries if ray hits this shape
	virtual void hit(const Ray& r, SpanList* sl) const;

	//! Queries the surface normal at intersection point
	virtual Vector normal(const Point& P) const;

private:
	// triangle vertices
	Point _p1, _p2, _p3;
};

inline Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
	: _p1(p1), _p2(p2), _p3(p3)
{
	setBounds(BoundingBox(min(p1.x(), p2.x(), p3.x()),
			      min(p1.y(), p2.y(), p3.y()),
			      min(p1.z(), p2.z(), p3.z()),
			      max(p1.x(), p2.x(), p3.x()),
			      max(p1.y(), p2.y(), p3.y()),
			      max(p1.z(), p2.z(), p3.z())));
}

inline Triangle::~Triangle()
{
}

inline Point Triangle::point1() const
{
	return _p1;
}

inline Point Triangle::point2() const
{
	return _p2;
}

inline Point Triangle::point3() const
{
	return _p3;
}

}

#endif // __VIRTUALITY_TRIANGLE_H__
