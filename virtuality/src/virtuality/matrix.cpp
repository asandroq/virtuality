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

#include <math.hpp>
#include <matrix.hpp>

namespace Virtuality {

#define SWAP_ROWS(a, b) { double *_tmp = (a); (a) = (b), (b) = _tmp; }

/*
 * This code was shamelessly stolen from the Mesa 3-D graphics library, by
 * Brian Paul. The code was contributed by Jacques Leroy <jle@star.be>
 */

Matrix Matrix::inverse() const
{
	double wtmp[4][8];
	double m0, m1, m2, m3, s;
	double *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = _e11, r0[1] = _e12,
	r0[2] = _e13, r0[3] = _e14,
	r0[4] =  1.0, r0[5] = r0[6] = r0[7] = 0.0,

	r1[0] = _e21, r1[1] = _e22,
	r1[2] = _e23, r1[3] = _e24,
	r1[5] =  1.0, r1[4] = r1[6] = r1[7] = 0.0,

	r2[0] = _e31, r2[1] = _e32,
	r2[2] = _e33, r2[3] = _e34,
	r2[6] =  1.0, r2[4] = r2[5] = r2[7] = 0.0,

	r3[0] = _e41, r3[1] = _e42,
	r3[2] = _e43, r3[3] = _e44,
	r3[7] =  1.0, r3[4] = r3[5] = r3[6] = 0.0;

	// choose pivot - or return identity
	if(abs(r3[0]) > abs(r2[0])) SWAP_ROWS(r3, r2);
	if(abs(r2[0]) > abs(r1[0])) SWAP_ROWS(r2, r1);
	if(abs(r1[0]) > abs(r0[0])) SWAP_ROWS(r1, r0);
	if(isZero(r0[0])) return Matrix();

	/* eliminate first variable	*/
	m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if(!isZero(s)) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if(!isZero(s)) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if(!isZero(s)) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if(!isZero(s)) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or return identity
	if(abs(r3[1]) > abs(r2[1])) SWAP_ROWS(r3, r2);
	if(abs(r2[1]) > abs(r1[1])) SWAP_ROWS(r2, r1);
	if(isZero(r1[1])) return Matrix();

	// eliminate second variable
	m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if(!isZero(s)) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if(!isZero(s)) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if(!isZero(s)) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if(!isZero(s)) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	// choose pivot - or return identity
	if(abs(r3[2]) > abs(r2[2])) SWAP_ROWS(r3, r2);
	if(isZero(r2[2])) return Matrix();

	/* eliminate third variable */
	m3 = r3[2]/r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
	r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
	r3[7] -= m3 * r2[7];

	// last check
	if(isZero(r3[3])) return Matrix();

	s = 1.0/r3[3];  	    // now back substitute row 3
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];		    // now back substitute row 2
	s  = 1.0/r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
	r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
	r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
	r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];		    // now back substitute row 1
	s  = 1.0/r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
	r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
	r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];		    // now back substitute row 0
	s  = 1.0/r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
	r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	return Matrix(r0[4], r0[5], r0[6], r0[7],
		      r1[4], r1[5], r1[6], r1[7],
      		      r2[4], r2[5], r2[6], r2[7],
      		      r3[4], r3[5], r3[6], r3[7]);
}

#undef SWAP_ROWS

Matrix Matrix::transposed() const
{
	return Matrix(_e11, _e21, _e31, _e41,
		      _e12, _e22, _e32, _e42,
		      _e13, _e23, _e33, _e43,
		      _e14, _e24, _e34, _e44);
}

#define T(x) (this->x)

Matrix& Matrix::operator*=(const Matrix& m)
{
	*this =
	Matrix(T(_e11)*m._e11+T(_e12)*m._e21+T(_e13)*m._e31+T(_e14)*m._e41,
	       T(_e11)*m._e12+T(_e12)*m._e22+T(_e13)*m._e32+T(_e14)*m._e42,
	       T(_e11)*m._e13+T(_e12)*m._e23+T(_e13)*m._e33+T(_e14)*m._e43,
	       T(_e11)*m._e14+T(_e12)*m._e24+T(_e13)*m._e34+T(_e14)*m._e44,
	       T(_e21)*m._e11+T(_e22)*m._e21+T(_e23)*m._e31+T(_e24)*m._e41,
	       T(_e21)*m._e12+T(_e22)*m._e22+T(_e23)*m._e32+T(_e24)*m._e42,
	       T(_e21)*m._e13+T(_e22)*m._e23+T(_e23)*m._e33+T(_e24)*m._e43,
	       T(_e21)*m._e14+T(_e22)*m._e24+T(_e23)*m._e34+T(_e24)*m._e44,
	       T(_e31)*m._e11+T(_e32)*m._e21+T(_e33)*m._e31+T(_e34)*m._e41,
	       T(_e31)*m._e12+T(_e32)*m._e22+T(_e33)*m._e32+T(_e34)*m._e42,
	       T(_e31)*m._e13+T(_e32)*m._e23+T(_e33)*m._e33+T(_e34)*m._e43,
	       T(_e31)*m._e14+T(_e32)*m._e24+T(_e33)*m._e34+T(_e34)*m._e44,
	       T(_e41)*m._e11+T(_e42)*m._e21+T(_e43)*m._e31+T(_e44)*m._e41,
	       T(_e41)*m._e12+T(_e42)*m._e22+T(_e43)*m._e32+T(_e44)*m._e42,
	       T(_e41)*m._e13+T(_e42)*m._e23+T(_e43)*m._e33+T(_e44)*m._e43,
	       T(_e41)*m._e14+T(_e42)*m._e24+T(_e43)*m._e34+T(_e44)*m._e44);

	return *this;
}

#undef T

Point operator*(const Matrix& m, const Point& p)
{
	double x = m.e11()*p.x() + m.e12()*p.y() + m.e13()*p.z() + m.e14();
	double y = m.e21()*p.x() + m.e22()*p.y() + m.e23()*p.z() + m.e24();
	double z = m.e31()*p.x() + m.e32()*p.y() + m.e33()*p.z() + m.e34();
	double w = m.e41()       + m.e42()       + m.e43()       + m.e44();

	if(isZero(w)) {
		return Point(x, y, z);
	} else {
		return Point(x/w, y/w, z/w);
	}
}

Vector operator*(const Matrix& m, const Vector& v)
{
	double x = m.e11()*v.x() + m.e12()*v.y() + m.e13()*v.z();
	double y = m.e21()*v.x() + m.e22()*v.y() + m.e23()*v.z();
	double z = m.e31()*v.x() + m.e32()*v.y() + m.e33()*v.z();

	return Vector(x, y, z);
}

}
