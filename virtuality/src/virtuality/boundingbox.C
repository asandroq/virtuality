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

BoundingBox::BoundingBox(double x1, double y1, double z1,
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
	bool inside = true;
	double candidatePlane[3];

	// find candidate planes; this loop could be avoided if
	// rays were all cast from the eye (assume perspective view)
	if(r.origin().x() < _x1) {
		quads[0] = Left;
		candidatePlane[0] = _x1;
		inside = false;
	} else if(r.origin().x() > _x1) {
		quads[0] = Right;
		candidatePlane[0] = _x2;
		inside = false;
	} else {
		quads[0] = Middle;
	}
	if(r.origin().y() < _y1) {
		quads[1] = Left;
		candidatePlane[1] = _y1;
		inside = false;
	} else if(r.origin().y() > _y1) {
		quads[1] = Right;
		candidatePlane[1] = _y2;
		inside = false;
	} else {
		quads[1] = Middle;
	}
	if(r.origin().z() < _z1) {
		quads[2] = Left;
		candidatePlane[2] = _z1;
		inside = false;
	} else if(r.origin().z() > _z1) {
		quads[2] = Right;
		candidatePlane[2] = _z2;
		inside = false;
	} else {
		quads[2] = Middle;
	}
	// ray's origin inside bounding box
	if(inside) {
		return true;
	}
	// calculate T distances to candidate planes
}

}
