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
	double t1x, t2x, t1y, t2y, t1z, t2z;

	// applying inverse transformation to ray
	Ray r = inverseTransformation() * r0;
	// auxiliary points
	Point p0 = r.origin();
	Point p1 = r.pointOnRay(1.0);
	// calculating intersections
	double dir = p1.x() - p0.x();
	if(dir < 0.0) {
		t1x = (_big_x   - p0.x()) / dir;
		t2x = (_small_x - p0.x()) / dir;
	} else if(dir > 0.0) {
		t1x = (_small_x - p0.x()) / dir;
		t2x = (_big_x   - p0.x()) / dir;
	} else if(p0.x() >= _small_x && p0.x() <= _big_x) {
		t1x = 0.0;
		t2x = Omega;
	} else {
		return;
	}
	dir = p1.y() - p0.y();
	if(dir < 0.0) {
		t1y = (_big_y   - p0.y()) / dir;
		t2y = (_small_y - p0.y()) / dir;
	} else if(dir > 0.0) {
		t1y = (_small_y - p0.y()) / dir;
		t2y = (_big_y   - p0.y()) / dir;
	} else if(p0.y() >= _small_y && p0.y() <= _big_y) {
		t1y = 0.0;
		t2y = Omega;
	} else {
		return;
	}
	// tests if we miss the box
	double t1 = max(t1x, t1y);
	double t2 = min(t2x, t2y);
	if(t1 > t2) {
		return;
	}
	// remaining intersections
	dir = p1.z() - p0.z();
	if(dir < 0.0) {
		t1z = (_big_z   - p0.z()) / dir;
		t2z = (_small_z - p0.z()) / dir;
	} else if(dir > 0.0) {
		t1z = (_small_z - p0.z()) / dir;
		t2z = (_big_z   - p0.z()) / dir;
	} else if(p0.z() >= _small_z && p0.z() <= _big_z) {
		t1z = 0.0;
		t2z = Omega;
	} else {
		return;
	}
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
	if(areEqual(p.x(), _small_x)) {
		return Vector(-1.0, 0.0, 0.0);
	} else if(areEqual(p.x(), _big_x)) {
		return Vector( 1.0, 0.0, 0.0);
	} else if(areEqual(p.y(), _small_y)) {
		return Vector(0.0, -1.0, 0.0);
	} else if(areEqual(p.y(), _big_y)) {
		return Vector(0.0,  1.0, 0.0);
	} else if(areEqual(p.z(), _small_z)) {
		return Vector(0.0, 0.0, -1.0);
	} else if(areEqual(p.z(), _big_z)) {
		return Vector(0.0, 0.0,  1.0);
	} else {
		return Vector(0.0, 0.0, 0.0);
	}
}

}
