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
#include <triangle.H>

namespace Virtuality {

void Triangle::hit(const Ray& r0, SpanList* sl) const
{
	double l1, l2, l3;

	// applying inverse transformation to ray
	Ray r = inverseTransformation() * r0;
	Vector n = normal(_p1);
	// I must first test if the ray hits the triangle's plane
	double den =
		n.x()*r.direction().x() +
		n.y()*r.direction().y() +
		n.z()*r.direction().z();
	if(isZero(den)) {
		return;
	}
	// now I must find out if the intersection point
	// lies within the triangle
	double distance = n.x()*_p1.x() + n.y()*_p1.y() + n.z()*_p1.z();
	double t = (distance -
			n.x()*r.origin().x() -
			n.y()*r.origin().y() -
			n.z()*r.origin().z()) / den;
	Point p = r.pointOnRay(t);
	// projecting onto one of the coordinate planes
	// without x
	double dx = _p1.y()*(_p2.z()-_p3.z())+
			_p2.y()*(_p3.z()-_p1.z())+
			_p3.y()*(_p1.z()-_p2.z());
	// without y
	double dy = _p1.x()*(_p2.z()-_p3.z())+
			_p2.x()*(_p3.z()-_p1.z())+
			_p3.x()*(_p1.z()-_p2.z());
	// without z
	double dz = _p1.x()*(_p2.y()-_p3.y())+
			_p2.x()*(_p3.y()-_p1.y())+
			_p3.x()*(_p1.y()-_p2.y());
	if(abs(dx) > abs(dy)) {
		if(abs(dx) > abs(dz)) {
			// without x yelds the largest area
			if(isZero(dx)) {
				return;
			}
			l1 = (p.y()*(_p2.z()-_p3.z())+
				_p2.y()*(_p3.z()-p.z())+
				_p3.y()*(p.z()-_p2.z())) / dx;
			l2 = (_p1.y()*(p.z()-_p3.z())+
				p.y()*(_p3.z()-_p1.z())+
				_p3.y()*(_p1.z()-p.z())) / dx;
			l3 = (_p1.y()*(_p2.z()-p.z())+
				_p2.y()*(p.z()-_p1.z())+
				p.y()*(_p1.z()-_p2.z())) / dx;
		} else {
			// without z yelds the largest area
			if(isZero(dz)) {
				return;
			}
			l1 = (p.x()*(_p2.y()-_p3.y())+
				_p2.x()*(_p3.y()-p.y())+
				_p3.x()*(p.y()-_p2.y())) / dz;
			l2 = (_p1.x()*(p.y()-_p3.y())+
				p.x()*(_p3.y()-_p1.y())+
				_p3.x()*(_p1.y()-p.y())) / dz;
			l3 = (_p1.x()*(_p2.y()-p.y())+
				_p2.x()*(p.y()-_p1.y())+
				p.x()*(_p1.y()-_p2.y())) / dz;
		}
	} else {
		if(abs(dy) > abs(dz)) {
			// without y yelds the largest area
			if(isZero(dy)) {
				return;
			}
			l1 = (p.x()*(_p2.z()-_p3.z())+
				_p2.x()*(_p3.z()-p.z())+
				_p3.x()*(p.z()-_p2.z())) / dy;
			l2 = (_p1.x()*(p.z()-_p3.z())+
				p.x()*(_p3.z()-_p1.z())+
				_p3.x()*(_p1.z()-p.z())) / dy;
			l3 = (_p1.x()*(_p2.z()-p.z())+
				_p2.x()*(p.z()-_p1.z())+
				p.x()*(_p1.z()-_p2.z())) / dy;
		} else {
			// without z yelds the largest area
			if(isZero(dz)) {
				return;
			}
			l1 = (p.x()*(_p2.y()-_p3.y())+
				_p2.x()*(_p3.y()-p.y())+
				_p3.x()*(p.y()-_p2.y())) / dz;
			l2 = (_p1.x()*(p.y()-_p3.y())+
				p.x()*(_p3.y()-_p1.y())+
				_p3.x()*(_p1.y()-p.y())) / dz;
			l3 = (_p1.x()*(_p2.y()-p.y())+
				_p2.x()*(p.y()-_p1.y())+
				p.x()*(_p1.y()-_p2.y())) / dz;
		}
	}
	if(!(l1 < 0.0 || l2 < 0.0 || l3 < 0.0)) {
		sl->insert(SpanList::value_type(t, this));
	}
}

Vector Triangle::normal(const Point& P) const
{
	return ((_p1-_p2)^(_p3-_p2)).normalise();
}

}
