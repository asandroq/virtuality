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
 * To contact the author send eletronic mail to asandro@lcg.dc.ufc.br
 */

#ifndef __VIRTUALITY_MATRIX_H__
#define __VIRTUALITY_MATRIX_H__

#include <point.hpp>
#include <vector.hpp>

namespace Virtuality {

class Matrix {
public:
	/*!
	 * Constructor
	 * An identity matrix is constructed by default.
	 */
	Matrix(double e11=1.0, double e12=0.0, double e13=0.0, double e14=0.0,
	       double e21=0.0, double e22=1.0, double e23=0.0, double e24=0.0,
	       double e31=0.0, double e32=0.0, double e33=1.0, double e34=0.0,
	       double e41=0.0, double e42=0.0, double e43=0.0, double e44=1.0)
		: _e11(e11), _e12(e12), _e13(e13), _e14(e14),
		  _e21(e21), _e22(e22), _e23(e23), _e24(e24),
		  _e31(e31), _e32(e32), _e33(e33), _e34(e34),
		  _e41(e41), _e42(e42), _e43(e43), _e44(e44) {}

	//! accessing elements
	double e11() const, e12() const, e13() const, e14() const;
	double e21() const, e22() const, e23() const, e24() const;
	double e31() const, e32() const, e33() const, e34() const;
	double e41() const, e42() const, e43() const, e44() const;

	//! the inverse of this matrix
	Matrix inverse() const;

	//! the transposed matrix
	Matrix transposed() const;

	//! multiplying this matrix by another one
	Matrix& operator*=(const Matrix& m);

private:
	// matrix elements
	double _e11, _e12, _e13, _e14,
	       _e21, _e22, _e23, _e24,
	       _e31, _e32, _e33, _e34,
	       _e41, _e42, _e43, _e44;
};

/*
 * Acessing elements
 * Although it's a lot of code, it's all inlined so it won't be compiled.
 * This way it's smaller and safer than using double* as matrix data.
 */

inline double Matrix::e11() const
{
	return _e11;
}

inline double Matrix::e12() const
{
	return _e12;
}

inline double Matrix::e13() const
{
	return _e13;
}

inline double Matrix::e14() const
{
	return _e14;
}

inline double Matrix::e21() const
{
	return _e21;
}

inline double Matrix::e22() const
{
	return _e22;
}

inline double Matrix::e23() const
{
	return _e23;
}

inline double Matrix::e24() const
{
	return _e24;
}

inline double Matrix::e31() const
{
	return _e31;
}

inline double Matrix::e32() const
{
	return _e32;
}

inline double Matrix::e33() const
{
	return _e33;
}

inline double Matrix::e34() const
{
	return _e34;
}

inline double Matrix::e41() const
{
	return _e41;
}

inline double Matrix::e42() const
{
	return _e42;
}

inline double Matrix::e43() const
{
	return _e43;
}

inline double Matrix::e44() const
{
	return _e44;
}

//! multiplying two matrices
inline Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	Matrix r(m1);
	r *= m2;

	return r;
}

//! transforming a point
Point operator*(const Matrix& m, const Point& p);

/*!
 * transforming a vector
 * the vector is not translated
 */
Vector operator*(const Matrix& m, const Vector& v);

}

#endif // __VIRTUALITY_MATRIX_H__
