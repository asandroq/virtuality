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

#ifndef __VIRTUALITY_BOUNDINGBOX_H__
#define __VIRTUALITY_BOUNDINGBOX_H__

#include <ray.H>

namespace Virtuality {

class BoundingBox {
public:
	//! constructor
	BoundingBox(double x1, double y1, double z1,
		    double x2, double y2, double z2);

	//! destructor
	~BoundingBox();

	//! queries if the ray hit this box
	bool hit(const Ray& r) const;

private:
	// box extremes
	double _x1, _y1, _z1, _x2, _y2, _z2;
};

inline BoundingBox::~BoundingBox()
{
}

}

#endif  // __VIRTUALITY_BOUNDINGBOX_H__
