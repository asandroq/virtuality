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

class PlasticSurfaceShader : public SurfaceShader {
public:
	//! Constructor
	PlasticSurfaceShader(double ka = 1.0, double kd = 0.5, double ks = 0.5,
			     double roughness = 0.1,
			     Colour specularcolour = Colour(1.0, 1.0, 1.0));

	//! Destructor
	virtual ~PlasticSurfaceShader();

	//! Shades a surface
	virtual void shade(const ShaderEnv& env, Colour& Ci, Colour& Oi);

private:
	double _ka, _kd, _ks, _roughness;
	Colour _specularcolour;
};

inline PlasticSurfaceShader::PlasticSurfaceShader(double ka,
						  double kd,
						  double ks,
						  double roughness,
						  Colour specularcolour)
	: _ka(ka), _kd(kd), _ks(ks),
	  _roughness(roughness), _specularcolour(specularcolour)
{
}

inline PlasticSurfaceShader::~PlasticSurfaceShader()
{
}

}

#endif // __VIRTUALITY_PLASTICSURFACESHADER_H__
