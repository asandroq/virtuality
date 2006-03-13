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

#ifndef __VIRTUALITY_SHADERENV_H__
#define __VIRTUALITY_SHADERENV_H__

#include <colour.hpp>
#include <vector.hpp>

namespace Virtuality {

//! This class encapsulates the shader's environment, with all the data it needs
class ShaderEnv {
public:
	//! Constructor
	/*!
	 * \param Cs Surface colour
	 * \param Os Surface opacity
	 * \param P  Intersection point
	 * \param N  Normal at intersection
	 * \param u  Surface parameter
	 * \param v  Surface parameter
	 * \param s  Texture coordinate
	 * \param t  Texture coordinate
	 * \param E  Eye position
	 * \param I  Incident ray direction
	 */
	ShaderEnv(const Colour& Cs, const Colour& Os,
		  const Point& P, const Vector& N, double u, double v,
		  double s, double t, const Point& E, const Vector& I);

	//! Destructor
	~ShaderEnv();

	//! Queries the surface colour
	Colour Cs() const;

	//! Queries the surface opacity
	Colour Os() const;

	//! Queries the intersection point
	Point P() const;

	//! Queries the normal vector at intersection
	Vector N() const;

	//! Queries the "u" surface parameter
	double u() const;

	//! Queries the "v" surface parameter
	double v() const;

	//! Queries the "s" texture coodinate
	double s() const;

	//! Queries the "t" texture coordinate
	double t() const;

	//! Queries the eye position
	Point E() const;

	//! Queries the incident ray direction
	Vector I() const;

private:
	// surface's colour and opacity
	Colour _Cs, _Os;
	// intersection point
	Point _P;
	// normal vector at intersection
	Vector _N;
	// surface parameters
	double _u, _v;
	// texture coordinates
	double _s, _t;
	// eye position
	Point _E;
	// incident ray direction
	Vector _I;
};

inline ShaderEnv::ShaderEnv(const Colour& Cs, const Colour& Os,
			    const Point& P, const Vector& N, double u, double v,
			    double s, double t, const Point& E, const Vector& I)
	: _Cs(Cs), _Os(Os), _P(P), _N(N),
	  _u(u), _v(v), _s(s), _t(t), _E(E),_I(I)
{
}

inline ShaderEnv::~ShaderEnv()
{
}

inline Colour ShaderEnv::Cs() const
{
	return _Cs;
}

inline Colour ShaderEnv::Os() const
{
	return _Os;
}

inline Point ShaderEnv::P() const
{
	return _P;
}

inline Vector ShaderEnv::N() const
{
	return _N;
}

inline double ShaderEnv::u() const
{
	return _u;
}

inline double ShaderEnv::v() const
{
	return _v;
}

inline double ShaderEnv::s() const
{
	return _s;
}

inline double ShaderEnv::t() const
{
	return _t;
}

inline Point ShaderEnv::E() const
{
	return _E;
}

inline Vector ShaderEnv::I() const
{
	return _I;
}

}

#endif // __VIRTUALITY_SHADERENV_H__
