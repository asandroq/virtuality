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
#include <sphere.H>

namespace Virtuality {

void Sphere::hit(const Ray& r0, SpanList* sl) const
{
	double factor;

	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &factor);
	// sphere's centre
	double l = _centre.x();
	double m = _centre.y();
	double n = _centre.z();
	// ray's origin components
	double x = r.origin().x();
	double y = r.origin().y();
	double z = r.origin().z();
	// ray's direction components
	double i = r.direction().x();
	double j = r.direction().y();
	double k = r.direction().z();
	// quadratic terms
	double b = 2*(i*(x-l) + j*(y-m) + k*(z-n));
	double c = sqr(x-l) + sqr(y-m) + sqr(z-n) - sqr(_radius);
	// delta
	double d = sqr(b) - 4*c;
	if(isZero(d)) {
		// ray grazes the sphere
		sl->insert(SpanList::value_type(-0.5*b*factor, this));
	} else if(d > 0.0) {
		double sqrt_d = sqrt(d);
		sl->insert(SpanList::value_type(0.5*(-b-sqrt_d)*factor, this));
		sl->insert(SpanList::value_type(0.5*(-b+sqrt_d)*factor, this));
	}
}

Vector Sphere::normal(const Point& p0) const
{
	Point p = inverseTransformation() * p0;
	Vector n(p.x() - _centre.x(),
		 p.y() - _centre.y(),
		 p.z() - _centre.z());

	return transformNormal(n).normalise();
}

}
