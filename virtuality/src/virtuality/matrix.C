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
#include <matrix.H>

namespace Virtuality {

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

#undef T(x)

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
