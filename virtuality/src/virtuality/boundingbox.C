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

#include <boundingbox.H>

namespace Virtuality {

void BoundingBox::set(double x1, double y1, double z1,
		      double x2, double y2, double z2)
{
	_x1 = min(x1, x2);
	_x2 = max(x1, x2);
	_y1 = min(y1, y2);
	_y2 = max(y1, y2);
	_z1 = min(z1, z2);
	_z2 = max(z1, z2);
}

/*
 * This code is Andrew Woo's, from Graphics Gems, Academic Press, 1990.
 * It was modified to adapt to Virtuality.
 */

bool BoundingBox::hit(const Ray& r) const
{
	// auxiliary type definition
	enum Pos { Left, Middle, Right };

	Pos quads[3];
	double cplane[3];
	bool inside = true;

	// find candidate planes; this loop could be avoided if
	// rays were all cast from the eye (assume perspective view)
	if(r.origin().x() < _x1) {
		quads[0] = Left;
		cplane[0] = _x1;
		inside = false;
	} else if(r.origin().x() > _x2) {
		quads[0] = Right;
		cplane[0] = _x2;
		inside = false;
	} else {
		quads[0] = Middle;
	}
	if(r.origin().y() < _y1) {
		quads[1] = Left;
		cplane[1] = _y1;
		inside = false;
	} else if(r.origin().y() > _y2) {
		quads[1] = Right;
		cplane[1] = _y2;
		inside = false;
	} else {
		quads[1] = Middle;
	}
	if(r.origin().z() < _z1) {
		quads[2] = Left;
		cplane[2] = _z1;
		inside = false;
	} else if(r.origin().z() > _z2) {
		quads[2] = Right;
		cplane[2] = _z2;
		inside = false;
	} else {
		quads[2] = Middle;
	}
	// ray's origin inside bounding box
	if(inside) {
		return true;
	}
	// calculate T distances to candidate planes
	double maxT[3];
	if(quads[0] != Middle && !isZero(r.direction().x())) {
		maxT[0] = (cplane[0] - r.origin().x()) / r.direction().x();
	} else {
		maxT[0] = -1.0;
	}
	if(quads[1] != Middle && !isZero(r.direction().y())) {
		maxT[1] = (cplane[1] - r.origin().y()) / r.direction().y();
	} else {
		maxT[1] = -1.0;
	}
	if(quads[2] != Middle && !isZero(r.direction().z())) {
		maxT[2] = (cplane[2] - r.origin().z()) / r.direction().z();
	} else {
		maxT[2] = -1.0;
	}
	// get largest of the maxTs for final choice of intersection
	int plane = 0;
	for(int i = 0; i < 3; i++) {
		if(maxT[plane] < maxT[i]) {
			plane = i;
		}
	}
	// check final candidate actually inside box
	if(maxT[plane] < 0.0) {
		return false;
	}
	if(plane != 0) {
		double coord = r.origin().x() + maxT[plane] * r.direction().x();
		if(coord < _x1 || coord > _x2) {
			return false;
		}
	}
	if(plane != 1) {
		double coord = r.origin().y() + maxT[plane] * r.direction().y();
		if(coord < _y1 || coord > _y2) {
			return false;
		}
	}
	if(plane != 2) {
		double coord = r.origin().z() + maxT[plane] * r.direction().z();
		if(coord < _z1 || coord > _z2) {
			return false;
		}
	}

	return true;
}

BoundingBox& BoundingBox::operator+=(const BoundingBox& b)
{
	set(min(_x1, b._x1), min(_y1, b._y1), min(_z1, b._z1),
	    max(_x2, b._x2), max(_y2, b._y2), max(_z2, b._z2));

	return *this;
}

}
