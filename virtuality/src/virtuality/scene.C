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
#include <scene.H>

namespace Virtuality {

double Scene::hit(const Ray& r, Shape** s) const
{
	*s = 0;
	double t = -1.0;
	vector<Shape*>::const_iterator it;

	for(it = _shapes.begin(); it != _shapes.end(); it++) {
		SpanList sl;
		// does the ray hit the object?
		(*it)->hit(r, &sl);
		if(sl.empty()) {
			continue;
		}
		// testing intersection against previous values
		double i = sl.begin()->first;
		if(i > Epsilon) {
			if(t < 0.0 || i < t) {
				t = i;
				*s = const_cast<Shape*>(sl.begin()->second);
			}
		}
	}
	return t;
}

bool Scene::occluded(const Point& p1, const Point& p2) const
{
	double t;
	Ray r(p1, p2-p1);
	vector<Shape*>::const_iterator it;

	// finds parametric distance from one point to the other
	if(isZero(r.direction().x())) {
		if(isZero(r.direction().y())) {
			if(isZero(r.direction().z())) {
				// may happen if the two objects are too close
				// if so, they must "see" each other
				return false;
			} else {
				t = (p2.z()-p1.z()) / r.direction().z();
			}
		} else {
			t = (p2.y()-p1.y()) / r.direction().y();
		}
	} else {
		t = (p2.x()-p1.x()) / r.direction().x();
	}
	for(it = _shapes.begin(); it != _shapes.end(); it++) {
		SpanList sl;
		// does the ray hit the object?
		(*it)->hit(r, &sl);
		if(sl.empty()) {
			continue;
		}
		// testing intersection against previous values
		double i = sl.begin()->first;
		if(i > Epsilon && i < t) {
			return true;
		}
	}

	return false;
}

}
