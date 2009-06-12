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

#ifndef __VIRTUALITY_BOX_H__
#define __VIRTUALITY_BOX_H__

#include <shape.hpp>

namespace Virtuality {

class Box : public Shape {
public:
	//! Constructor
	Box(const Point& point1, const Point& point2);

	//! Destructor
	~Box() {}

	//! Queries if ray hits this shape
	virtual void hit(const Ray& r, SpanList* sl) const;

	//! Queries the surface normal at intersection point
	virtual Vector normal(const Point& P) const;

private:
	// box's extremes
	double _small_x, _big_x, _small_y, _big_y, _small_z, _big_z;
};

inline Box::Box(const Point& p1, const Point& p2)
{
	_small_x = min(p1.x(), p2.x());
	_big_x   = max(p1.x(), p2.x());
	_small_y = min(p1.y(), p2.y());
	_big_y   = max(p1.y(), p2.y());
	_small_z = min(p1.z(), p2.z());
	_big_z   = max(p1.z(), p2.z());

	// setting bounding box
	setBounds(BoundingBox(_small_x, _small_y, _small_z,
			      _big_x, _big_y, _big_z));

}

}

#endif  // __VIRTUALITY_BOX_H__
