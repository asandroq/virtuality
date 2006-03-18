/*
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

#ifndef __VIRTUALITY_LUASCRIPT_H__
#define __VIRTUALITY_LUASCRIPT_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <scene.hpp>
#include <renderer.hpp>
#include <framebuffer.hpp>

namespace Virtuality {

class LuaScript;

#warning I really would like to get rid of this global variable
// currently running script
extern LuaScript* _lua_script;

class LuaScript {
public:
	//! Constructor
	LuaScript();

	//! Destructor
	~LuaScript();

	//! Queries the current scene
	const Scene* scene() const;

	//! Queries the tag of the Colour objects
	int colourTag() const;

	// exports the shading environment to the Lua interpreter
	void exportShaderEnv(const ShaderEnv& env);

	//! Runs specified script
	bool run(const char* filename, bool verbose);

private:
	// state
	bool _verbose;

	// lua state
	int _script_ref;
	lua_State* _lua_state;

	// points
	int _point_tag;
	static int _point_ctor(lua_State* L);
	static int _point_dtor(lua_State* L);
	static int _point_index(lua_State* L);
	static int _point_add(lua_State* L);
	static int _point_sub(lua_State* L);
	static int _point_mul(lua_State* L);
	static int _point_div(lua_State* L);

	// colours
	int _colour_tag;
	static int _colour_ctor(lua_State* L);
	static int _colour_dtor(lua_State* L);
	static int _colour_index(lua_State* L);
	static int _colour_add(lua_State* L);
	static int _colour_sub(lua_State* L);
	static int _colour_mul(lua_State* L);
	static int _colour_div(lua_State* L);

	// vectors
	int _vector_tag;
	static int _vector_ctor(lua_State* L);
	static int _vector_dtor(lua_State* L);
	static int _vector_index(lua_State* L);
	static int _vector_add(lua_State* L);
	static int _vector_sub(lua_State* L);
	static int _vector_mul(lua_State* L);
	static int _vector_div(lua_State* L);

	// light
	int _light_tag;
	static int _light_ctor(lua_State* L);
	static int _light_dtor(lua_State* L);

	// camera
	int _camera_tag;
	static int _camera_ctor(lua_State* L);
	static int _camera_dtor(lua_State* L);

	// shapes
	void _shape_ctor(lua_State* L, Shape* s);
	static int _shape_dtor(lua_State* L);

	// CSG
	int _csg_tag;
	static int _union_ctor(lua_State* L);
	static int _difference_ctor(lua_State* L);
	static int _intersection_ctor(lua_State* L);

	// boxes
	int _box_tag;
	static int _box_ctor(lua_State* L);

	// cylinders
	int _cylinder_tag;
	static int _cylinder_ctor(lua_State* L);

	// spheres
	int _sphere_tag;
	static int _sphere_ctor(lua_State* L);

	// planes
	int _plane_tag;
	static int _plane_ctor(lua_State* L);

	// torii
	int _torus_tag;
	static int _torus_ctor(lua_State* L);

	// triangles
	int _triangle_tag;
	static int _triangle_ctor(lua_State* L);

	// surface shaders
	int _surface_tag;
	static int _constantsurface_ctor(lua_State* L);
	static int _mattesurface_ctor(lua_State* L);
	static int _plasticsurface_ctor(lua_State* L);

	// frames
	static int _frame_ctor(lua_State* L);

	// scene to hold the objects
	Scene* _sc;

	// renderer which will render the scene
	Renderer* _rd;

	// framebuffer where to render the scene
	FrameBuffer* _fb;

	// helper function
	bool isShape(int tag) const;
};

inline int LuaScript::colourTag() const
{
	return _colour_tag;
}

inline const Scene* LuaScript::scene() const
{
	return _sc;
}

}

#endif  //__VIRTUALITY_LUASCRIPT_H__
