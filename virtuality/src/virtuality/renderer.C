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

#include <cassert>
#include <iomanip>

#include <renderer.H>

namespace Virtuality {

void Renderer::printStatistics(clock_t t, int h, int i) const
{
	clock_t t1 = clock();
	int secs = (t1-t) / CLOCKS_PER_SEC;
	// showing elapsed time and current scanline
	cout << "\r";
	cout << setw(2) << secs/3600 << ":";
	cout << setw(2) << secs/60   << ":";
	cout << setw(2) << secs%60;
	cout << "\tRendering line " << h-i << " of " << h;
	if(i == 0) {
		cout << endl;
	} else {
		cout << flush;
	}
}

Colour Renderer::trace(const Ray& r) const
{
	double t;
	Shape* s;

	// ambient colour
	Colour amb(0.1, 0.1, 0.1);
	// fires ray into scene
	t = _scn->hit(r, &s);
	if(!s) {
		// we hit nothing
		return _scn->backgroundColour();
	}
	Vector V = -r.direction();
	Point  P = r.pointOnRay(t);
	Vector N = s->normal(P);
	// make normal point to camera
	if(N*V < 0.0) {
		N = -N;
	}
	// shading locally
	Colour c = amb + shade(s, P, N, V);
	// calculating reflections and refractions
	if(_curr_depth++ < _max_depth) {
		c += 0.2 * trace(s->reflectedRay(r, P));
		//c += 0.2 * trace(s->transmittedRay(r, P));
	}
	
	return c;
}

Colour Renderer::shade(Shape* s, const Point& P,
				const Vector& N, const Vector& V) const
{
	Colour c;

	assert(s);
	for(unsigned i = 0; i < _scn->numLights(); i++) {
		// gets light and light direction
		Light  l = _scn->light(i);
		Vector L = (l.position()-P).normalise();
		// calculating light contribution
		double coss = N*L;
		if(coss > 0.0) {
			// is this point in shadow?
			if(_scn->occluded(P, l.position())) {
				continue;
			}
			Vector H = 0.5*(L+V);
			c += (0.7*coss*s->colour() +
				pow(N*H, 30.0)*Colour(.7, .7, .7))*l.colour();
		}
	}

	return c;
}

void Renderer::render(bool verbose) const
{
	// elapsed time
	clock_t t;
	// scanline
	Colour *sl;
	// sample's window coordinates
	double wx, wy;
	// camera origin
	Point p = _scn->camera().position();
	// viewport dimensions
	int vw = _fb->width(), vh = _fb->height();
	// window dimensions
	double ww = _scn->camera().right().length();
	// axes of camera's coordinate system
	Vector dir = _scn->camera().direction().normalise();
	Vector xc  = (_scn->camera().up()^dir).normalise();
	Vector up  = dir^xc;

	// rendering
	t = clock();
	sl = new Colour[vw];
	for(int j = vh - 1; j >= 0; j--) {
		if(verbose) {
			printStatistics(t, vh, j);
		}
		for(int i = 0; i < vw; i++) {
			// calculating sample's window coordinates
			wy = (double) j / (double)vh - 0.5;
			wx = ((double)i / (double)vw - 0.5) * ww;
			// calculating sample's world coordinates
			Vector v(xc.x()*wx+up.x()*wy+dir.x(),
				 xc.y()*wx+up.y()*wy+dir.y(),
				 xc.z()*wx+up.z()*wy+dir.z());
			// creating and firing ray
			Ray r(p, v);
			_curr_depth = 0;
			sl[i] = trace(r);
		}
		_fb->addScanLine(sl);
	}
	delete [] sl;
}

}
