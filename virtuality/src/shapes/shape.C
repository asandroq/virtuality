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
#include <shape.H>

namespace Virtuality {

/*
 * This piece of code was "inspired" by the source of a famous package that
 * unfortunately has a very restrictive license. Can this be considered a
 * copy?
 */
void Shape::rotate(double ax, double ay, double az)
{
	double cosx, sinx, cosy, siny, cosz, sinz;

	// precomputing...
	cosx = cos(radians(ax));
	sinx = sin(radians(ax));
	cosy = cos(radians(ay));
	siny = sin(radians(ay));
	cosz = cos(radians(az));
	sinz = sin(radians(az));
}

Ray Shape::reflectedRay(const Ray& r, const Point& P) const
{
	Vector N = normal(P);
	// makes ray go to eye
	Vector I = -r.direction();

	return Ray(P, 2*(N*I)*N - I);
}

Ray Shape::transmittedRay(const Ray& r, const Point& P) const
{
	const double nr = 1.0;

	Vector N = normal(P);
	// makes ray go to eye
	Vector I = -r.direction();

	return Ray(P, (nr*(N*I)-sqrt(1.0-sqr(nr)*(1.0-sqr(N*I))))*N-nr*I);
}

}
