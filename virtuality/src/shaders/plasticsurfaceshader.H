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

#ifndef __VIRTUALITY_PLASTICSURFACESHADER_H__
#define __VIRTUALITY_PLASTICSURFACESHADER_H__

#include <surfaceshader.H>

namespace Virtuality {

class PlasticSurfaceShader {
public:
	//! Constructor
	PlasticSurfaceShader();

	//! Destructor
	virtual ~PlasticSurfaceShader();

	//! Shades a surface
	virtual Colour shade(const Colour& Cs, const Colour& Os, const Point& P,
			const Vector& N, double u, double v, double s, double t,
			const Vector& E, const Vector& I);

};

inline PlasticSurfaceShader::PlasticSurfaceShader()
{
}

inline PlasticSurfaceShader::~PlasticSurfaceShader()
{
}

}

#endif // __VIRTUALITY_PLASTICSURFACESHADER_H__
