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

bool Cylinder::clip(const Ray& r, double in, double out,
					double *min, double *max) const
{
	*min = in;
	*max = out;
	// planes' distances to origin
	double bot = _base * _axis;
	double top = (_base + _length*_axis) * _axis;
	// intersect ray with the bottom plane
	double u = r.origin() * _axis;
	double dc = r.direction() * _axis;
	double dw = u - bot;
	// if parallel to plane
	if(isZero(dc)) {
		if(isZero(dw) || dw > 0.0) {
			return false;
		}
	} else {
		double t = - dw / dc;
		// if far plane
		if(dc < 0.0) {
			if(t > in && t < out) {
				out = t;
			} else if(t < in) {
				return false;
			}
		} else {
			if(t > in && t < out) {
				in = t;
			} else if(t > out) {
				return false;
			}
		}
	}
	// intersect ray with the top plane
	dw = u - top;
	// if parallel to plane
/*
	if(isZero(dc)) {
		if(isZero(dw) || dw > 0.0) {
			return false;
		}
	} else {
		double t = - dw / dc;
		// if far plane
		if(dc > 0.0) {
			if(t > in && t < out) {
				out = t;
			} else if(t < in) {
				return false;
			}
		} else {
			if(t > in && t < out) {
				in = t;
			} else if(t > out) {
				return false;
			}
		}
	}
*/
	*min = in;
	*max = out;

	return (in < out);
}

void Cylinder::hit(const Ray& r0, SpanList* sl) const
{
	double fct;

	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &fct);
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
			double t1, t2;
			// clipping negative and positive infinite
			if(clip(r, -Omega, Omega, &t1, &t2)) {
				sl->insert(SpanList::value_type(t1*fct, this));
				sl->insert(SpanList::value_type(t2*fct, this));
			}
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
		double t1, t2;
		if(clip(r, t-s, t+s, &t1, &t2)) {
			sl->insert(SpanList::value_type(t1*fct, this));
			sl->insert(SpanList::value_type(t2*fct, this));
		}
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
	// testing if point lies in any of the caps
	double t = p * _axis;
	double bot = _base * _axis;
	double top = (_base + _length * _axis) * _axis;
	if(areEqual(t, bot) || areEqual(t, top)) {
		v = _axis;
	} else {
		// distance from cylinder bottom to desired plane
		double d = t - bot;
		// point in axis and plane
		Point pn = _base + d * _axis;
		v = p - pn;
	}

	return transformNormal(v).normalise();
}

}
