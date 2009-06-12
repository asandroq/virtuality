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

#ifndef __VIRTUALITY_TORUS_H__
#define __VIRTUALITY_TORUS_H__

#include <shape.hpp>

namespace Virtuality {

class Torus : public Shape {
public:
	//! Constructor
	Torus(double major, double minor);

	//! Destructor
	~Torus() {}

	//! Queries if ray hits this shape
	virtual void hit(const Ray& r, SpanList* sl) const;

	//! Queries the surface normal at intersection point
	virtual Vector normal(const Point& P) const;

private:
	// torus' major radius
	double _major;
	// torus' minor radius
	double _minor;
};

inline Torus::Torus(double major, double minor)
	: _major(major), _minor(minor)
{
	double d = major + minor;
	setBounds(BoundingBox(-d, -minor, -d, d, minor, d));
}

}

#endif  // __VIRTUALITY_TORUS_H__