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

#ifndef __VIRTUALITY_MATTESURFACESHADER_H__
#define __VIRTUALITY_MATTESURFACESHADER_H__

#include <surfaceshader.H>

namespace Virtuality {

class MatteSurfaceShader : public SurfaceShader {
public:
	//! Constructor
	MatteSurfaceShader(double ka = 1.0, double kd = 1.0);

	//! Destructor
	virtual ~MatteSurfaceShader();

	//! Shades a surface
	virtual void shade(const ShaderEnv& env, Colour& Ci, Colour& Oi);

private:
	double _ka, _kd;
};

inline MatteSurfaceShader::MatteSurfaceShader(double ka, double kd)
	: _ka(ka), _kd(kd)
{
}

inline MatteSurfaceShader::~MatteSurfaceShader()
{
}

using namespace ScriptAPI;

inline void MatteSurfaceShader::shade(const ShaderEnv& env,
						Colour& Ci, Colour& Oi)
{
	Vector Nf = faceforward(env.N().normalise(), env.I());
	Oi = env.Os();
	Ci = env.Os() * env.Cs()*(_ka*ambient(env) + _kd*diffuse(env, Nf));
}

}

#endif // __VIRTUALITY_MATTESURFACESHADER_H__
