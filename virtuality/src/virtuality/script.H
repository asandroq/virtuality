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

#ifndef __VIRTUALITY_SCRIPT_H__
#define __VIRTUALITY_SCRIPT_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
}

#include <scene.H>
#include <renderer.H>
#include <framebuffer.H>

namespace Virtuality {

class Script {
public:
	//! Constructor
	Script();

	//! Destructor
	~Script();

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

	// colours
	int _colour_tag;
	static int _colour_ctor(lua_State* L);
	static int _colour_dtor(lua_State* L);
	static int _colour_index(lua_State* L);

	// vectors
	int _vector_tag;
	static int _vector_ctor(lua_State* L);
	static int _vector_dtor(lua_State* L);
	static int _vector_index(lua_State* L);

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

	// spheres
	int _sphere_tag;
	static int _sphere_ctor(lua_State* L);

	// planes
	int _plane_tag;
	static int _plane_ctor(lua_State* L);

	// triangles
	int _triangle_tag;
	static int _triangle_ctor(lua_State* L);

	// frames
	static int _frame_ctor(lua_State* L);

	// scene to hold the objects
	Scene* _sc;

	// renderer which will render the scene
	Renderer* _rd;

	// framebuffer where to render the scene
	FrameBuffer* _fb;
};

}

#endif  //__VIRTUALITY_SCRIPT_H__
