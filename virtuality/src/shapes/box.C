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

#include <box.H>

namespace Virtuality {

void Box::hit(const Ray& r0, SpanList* sl) const
{
	// applying inverse transformation to ray
	Ray r = inverseTransformation() * r0;
	// auxiliary points
	Point p0 = r.origin();
	Point p1 = r.pointOnRay(1.0);
	// calculating intersections
	double t1x = (min(_p1.x(), _p2.x()) - p0.x()) / (p1.x() - p0.x());
	double t2x = (max(_p1.x(), _p2.x()) - p0.x()) / (p1.x() - p0.x());
	double t1y = (min(_p1.y(), _p2.y()) - p0.y()) / (p1.y() - p0.y());
	double t2y = (max(_p1.y(), _p2.y()) - p0.y()) / (p1.y() - p0.y());
	// tests if we miss the box
	double t1 = max(t1x, t1y);
	double t2 = min(t2x, t2y);
	if(t1 > t2) {
		return;
	}
	// remaining intersections
	double t1z = (min(_p1.z(), _p2.z()) - p0.z()) / (p1.z() - p0.z());
	double t2z = (max(_p1.z(), _p2.z()) - p0.z()) / (p1.z() - p0.z());
	// remaining tests
	t1 = max(t1, t1z);
	t2 = min(t2, t2z);
	if(t1 > t2) {
		return;
	} else {
		sl->insert(SpanList::value_type(t1, this));
		sl->insert(SpanList::value_type(t2, this));
	}
}

Vector Box::normal(const Point& p) const
{
	if(isZero(p.x() - min(_p1.x(), _p2.x()))) {
		return Vector(-1.0, 0.0, 0.0);
	} else if(isZero(p.x() - max(_p1.x(), _p2.x()))) {
		return Vector( 1.0, 0.0, 0.0);
	} else if(isZero(p.y() - min(_p1.y(), _p2.y()))) {
		return Vector(0.0, -1.0, 0.0);
	} else if(isZero(p.y() - max(_p1.y(), _p2.y()))) {
		return Vector(0.0,  1.0, 0.0);
	} else if(isZero(p.z() - min(_p1.z(), _p2.z()))) {
		return Vector(0.0, 0.0, -1.0);
	} else if(isZero(p.z() - max(_p1.z(), _p2.z()))) {
		return Vector(0.0, 0.0,  1.0);
	} else {
		return Vector(0.0, 0.0, 0.0);
	}
}

}
