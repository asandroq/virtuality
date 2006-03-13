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

#include <math.hpp>
#include <torus.hpp>

namespace Virtuality {

void Torus::hit(const Ray& r0, SpanList* sl) const
{
	double factor, coefs[5], roots[4];

	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &factor);
	// possibly discarding ray
	if(!bounds().hit(r)) {
		return;
	}
	// caching...
	Point p  = r.origin();
	Vector v = r.direction();
	double sqr_major = sqr(_major);
	double sqr_minor = sqr(_minor);
	// finding intersections
	double a = p.x()*v.x() + p.y()*v.y() + p.z()*v.z();
	double b = sqr(p.x()) + sqr(p.y()) + sqr(p.z()) - sqr_major - sqr_minor;
	coefs[4] = 1.0;
	coefs[3] = 4 * a;
	coefs[2] = 2 * b + 4 * sqr(a) + 4 * sqr_major * sqr(v.y());
	coefs[1] = 4 * a * b + 8 * sqr_major * p.y() * v.y();
	coefs[0] = sqr(b) - 4 * sqr_major * (sqr_minor - sqr(p.y()));
	int num_roots = solveQuartic(coefs, roots);
	if(num_roots > 0) {
		if(roots[0] > Epsilon) {
			sl->insert(SpanList::value_type(roots[0]*factor, this));
		}
		if(roots[1] > Epsilon) {
			sl->insert(SpanList::value_type(roots[1]*factor, this));
		}
	}
	if(num_roots > 2) {
		if(roots[2] > Epsilon) {
			sl->insert(SpanList::value_type(roots[2]*factor, this));
		}
		if(roots[3] > Epsilon) {
			sl->insert(SpanList::value_type(roots[3]*factor, this));
		}
	}
}

Vector Torus::normal(const Point& p0) const
{
	Vector n;

	// applying inverse transformation to point
	Point p = inverseTransformation() * p0;
	double dist = sqrt(sqr(p.x()) + sqr(p.z()));
	if(isZero(dist)) {
		n = Vector(0.0, 0.0, 0.0);
	} else {
		n = Vector(p.x() - _major*p.x()/dist,
			   p.y(),
			   p.z() - _major*p.z()/dist);
	}

	return transformNormal(n).normalise();
}

}
