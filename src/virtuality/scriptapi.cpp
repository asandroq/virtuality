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

#include <cassert>

#include <math.hpp>
#include <luascript.hpp>
#include <scriptapi.hpp>

namespace Virtuality {

namespace ScriptAPI {

Vector reflect(const Vector& I, const Vector& N)
{
	return I - 2*(I*N)*N;
}

Vector refract(const Vector& I, const Vector& N, double eta)
{
	double IdotN = I*N;
	double k = 1 - sqr(eta)*(1 - sqr(IdotN));
	return k < 0 ? Vector(0.0, 0.0, 0.0) : eta*I - (eta*IdotN + sqrt(k))*N;
}

Vector faceforward(const Vector& N, const Vector& I)
{
	if(N*I < 0.0) {
		return N;
	} else {
		return -N;
	}
}

Colour ambient(const ShaderEnv& env)
{
	assert(_lua_script);
	return _lua_script->scene()->ambient();
}

Colour diffuse(const ShaderEnv& env, const Vector& N)
{
	Colour c;

	assert(_lua_script);
	for(unsigned i = 0; i < _lua_script->scene()->numLights(); i++) {
		// gets light and light direction
                Light  l = _lua_script->scene()->light(i);
		Vector L = (l.position()-env.P()).normalise();
		 // calculating light contribution
                double coss = N*L;
                if(coss > 0.0) {
                        // is this point in shadow?
                        if(_lua_script->scene()->occluded(env.P(),
								l.position())) {
                                continue;
                        }
			c += coss*l.colour();
		}
	}

	return c;
}

Colour specular(const ShaderEnv& env, 
        	        const Vector& N, const Vector& V, double roughness)
{
	Colour c;

	assert(_lua_script);
	if(isZero(roughness)) {
		roughness = 0.02;
	}
	for(unsigned i = 0; i < _lua_script->scene()->numLights(); i++) {
		// gets light and light direction
                Light  l = _lua_script->scene()->light(i);
		Vector L = (l.position()-env.P()).normalise();
		 // calculating light contribution
                if(N*L > 0.0) {
                        // is this point in shadow?
                        if(_lua_script->scene()->occluded(env.P(),
								l.position())) {
                                continue;
                        }
			Vector H = 0.5*(L+V);
			c += pow(N*H, 1/roughness)*l.colour();
                                
		}
	}

	return c;
}

}

}
