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

#ifndef __VIRTUALITY_SCRIPTAPI_H__
#define __VIRTUALITY_SCRIPTAPI_H__

#include <shaderenv.H>

namespace Virtuality {

namespace ScriptAPI {

	//! Gives the reflection vector
	Vector reflect(const Vector& I, const Vector& N);

	//! Gives the refraction vector
	Vector refract(const Vector& I, const Vector& N, double eta);

	//! Returns the ambient light in scene
	Colour ambient(const ShaderEnv& env);


	//! Returns the amount of diffuse light given normal
	Colour diffuse(const ShaderEnv& env, const Vector& N);
}

}

#endif // __VIRTUALITY_SCRIPTAPI_H__
