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

#include <math.H>
#include <plane.H>

namespace Virtuality {

void Plane::hit(const Ray& r0, SpanList* sl) const
{
	// applying inverse transformation to ray
	Ray r = transformRay(r0);
	// finds intersection
	double den = _normal.x()*r.direction().x() +
				_normal.y()*r.direction().y() +
				_normal.z()*r.direction().z();
	// tests if ray hits the plane
	if(!isZero(den)) {
		double t = (_distance - _normal.x()*r.origin().x() -
					_normal.y()*r.origin().y() -
					_normal.z()*r.origin().z()) / den;
		sl->insert(SpanList::value_type(t, this));
	}
}

}
