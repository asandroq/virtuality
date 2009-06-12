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

#ifndef __VIRTUALITY_BOUNDINGBOX_H__
#define __VIRTUALITY_BOUNDINGBOX_H__

#include <ray.hpp>

namespace Virtuality {

class BoundingBox {
public:
	//! constructor
	BoundingBox();
	BoundingBox(double x1, double y1, double z1,
		    double x2, double y2, double z2);

	//! destructor
	~BoundingBox();

	//! configures this box
	void set(double x1, double y1, double z1,
		 double x2, double y2, double z2);

	//! queries if the ray hit this box
	bool hit(const Ray& r) const;

	//! enlages this box so it contains another
	BoundingBox& operator+=(const BoundingBox& b);

private:
	// box extremes
	double _x1, _y1, _z1, _x2, _y2, _z2;
};

inline BoundingBox::BoundingBox()
	: _x1(0.0), _y1(0.0), _z1(0.0), _x2(0.0), _y2(0.0), _z2(0.0)
{
}

inline BoundingBox::BoundingBox(double x1, double y1, double z1,
				double x2, double y2, double z2)
{
	set(x1, y1, z1, x2, y2, z2);
}

inline BoundingBox::~BoundingBox()
{
}

inline BoundingBox operator+(const BoundingBox& b1, const BoundingBox& b2)
{
	BoundingBox bb(b1);

	return bb += b2;
}

}

#endif  // __VIRTUALITY_BOUNDINGBOX_H__
