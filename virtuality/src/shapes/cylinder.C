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

#include <cylinder.H>

namespace Virtuality {

/*
 * ANSI C code from the article
 * "Intersecting a Ray with a Cylinder"
 * by Joseph M. Cychosz and Warren N. Waggenspack, Jr.,
 * (3ksnn64@ecn.purdue.edu, mewagg@mewnw.dnet.lsu.edu)
 * in "Graphics Gems IV", Academic Press, 1994
 *
 * The code was modified to adapt to Virtuality
 */

double Cylinder::clip(const Ray& r, double t) const
{
}

void Cylinder::hit(const Ray& r0, SpanList* sl) const
{
	double factor;

	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &factor);
	// possibly discarding ray
	//if(!bounds().hit(r)) {
	//	return;
	//}
	// vector pointing from cylinder base to ray's origin
	Vector RC = r.origin() - _base;
	Vector n = r.direction() ^ _axis;
	// is ray parallel to cylinder?
	double length = n.length();
	if(isZero(length)) {
		double d = RC * _axis;
		d = (RC - d*_axis).length();
		if(d <= _radius) {
			//double t =
		}
		return;
	}
	// shortest distance
	n = n.normalise();
	double d = abs(RC * n);
	// ray hits infinite cylinder
	if(d <= _radius) {
		Vector O = RC ^ _axis;
		double t = -(O * n) / length;
		O = (n ^ _axis).normalise();
		double s = abs(sqrt(sqr(_radius) - sqr(d)) / (r.direction()*O));
		sl->insert(SpanList::value_type((t-s)*factor, this));
		sl->insert(SpanList::value_type((t+s)*factor, this));
	}
}

/*
 * Well, this I can say was by myself :)
 * I'm gonna find the plane whose normal is the cylinder axis and contains p,
 * then the point pn in the axis which lie in the same plane. The normal is
 * p - pn.
 */
Vector Cylinder::normal(const Point& p0) const
{
	Vector v;

	Point p = inverseTransformation() * p0;
	// distance from cylinder bottom to desired plane
	double d = p * _axis - _base * _axis;
	// point in axis and plane
	Point pn = _base + d * _axis;
	v = p - pn;

	return transformNormal(v).normalise();
}

}
