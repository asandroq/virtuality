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

#ifndef __VIRTUALITY_MATH_H__
#define __VIRTUALITY_MATH_H__

#include <cmath>

namespace Virtuality {

// some constants
const double Omega = 1.0e+17;
const double Epsilon = 1.0e-10;
const double Pi = 3.1415926535898;

inline bool isZero(double t)
{
	return -Epsilon < t && t < Epsilon;
}

inline bool areEqual(double a, double b)
{
	return isZero(a-b);
}

template<class T> inline T min(T a, T b)
{
	return a < b ? a : b;
}

template<class T> inline T max(T a, T b)
{
	return a > b ? a : b;
}

template<class T> inline T min(T a, T b, T c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

template<class T> inline T max(T a, T b, T c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

template<class T> inline T clamp(T a, T min, T max)
{
	return a < min ? min : a > max ? max : a;
}

template<class T> inline T sqr(T x)
{
	return x*x;
}

// convert degrees to radians
inline double radians(double degrees)
{
	return degrees * (Pi/180.0);
}

inline double degrees(double radians)
{
	return radians / (Pi/180.0);
}

// a function to find the cubic root
inline double cbrt(double x)
{
	return x > 0.0 ? pow(x, 1.0/3.0) : x < 0.0 ? -pow(-x, 1.0/3.0) : 0.0;
}

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

int solveQuadric(double coefs[3], double roots[2]);

int solveCubic(double coefs[4], double roots[3]);

int solveQuartic(double coefs[5], double roots[4]);

}

#endif  // __VIRTUALITY_MATH_H__
