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

#ifndef __VIRTUALITY_LUASCRIPTAPI_H__
#define __VIRTUALITY_LUASCRIPTAPI_H__

extern "C" {
#include <lua.h>
}

#include <scriptapi.H>

namespace Virtuality {

namespace LuaScriptAPI {

//! Exports this API to the Lua interpreter
void exportLuaScriptAPI(lua_State* L);

//! Returns the reflection vector
int reflect(lua_State* L);

//! Returns the refraction vector
int refract(lua_State* L);

//! Returns the vector N or -N, which is opposite to I
int faceforward(lua_State* L);

//! Returns the ambient light in scene
int ambient(lua_State* L);

//! Returns the amount of diffuse light
int diffuse(lua_State* L);

//! Returns the amount of specular light
int specular(lua_State* L);

}

}

#endif // __VIRTUALITY_LUASCRIPTAPI_H__
