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
 * This code was shamelessly stolen from the Mesa 3-D graphics library, by
 * Brian Paul, with minor modifications. This function was contributed by
 * Erich Boleyn <erich@uruk.org>
 */
void Shape::rotate(double angle, double x, double y, double z)
{
	double mag, s, c;
	double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	mag = sqrt(sqr(x) + sqr(y) + sqr(z));
	if (isZero(mag)) {
		// there is no axis
		return;
	}
	x /= mag; y /= mag; z /= mag;

	s = sin(radians(angle));
	c = cos(radians(angle));

	/*
	 *     Arbitrary axis rotation matrix.
	 *
	 *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
	 *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
	 *  (which is about the X-axis), and the two composite transforms
	 *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
	 *  from the arbitrary axis to the X-axis then back.  They are
	 *  all elementary rotations.
	 *
	 *  Rz' is a rotation about the Z-axis, to bring the axis vector
	 *  into the x-z plane.  Then Ry' is applied, rotating about the
	 *  Y-axis to bring the axis vector parallel with the X-axis.  The
	 *  rotation about the X-axis is then performed.  Ry and Rz are
	 *  simply the respective inverse transforms to bring the arbitrary
	 *  axis back to it's original orientation.  The first transforms
	 *  Rz' and Ry' are considered inverses, since the data from the
	 *  arbitrary axis gives you info on how to get to it, not how
	 *  to get away from it, and an inverse must be applied.
	 *
	 *  The basic calculation used is to recognize that the arbitrary
	 *  axis vector (x, y, z), since it is of unit length, actually
	 *  represents the sines and cosines of the angles to rotate the
	 *  X-axis to the same orientation, with theta being the angle about
	 *  Z and phi the angle about Y (in the order described above)
	 *  as follows:
	 *
	 *  cos ( theta ) = x / sqrt ( 1 - z^2 )
	 *  sin ( theta ) = y / sqrt ( 1 - z^2 )
	 *
	 *  cos ( phi ) = sqrt ( 1 - z^2 )
	 *  sin ( phi ) = z
	 *
	 *  Note that cos ( phi ) can further be inserted to the above
	 *  formulas:
	 *
	 *  cos ( theta ) = x / cos ( phi )
	 *  sin ( theta ) = y / sin ( phi )
	 *
	 *  ...etc.  Because of those relations and the standard trigonometric
	 *  relations, it is pssible to reduce the transforms down to what
	 *  is used below.  It may be that any primary axis chosen will give the
	 *  same results (modulo a sign convention) using thie method.
	 *
	 *  Particularly nice is to notice that all divisions that might
	 *  have caused trouble when parallel to certain planes or
	 *  axis go away with care paid to reducing the expressions.
	 *  After checking, it does perform correctly under all cases, since
	 *  in all the cases of division where the denominator would have
	 *  been zero, the numerator would have been zero as well, giving
	 *  the expected result.
	 */

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0 - c;

	Matrix temp((one_c*xx) +  c, (one_c*xy) - zs, (one_c*zx) + ys, 0.0,
		    (one_c*xy) + zs, (one_c*yy) +  c, (one_c*yz) - xs, 0.0,
		    (one_c*zx) - ys, (one_c*yz) + xs, (one_c*zz) +  c, 0.0,
		                0.0,             0.0,             0.0, 1.0);
	// applying transformation
	_trans *= temp;
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
