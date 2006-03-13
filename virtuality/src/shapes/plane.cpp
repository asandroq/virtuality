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
 * To contact the author send eletronic mail to ventonegro@ventonegro.org
 */

#include <plane.hpp>

namespace Virtuality {

void Plane::hit(const Ray& r0, SpanList* sl) const
{
	double factor;

	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &factor);
	// finds intersection
	double den = _normal * r.direction();
	if(!isZero(den)) {
		double t = (_distance - r.origin() * _normal) / den;
		sl->insert(SpanList::value_type(t*factor, this));
	}
}

}
