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

namespace Virtuality {

/*
 * Functions to solve quadric, cubic and quartic equations.
 * The arguments are an array of coefficients and one for the roots,
 * the functions return the number of roots found.
 * Coefficients are passed like this:
 *
 * c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3 + c[4]*x^4 = 0
 *
 * Code by Jochen Schwarze (schwarze@isa.de)
 */

int solveQuadric(double coefs[3], double roots[2])
{
	// normal form: x^2 + px + q = 0
	double p = coefs[1] / (2 * coefs[2]);
	double q = coefs[0] / coefs[2];
	// calculates delta
	double D = sqr(p) - q;
	if(isZero(D)) {
		roots[0] = -p;
		return 1;
	} else if(D > 0.0) {
		double sqrt_D = sqrt(D);
		roots[0] =  sqrt_D - p;
		roots[1] = -sqrt_D - p;
		return 2;
	} else {
		return 0;
	}
}

int solveCubic(double coefs[4], double roots[3])
{
	int num;

	// normal form: x^3 + Ax^2 + Bx + C = 0
	double A = coefs[2] / coefs[3];
	double B = coefs[1] / coefs[3];
	double C = coefs[0] / coefs[3];
	// substitute x = y - A/3 to eliminate quadric term: x^3 + px + q = 0
	double sqr_A = sqr(A);
	double p = 1.0/3.0 * (-1.0/3.0 * sqr_A + B);
	double q = 1.0/2.0 * (2.0/27.0 * A * sqr_A - 1.0/3.0 * A * B +C);
	// use Cardano's formula
	double cb_p = p * p * p;
	double D = sqr(q) + cb_p;
	if(isZero(D)) {
		if(isZero(q)) {
			// one triple solution
			roots[0] = 0.0;
			num = 1;
		} else {
			// one single and one double solution
			double u = cbrt(-q);
			roots[0] = 2 * u;
			roots[1] = -u;
			num = 2;
		}
	} else if(D < 0.0) {
		// Casus irreducibilis: three real solutions
		double phi = 1.0/3.0 * acos(-q / sqrt(-cb_p));
		double t = 2 * sqrt(-p);
		roots[0] =  t * cos(phi);
		roots[1] = -t * cos(phi + Pi / 3.0);
		roots[2] = -t * cos(phi - Pi / 3.0);
		num = 3;
	} else {
		// one real solution
		double sqrt_D = sqrt(D);
		double u =  cbrt(sqrt_D - q);
		double v = -cbrt(sqrt_D + q);
		roots[0] = u + v;
		num = 1;
	}
	// resubstitue
	double sub = 1.0/3.0 * A;
	for(int i = 0; i < num; i++) {
		roots[i] -= sub;
	}

	return num;
}

int solveQuartic(double coefs[5], double roots[4])
{
	int num;

	// normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0
	double A = coefs[3] / coefs[4];
	double B = coefs[2] / coefs[4];
	double C = coefs[1] / coefs[4];
	double D = coefs[0] / coefs[4];
	// subs. x = y - A/4 to eliminate cubic term: x^4 + px^2 + qx + r = 0
	double sqr_A = sqr(A);
	double p = -3.0/8.0 * sqr_A + B;
	double q =  1.0/8.0 * sqr_A * A - 1.0/2.0 * A * B + C;
	double r = -3.0/256 * sqr(sqr_A) + 1.0/16 * sqr_A * B - 1.0/4*A*C + D;
	if(isZero(r)) {
		// no absolute term: y(y^3 + py + q) = 0
		double c[4];
		c[0] = q;
		c[1] = p;
		c[2] = 0.0;
		c[3] = 1.0;
		num = solveCubic(c, roots);
		roots[num++] = 0.0;
	} else {
		// solve the resolvent cubic...
		double c[4];
		c[0] = 1.0/2.0 * r * p - 1.0/8.0 * q * q;
		c[1] = -r;
		c[2] = -1.0/2.0 * p;
		c[3] = 1.0;
		(void)solveCubic(c, roots);
		// and take the one real solution...
		double z = roots[0];
		// ... to build two quadric equations
		double u = z * z - r;
		double v = 2 * z - p;
		if(isZero(u)) {
			u = 0.0;
		} else if(u > 0.0) {
			u = sqrt(u);
		} else {
			return 0;
		}
		if(isZero(v)) {
			v = 0.0;
		} else if(v > 0.0) {
			v = sqrt(v);
		} else {
			return 0;
		}
		// the first one
		c[0] = z - u;
		c[1] = q < 0.0 ? -v : v;
		c[2] = 1.0;
		num = solveQuadric(c, roots);
		// the second one
		c[0] = z + u;
		c[1] = q < 0.0 ? v : -v;
		c[2] = 1.0;
		num += solveQuadric(c, roots+num);
	}
	// resubstitute
	double sub = 1.0/4.0 * A;
	for(int i = 0; i < num; i++) {
		roots[i] -= sub;
	}

	return num;
}

}
