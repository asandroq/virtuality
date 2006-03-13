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

#include <cassert>
#include <iomanip>

#include <renderer.hpp>

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

Colour Renderer::shade(const Ray& r) const
{
	double t;
	Shape* s;
	Colour Ci, Oi;

	// fires ray into scene
	t = _scn->hit(r, &s);
	if(!s) {
		// we hit nothing
		return _scn->backgroundColour();
	}
	Point  P = r.pointOnRay(t);
	Vector N = s->normal(P);
	// shading locally
	ShaderEnv env(s->colour(), Colour(1.0, 1.0, 1.0),
		      P, N, 0, 0, 0, 0, r.origin(), r.direction());
	s->surfaceShader()->shade(env, Ci, Oi);
	// calculating reflections and refractions
	if(_curr_depth++ < _max_depth) {
		Ci += 0.2 * shade(s->reflectedRay(r, P));
		//Ci += 0.2 * shade(s->transmittedRay(r, P));
	}
	
	return Ci;
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
			sl[i] = shade(r);
		}
		_fb->addScanLine(sl);
	}
	delete [] sl;
}

}
