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

#include <luascript.hpp>
#include <luasurfaceshader.hpp>

namespace Virtuality {

LuaSurfaceShader::LuaSurfaceShader(lua_State* L, int index)
{
	_shader = 0;
	_lua_state = L;
	// copying object to stack's top
	lua_pushvalue(_lua_state, index);
	// creating a reference to it
	_shader = lua_ref(_lua_state, 1);
}

LuaSurfaceShader::~LuaSurfaceShader()
{
	lua_unref(_lua_state, _shader);
}

void LuaSurfaceShader::shade(const ShaderEnv& env, Colour& Ci, Colour& Oi)
{
	assert(_lua_script);
	// exports the shader environment
	_lua_script->exportShaderEnv(env);
	// call the real shader
	lua_getref(_lua_state, _shader);
	lua_call(_lua_state, 0, 2);
	if(lua_isnil(_lua_state, -1)) {
		lua_error(_lua_state, "Lua shader did not return opacity");
	} else if(lua_tag(_lua_state, -1) != _lua_script->colourTag()) {
		lua_error(_lua_state, "Wrong type for returned opacity");
	} else {
		Oi = *(static_cast<Colour*>(lua_touserdata(_lua_state, -1)));
	}
	if(lua_isnil(_lua_state, -2)) {
		lua_error(_lua_state, "Lua shader did not return colour");
	} else if(lua_tag(_lua_state, -2) != _lua_script->colourTag()) {
		lua_error(_lua_state, "Wrong type for returned colour");
	} else {
		Ci = *(static_cast<Colour*>(lua_touserdata(_lua_state, -2)));
	}
	lua_pop(_lua_state, 2);
}

}
