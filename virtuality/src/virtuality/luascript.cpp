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

#include <string>
#include <cassert>

#include <box.hpp>
#include <cylinder.hpp>
#include <plane.hpp>
#include <sphere.hpp>
#include <torus.hpp>
#include <triangle.hpp>

#include <union.hpp>
#include <difference.hpp>
#include <intersection.hpp>

#include <luasurfaceshader.hpp>
#include <mattesurfaceshader.hpp>
#include <plasticsurfaceshader.hpp>
#include <constantsurfaceshader.hpp>

#include <luascript.hpp>
#include <luascriptapi.hpp>
#include <pngframebuffer.hpp>
#include <tgaframebuffer.hpp>

/*
 * Code for binding Lua <---> C++ from
 * http://lua-users.org/wiki/DoItYourselfCppBinding
 */

void* operator new(size_t size, lua_State* L, const char* metaname)
{
	void *ptr = lua_newuserdata(L, size);
	luaL_getmetatable(L, metaname);
	lua_setmetatable(L, -2);

	return ptr;
}

#define luaV_pushobject(L, T) new(L, #T) T

#define luaV_udata_cast(L, pos, T) \
	reinterpret_cast<T*>(luaL_checkudata((L), (pos), #T))

namespace Virtuality {

const int FB_PNG = 1;
const int FB_TGA = 2;

int LuaScript::_point_ctor(lua_State *L)
{
	double x, y, z;

	// we must get a table
	luaL_checktype(L, 1, LUA_TTABLE);

	// reading x coordinate
	lua_getfield(L, 1, "x");
	if(lua_isnil(L, 2)) {
		x = 0.0;
	} else if(lua_type(L, 2) != LUA_TNUMBER) {
		return luaL_error(L, "invalid type for Point.x");
	} else {
		x = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);

	// reading y coordinate
	lua_getfield(L, 1, "y");
	if(lua_isnil(L, 2)) {
		y = 0.0;
	} else if(lua_type(L, 2) != LUA_TNUMBER) {
		return luaL_error(L, "invalid type for Point.y");
	} else {
		y = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);

	// reading z coordinate
	lua_getfield(L, 1, "z");
	if(lua_isnil(L, 2)) {
		z = 0.0;
	} else if(lua_type(L, 2) != LUA_TNUMBER) {
		return luaL_error(L, "invalid type for Point.z");
	} else {
		z = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);

	// pushing point onto stack
	new(L, "Point") Point(x, y, z);

	return 1;
}

int LuaScript::_point_index(lua_State* L)
{
	double res;

	// points can only be indexed by the strings "x", "y", "z"
	Point *p = luaV_udata_cast(L, 1, Point);
	const char *idx = luaL_checkstring(L, 2);

	std::string index(idx);

	if(index == "x") {
		res = p->x();
	} else if(index == "y") {
		res = p->y();
	} else if(index == "z") {
		res = p->z();
	} else {
		return luaL_error(L, "invalid point index");
	}

	lua_pushnumber(L, res);
	return 1;
}

#if 0

// it's possible to sum two points, a point and a vector, or
// a point and a scalar
int LuaScript::_point_add(lua_State *L)
{
	Point *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_point_tag && tag2 == s->_point_tag) {
		Point *p1 = static_cast<Point*>(lua_touserdata(L, 1));
		Point *p2 = static_cast<Point*>(lua_touserdata(L, 2));
		r = new Point(p1->x()+p2->x(), p1->y()+p2->y(),
							p1->z()+p2->z());
	} else if(tag1 == s->_point_tag && tag2 == s->_vector_tag) {
		Point  *p = static_cast<Point*>(lua_touserdata(L, 1));
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		r = new Point(p->x()+v->x(), p->y()+v->y(), p->z()+v->z());
	} else if(tag1 == s->_vector_tag && tag2 == s->_point_tag) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		Point  *p = static_cast<Point*>(lua_touserdata(L, 2));
		r = new Point(p->x()+v->x(), p->y()+v->y(), p->z()+v->z());
	} else if(tag1 == s->_point_tag && tag2 == LUA_TNUMBER) {
		Point *p = static_cast<Point*>(lua_touserdata(L, 1));
		double n = lua_tonumber(L, 2);
		r = new Point(p->x()+n, p->y()+n, p->z()+n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_point_tag) {
		double n = lua_tonumber(L, 1);
		Point *p = static_cast<Point*>(lua_touserdata(L, 2));
		r = new Point(p->x()+n, p->y()+n, p->z()+n);
	} else {
		lua_error(L, "incompatible types in addition");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_point_tag);

	return 1;
}

int LuaScript::_point_sub(lua_State *L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_point_tag && tag2 == s->_point_tag) {
		Point *p1 = static_cast<Point*>(lua_touserdata(L, 1));
		Point *p2 = static_cast<Point*>(lua_touserdata(L, 2));
		Vector *r = new Vector(*p1 - *p2);
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else if(tag1 == s->_point_tag && tag2 == s->_vector_tag) {
		Point  *p = static_cast<Point*>(lua_touserdata(L, 1));
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		Point  *r = new Point(p->x()-v->x(), p->y()-v->y(),
							p->z()-v->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_vector_tag && tag2 == s->_point_tag) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		Point  *p = static_cast<Point*>(lua_touserdata(L, 2));
		Point  *r = new Point(v->x()-p->x(), v->y()-p->y(),
							v->z()-p->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_point_tag && tag2 == LUA_TNUMBER) {
		Point *p = static_cast<Point*>(lua_touserdata(L, 1));
		double n = lua_tonumber(L, 2);
		Point *r = new Point(p->x()-n, p->y()-n, p->z()-n);
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_point_tag) {
		double n = lua_tonumber(L, 1);
		Point *p = static_cast<Point*>(lua_touserdata(L, 2));
		Point *r = new Point(n-p->x(), n-p->z(), n-p->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else {
		lua_error(L, "incompatible types in subtraction");
	}

	return 1;
}

int LuaScript::_point_mul(lua_State *L)
{
	Point *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_point_tag && tag2 == s->_point_tag) {
		Point *p1 = static_cast<Point*>(lua_touserdata(L, 1));
		Point *p2 = static_cast<Point*>(lua_touserdata(L, 2));
		r = new Point(p1->x()*p2->x(), p1->y()*p2->y(),
							p1->z()*p2->z());
	} else if(tag1 == s->_point_tag && tag2 == LUA_TNUMBER) {
		Point *p = static_cast<Point*>(lua_touserdata(L, 1));
		double n = lua_tonumber(L, 2);
		r = new Point(p->x()*n, p->y()*n, p->z()*n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_point_tag) {
		double n = lua_tonumber(L, 1);
		Point *p = static_cast<Point*>(lua_touserdata(L, 2));
		r = new Point(p->x()*n, p->y()*n, p->z()*n);
	} else {
		lua_error(L, "incompatible types in multiplication");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_point_tag);

	return 1;
}

int LuaScript::_point_div(lua_State *L)
{
	Point *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_point_tag && tag2 == s->_point_tag) {
		Point *p1 = static_cast<Point*>(lua_touserdata(L, 1));
		Point *p2 = static_cast<Point*>(lua_touserdata(L, 2));
		// avoids division by zero
		if(isZero(p2->x()) || isZero(p2->y()) || isZero(p2->z())) {
			lua_error(L, "division by zero");
		}
		r = new Point(p1->x()/p2->x(), p1->y()/p2->y(),
							p1->z()/p2->z());
	} else if(tag1 == s->_point_tag && tag2 == LUA_TNUMBER) {
		Point *p = static_cast<Point*>(lua_touserdata(L, 1));
		double n = lua_tonumber(L, 2);
		if(isZero(n)) {
			lua_error(L, "division by zero");
		}
		r = new Point(p->x()/n, p->y()/n, p->z()/n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_point_tag) {
		double n = lua_tonumber(L, 1);
		Point *p = static_cast<Point*>(lua_touserdata(L, 2));
		if(isZero(p->x()) || isZero(p->y()) || isZero(p->z())) {
			lua_error(L, "division by zero");
		}
		r = new Point(n/p->x(), n/p->y(), n/p->z());
	} else {
		lua_error(L, "incompatible types in division");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_point_tag);

	return 1;
}

int LuaScript::_colour_ctor(lua_State *L)
{
	double r, g, b;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Colour");
	}
	// reading red component
	lua_pushstring(L, "red");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		r = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Colour.red");
		r = 0.0;
	} else {
		r = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading green component
	lua_pushstring(L, "green");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		g = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Colour.green");
		g = 0.0;
	} else {
		g = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading blue component
	lua_pushstring(L, "blue");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		b = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Colour.blue");
		b = 0.0;
	} else {
		b = lua_tonumber(L, 2);
	}
	lua_pop(L, 2);
	// pushing colour onto stack
	Colour* c = new Colour(r, g, b);
	lua_pushusertag(L, c, s->_colour_tag);

	return 1;
}

int LuaScript::_colour_dtor(lua_State* L)
{
	Colour* c = static_cast<Colour*>(lua_touserdata(L, 1));
	lua_pop(L, 1);
	delete c;

	return 0;
}

int LuaScript::_colour_index(lua_State* L)
{
	double res;

	// colours can only be indexed by the strings "red", "green", "blue"
	if(lua_tag(L, 2) != LUA_TSTRING) {
		lua_error(L, "index of colour has wrong type");
	}
	string index(lua_tostring(L, 2));
	if(index == "red") {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		res = c->red();
	} else if(index == "green") {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		res = c->green();
	} else if(index == "blue") {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		res = c->blue();
	} else {
		lua_error(L, "invalid colour index");
		res = 0.0;
	}
	lua_pop(L, 2);
	lua_pushnumber(L, res);

	return 1;
}

int LuaScript::_colour_add(lua_State *L)
{
	Colour *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	if(tag1 == s->_colour_tag && tag2 == s->_colour_tag) {
		Colour *c1 = static_cast<Colour*>(lua_touserdata(L, 1));
		Colour *c2 = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(c1->red()+c2->red(), c1->green()+c2->green(),
							c1->blue()+c2->blue());
	} else if(tag1 == s->_colour_tag && tag2 == LUA_TNUMBER) {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		r = new Colour(c->red()+n, c->green()+n, c->blue()+n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_colour_tag) {
		double  n = lua_tonumber(L, 1);
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(c->red()+n, c->green()+n, c->blue()+n);
	} else {
		lua_error(L, "incompatible types in addition");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_colour_tag);

	return 1;
}

int LuaScript::_colour_sub(lua_State *L)
{
	Colour *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	if(tag1 == s->_colour_tag && tag2 == s->_colour_tag) {
		Colour *c1 = static_cast<Colour*>(lua_touserdata(L, 1));
		Colour *c2 = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(c1->red()-c2->red(), c1->green()-c2->green(),
							c1->blue()-c2->blue());
	} else if(tag1 == s->_colour_tag && tag2 == LUA_TNUMBER) {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		r = new Colour(c->red()-n, c->green()-n, c->blue()-n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_colour_tag) {
		double  n = lua_tonumber(L, 1);
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(n-c->red(), n-c->green(), n-c->blue());
	} else {
		lua_error(L, "incompatible types in subtraction");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_colour_tag);

	return 1;
}

int LuaScript::_colour_mul(lua_State *L)
{
	Colour *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	if(tag1 == s->_colour_tag && tag2 == s->_colour_tag) {
		Colour *c1 = static_cast<Colour*>(lua_touserdata(L, 1));
		Colour *c2 = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(c1->red()*c2->red(), c1->green()*c2->green(),
							c1->blue()*c2->blue());
	} else if(tag1 == s->_colour_tag && tag2 == LUA_TNUMBER) {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		r = new Colour(c->red()*n, c->green()*n, c->blue()*n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_colour_tag) {
		double  n = lua_tonumber(L, 1);
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 2));
		r = new Colour(n*c->red(), n*c->green(), n*c->blue());
	} else {
		lua_error(L, "incompatible types in multiplication");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_colour_tag);

	return 1;
}

int LuaScript::_colour_div(lua_State *L)
{
	Colour *r = 0;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	if(tag1 == s->_colour_tag && tag2 == s->_colour_tag) {
		Colour *c1 = static_cast<Colour*>(lua_touserdata(L, 1));
		Colour *c2 = static_cast<Colour*>(lua_touserdata(L, 2));
		// avoids division by zero
		if(isZero(c2->red()) || isZero(c2->green()) ||
						isZero(c2->blue())) {
			lua_error(L, "division by zero");
		}
		r = new Colour(c1->red()/c2->red(), c1->green()/c2->green(),
							c1->blue()/c2->blue());
	} else if(tag1 == s->_colour_tag && tag2 == LUA_TNUMBER) {
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		// avoids division by zero
		if(isZero(n)) {
			lua_error(L, "division by zero");
		}
		r = new Colour(c->red()/n, c->green()/n, c->blue()/n);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_colour_tag) {
		double  n = lua_tonumber(L, 1);
		Colour *c = static_cast<Colour*>(lua_touserdata(L, 2));
		// avoids division by zero
		if(isZero(c->red()) || isZero(c->green()) || isZero(c->blue())){
			lua_error(L, "division by zero");
		}
		r = new Colour(n/c->red(), n/c->green(), n/c->blue());
	} else {
		lua_error(L, "incompatible types in division");
	}
	// stack management
	lua_pop(L, 2);
	lua_pushusertag(L, r, s->_colour_tag);

	return 1;
}

int LuaScript::_vector_ctor(lua_State *L)
{
	double x, y, z;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Vector");
	}
	// reading x coordinate
	lua_pushstring(L, "x");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		x = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Vector.x");
		x = 0.0;
	} else {
		x = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading y coordinate
	lua_pushstring(L, "y");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		y = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Vector.y");
		y = 0.0;
	} else {
		y = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading z coordinate
	lua_pushstring(L, "z");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		z = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Vector.z");
		z = 0.0;
	} else {
		z = lua_tonumber(L, 2);
	}
	lua_pop(L, 2);
	// pushing vector onto stack
	Vector* v = new Vector(x, y, z);
	lua_pushusertag(L, v, s->_vector_tag);

	return 1;
}

int LuaScript::_vector_dtor(lua_State* L)
{
	Vector* v = static_cast<Vector*>(lua_touserdata(L, 1));
	lua_pop(L, 1);
	delete v;

	return 0;
}

int LuaScript::_vector_index(lua_State* L)
{
	double res;

	// vectors can only be indexed by the strings "x", "y", "z"
	if(lua_tag(L, 2) != LUA_TSTRING) {
		lua_error(L, "index of vector has wrong type");
	}
	string index(lua_tostring(L, 2));
	if(index == "x") {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		res = v->x();
	} else if(index == "y") {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		res = v->y();
	} else if(index == "z") {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		res = v->z();
	} else {
		lua_error(L, "invalid vector index");
		res = 0.0;
	}
	lua_pop(L, 2);
	lua_pushnumber(L, res);

	return 1;
}

int LuaScript::_vector_add(lua_State *L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_vector_tag && tag2 == s->_vector_tag) {
		Vector *a = static_cast<Vector*>(lua_touserdata(L, 1));
		Vector *b = static_cast<Vector*>(lua_touserdata(L, 2));
		Vector *r = new Vector(a->x()+b->x(), a->y()+b->y(),
							a->z()+b->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else if(tag1 == s->_vector_tag && tag2 == s->_point_tag) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		Point  *p = static_cast<Point*>(lua_touserdata(L, 2));
		Point  *r = new Point(v->x()+p->x(), v->y()+p->y(),
							v->z()+p->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_point_tag && tag2 == s->_vector_tag) {
		Point  *p = static_cast<Point*>(lua_touserdata(L, 1));
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		Point  *r = new Point(p->x()+v->x(), p->y()+v->y(),
							p->z()+v->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_vector_tag && tag2 == LUA_TNUMBER) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		Vector *r = new Vector(v->x()+n, v->y()+n, v->z()+n);
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_vector_tag) {
		double  n = lua_tonumber(L, 1);
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		Vector *r = new Vector(n+v->x(), n+v->y(), n+v->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else {
		lua_error(L, "incompatible types in addition");
	}

	return 1;
}

int LuaScript::_vector_sub(lua_State *L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// argument tags
	int tag1 = lua_tag(L, 1);
	int tag2 = lua_tag(L, 2);
	// possible cases
	if(tag1 == s->_vector_tag && tag2 == s->_vector_tag) {
		Vector *a = static_cast<Vector*>(lua_touserdata(L, 1));
		Vector *b = static_cast<Vector*>(lua_touserdata(L, 2));
		Vector *r = new Vector(a->x()-b->x(), a->y()-b->y(),
							a->z()-b->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else if(tag1 == s->_vector_tag && tag2 == s->_point_tag) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		Point  *p = static_cast<Point*>(lua_touserdata(L, 2));
		Point  *r = new Point(v->x()+p->x(), v->y()+p->y(),
							v->z()+p->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_point_tag && tag2 == s->_vector_tag) {
		Point  *p = static_cast<Point*>(lua_touserdata(L, 1));
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		Point  *r = new Point(p->x()+v->x(), p->y()+v->y(),
							p->z()+v->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_point_tag);
	} else if(tag1 == s->_vector_tag && tag2 == LUA_TNUMBER) {
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 1));
		double  n = lua_tonumber(L, 2);
		Vector *r = new Vector(v->x()+n, v->y()+n, v->z()+n);
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else if(tag1 == LUA_TNUMBER && tag2 == s->_vector_tag) {
		double  n = lua_tonumber(L, 1);
		Vector *v = static_cast<Vector*>(lua_touserdata(L, 2));
		Vector *r = new Vector(n+v->x(), n+v->y(), n+v->z());
		// stack management
		lua_pop(L, 2);
		lua_pushusertag(L, r, s->_vector_tag);
	} else {
		lua_error(L, "incompatible types in subtraction");
	}

	return 1;
}

int LuaScript::_vector_mul(lua_State *L)
{
}

int LuaScript::_vector_div(lua_State *L)
{
}

int LuaScript::_light_ctor(lua_State* L)
{
	Point p;
	Colour c;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Light");
	}
	// reading position
	lua_pushstring(L, "position");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p = Point(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Light.position");
	} else {
		p = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading colour
	lua_pushstring(L, "colour");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		c = Colour(0.7, 0.7, 0.7);
	} else if(lua_tag(L, 2) != s->_colour_tag) {
		lua_error(L, "invalid type for Light.colour");
	} else {
		c = *(static_cast<Colour*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 2);
	// creating and pushing new light
	Light* l = new Light(p, c);
	lua_pushusertag(L, l, s->_light_tag);
		
	return 1;
}

int LuaScript::_light_dtor(lua_State* L)
{
	Light* l = static_cast<Light*>(lua_touserdata(L, 1));
	lua_pop(L, 1);
	delete l;

	return 0;
}

int LuaScript::_camera_ctor(lua_State* L)
{
	Point p;
	Vector d, u, r;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Camera");
	}
	// reading position
	lua_pushstring(L, "position");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p = Point(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Camera.position");
	} else {
		p = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading direction
	lua_pushstring(L, "direction");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		d = Vector(0.0, 0.0, 1.0);
	} else if(lua_tag(L, 2) != s->_vector_tag) {
		lua_error(L, "invalid type for Camera.direction");
	} else {
		d = *(static_cast<Vector*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading up vector
	lua_pushstring(L, "up");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		u = Vector(0.0, 1.0, 0.0);
	} else if(lua_tag(L, 2) != s->_vector_tag) {
		lua_error(L, "invalid type for Camera.up");
	} else {
		u = *(static_cast<Vector*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading right vector
	lua_pushstring(L, "right");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		r = Vector(4.0/3.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_vector_tag) {
		lua_error(L, "invalid type for Camera.right");
	} else {
		r = *(static_cast<Vector*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 2);
	// creating new camera
	Camera* c = new Camera(p, d, u, r);
	lua_pushusertag(L, c, s->_camera_tag);

	return 1;
}

int LuaScript::_camera_dtor(lua_State* L)
{
	Camera* c = static_cast<Camera*>(lua_touserdata(L, 1));
	lua_pop(L, 1);
	delete c;

	return 0;
}

void LuaScript::_shape_ctor(lua_State* L, Shape* p)
{
	Colour c;
	Vector v;
	SurfaceShader* ss;

	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Shape");
	}
	// reading translation
	lua_pushstring(L, "translate");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		// ok
	} else if(lua_tag(L, 2) != _vector_tag) {
		lua_error(L, "invalid type for Shape.translate");
	} else {
		v = *(static_cast<Vector*>(lua_touserdata(L, 2)));
		p->translate(v.x(), v.y(), v.z());
	}
	lua_pop(L, 1);
	// reading rotation
	lua_pushstring(L, "rotate");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		// ok
	} else if(lua_tag(L, 2) != _vector_tag) {
		lua_error(L, "invalid type for Shape.rotate");
	} else {
		v = *(static_cast<Vector*>(lua_touserdata(L, 2)));
		p->rotate(v.x(), v.y(), v.z());
	}
	lua_pop(L, 1);
	// reading scaling
	lua_pushstring(L, "scale");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		// ok
	} else if(lua_tag(L, 2) != _vector_tag) {
		lua_error(L, "invalid type for Shape.scale");
	} else {
		v = *(static_cast<Vector*>(lua_touserdata(L, 2)));
		p->scale(v.x(), v.y(), v.z());
	}
	lua_pop(L, 1);
	// reading colour
	lua_pushstring(L, "colour");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		c = Colour(0.7, 0.7, 0.7);
	} else if(lua_tag(L, 2) != _colour_tag) {
		lua_error(L, "invalid type for Shape.colour");
	} else {
		c = *(static_cast<Colour*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	p->setColour(c);
	// reading surface shader
	lua_pushstring(L, "surface");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		ss = new ConstantSurfaceShader();
	} else if(lua_isfunction(_lua_state, 2)) {
		ss = new LuaSurfaceShader(_lua_state, 2);
	} else if(lua_tag(L, 2) != _surface_tag) {
		lua_error(L, "invalid type for Shape.surface");
		ss = 0;
	} else {
		ss = static_cast<SurfaceShader*>(lua_touserdata(L, 2));
	}
	p->setSurfaceShader(ss);
	lua_pop(L, 2);
}

int LuaScript::_shape_dtor(lua_State* L)
{
	Shape* p = static_cast<Shape*>(lua_touserdata(L, 1));
	lua_pop(L, 1);
	delete p;

	return 0;
}

int LuaScript::_union_ctor(lua_State* L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Union");
	}
	// creating new union
	CSGNode *n = new Union;
	// traversing table gathering shapes
	lua_pushnil(L);
	while(lua_next(L, 1)) {
		int tag = lua_tag(L, 3);
		if(s->isShape(tag)) {
			n->addChild(static_cast<Shape*>(lua_touserdata(L, 3)));
		}
		lua_pop(L, 1);
	}
	// returning union
	s->_shape_ctor(L, n);
	lua_pushusertag(L, n, s->_csg_tag);

	return 1;
}

int LuaScript::_difference_ctor(lua_State* L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Difference");
	}
	// creating new difference
	CSGNode *n = new Difference;
	// traversing table gathering shapes
	lua_pushnil(L);
	while(lua_next(L, 1)) {
		int tag = lua_tag(L, 3);
		if(s->isShape(tag)) {
			n->addChild(static_cast<Shape*>(lua_touserdata(L, 3)));
		}
		lua_pop(L, 1);
	}
	// returning difference
	s->_shape_ctor(L, n);
	lua_pushusertag(L, n, s->_csg_tag);

	return 1;
}

int LuaScript::_intersection_ctor(lua_State* L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Intersection");
	}
	// creating new intersection
	CSGNode *n = new Intersection;
	// traversing table gathering shapes
	lua_pushnil(L);
	while(lua_next(L, 1)) {
		int tag = lua_tag(L, 3);
		if(s->isShape(tag)) {
			n->addChild(static_cast<Shape*>(lua_touserdata(L, 3)));
		}
		lua_pop(L, 1);
	}
	// returning intersection
	s->_shape_ctor(L, n);
	lua_pushusertag(L, n, s->_csg_tag);

	return 1;
}

int LuaScript::_box_ctor(lua_State* L)
{
	Point p1, p2;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Box");
	}
	// reading first point
	lua_pushstring(L, "point1");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p1 = Point(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Box.point1");
	} else {
		p1 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading second point
	lua_pushstring(L, "point2");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p2 = Point(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Box.point2");
	} else {
		p2 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// creating and pushing new box
	Shape* b = new Box(p1, p2);
	s->_shape_ctor(L, b);
	lua_pushusertag(L, b, s->_box_tag);

	return 1;
}

int LuaScript::_cylinder_ctor(lua_State* L)
{
	double r;
	Point p1, p2;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Cylinder");
	}
	// reading radius
	lua_pushstring(L, "radius");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		r = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Cylinder.radius");
		r = 0.0;
	} else {
		r = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading first point
	lua_pushstring(L, "point1");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p1 = Point();
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Cylinder.point1");
	} else {
		p1 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading second point
	lua_pushstring(L, "point2");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p2 = Point();
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Cylinder.point2");
	} else {
		p2 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// creating and pushing new cylinder
	Shape* c = new Cylinder(r, p1, p2);
	s->_shape_ctor(L, c);
	lua_pushusertag(L, c, s->_cylinder_tag);

	return 1;
}

int LuaScript::_sphere_ctor(lua_State* L)
{
	Point p;
	double r;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Sphere");
	}
	// reading centre
	lua_pushstring(L, "centre");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p = Point(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Sphere.centre");
	} else {
		p = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading radius
	lua_pushstring(L, "radius");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		r = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Sphere.radius");
		r = 0.0;
	} else {
		r = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// creating and pushing new sphere
	Shape* sph = new Sphere(p, r);
	s->_shape_ctor(L, sph);
	lua_pushusertag(L, sph, s->_sphere_tag);

	return 1;
}

int LuaScript::_plane_ctor(lua_State* L)
{
	Vector n;
	double d;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Plane");
	}
	// reading normal
	lua_pushstring(L, "normal");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		n = Vector(0.0, 0.0, 0.0);
	} else if(lua_tag(L, 2) != s->_vector_tag) {
		lua_error(L, "invalid type for Plane.normal");
	} else {
		n = *(static_cast<Vector*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading distance
	lua_pushstring(L, "distance");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		d = 0.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Plane.distance");
		d = 0.0;
	} else {
		d = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// creating plane
	Shape* p = new Plane(n, d);
	s->_shape_ctor(L, p);
	lua_pushusertag(L, p, s->_plane_tag);

	return 1;
}

int LuaScript::_torus_ctor(lua_State* L)
{
	double major, minor;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Torus");
	}
	// reading major radius
	lua_pushstring(L, "major");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		major = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Torus.major");
		major = 0.0;
	} else {
		major = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading minor radius
	lua_pushstring(L, "minor");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		minor = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Torus.minor");
		minor = 0.0;
	} else {
		minor = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// creating torus
	Shape* t = new Torus(major, minor);
	s->_shape_ctor(L, t);
	lua_pushusertag(L, t, s->_torus_tag);

	return 1;
}

int LuaScript::_triangle_ctor(lua_State* L)
{
	Point p1, p2, p3;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Triangle");
	}
	// reading first point
	lua_pushstring(L, "point1");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p1 = Point();
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Triangle.point1");
	} else {
		p1 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading second point
	lua_pushstring(L, "point2");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p2 = Point();
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Triangle.point2");
	} else {
		p2 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// reading third point
	lua_pushstring(L, "point3");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		p3 = Point();
	} else if(lua_tag(L, 2) != s->_point_tag) {
		lua_error(L, "invalid type for Triangle.point3");
	} else {
		p3 = *(static_cast<Point*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// creating triangle
	Shape* t = new Triangle(p1, p2, p3);
	s->_shape_ctor(L, t);
	lua_pushusertag(L, t, s->_triangle_tag);

	return 1;
}

int LuaScript::_mattesurface_ctor(lua_State* L)
{
	double ka, kd;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Matte");
	}
	// reading ka
	lua_pushstring(L, "ka");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		ka = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Matte.ka");
		ka = 0.0;
	} else {
		ka = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading kd
	lua_pushstring(L, "kd");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		kd = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Matte.kd");
		kd = 0.0;
	} else {
		kd = lua_tonumber(L, 2);
	}
	lua_pop(L, 2);
	SurfaceShader *ss = new MatteSurfaceShader(ka, kd);
	lua_pushusertag(L, ss, s->_surface_tag);

	return 1;
}

int LuaScript::_plasticsurface_ctor(lua_State* L)
{
	Colour spc;
	double ka, kd, ks, rn;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Plastic");
	}
	// reading ka
	lua_pushstring(L, "ka");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		ka = 1.0;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Plastic.ka");
		ka = 0.0;
	} else {
		ka = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading kd
	lua_pushstring(L, "kd");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		kd = 0.5;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Plastic.kd");
		kd = 0.0;
	} else {
		kd = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading ks
	lua_pushstring(L, "ks");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		ks = 0.5;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Plastic.ks");
		ks = 0.0;
	} else {
		ks = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading roughness
	lua_pushstring(L, "roughness");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		rn = 0.1;
	} else if(lua_tag(L, 2) != LUA_TNUMBER) {
		lua_error(L, "invalid type for Plastic.roughness");
		rn = 0.0;
	} else {
		rn = lua_tonumber(L, 2);
	}
	lua_pop(L, 1);
	// reading specularcolour
	lua_pushstring(L, "specularcolour");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		spc = Colour(1.0, 1.0, 1.0);
	} else if(lua_tag(L, 2) != s->_colour_tag) {
		lua_error(L, "invalid type for Plastic.specularcolour");
	} else {
		spc = *(static_cast<Colour*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 2);
	SurfaceShader *ss = new PlasticSurfaceShader(ka, kd, ks, rn, spc);
	lua_pushusertag(L, ss, s->_surface_tag);

	return 1;
}

int LuaScript::_constantsurface_ctor(lua_State* L)
{
	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Constant");
	}
	lua_pop(L, 1);
	SurfaceShader *ss = new ConstantSurfaceShader();
	lua_pushusertag(L, ss, s->_surface_tag);

	return 1;
}

int LuaScript::_frame_ctor(lua_State* L)
{
	string nm;
	Colour amb;
	int depth, format, width, height;

	// getting and popping upvalue - LuaScript instance
	LuaScript* s = static_cast<LuaScript*>(lua_touserdata(L, -1));
	lua_pop(L, 1);
	// we must get a table
	if(!lua_istable(L, 1)) {
		lua_error(L, "invalid argument to Frame");
	}
	// reading frame buffer type
	lua_pushstring(L, "format");
	lua_gettable(L, 1);
	if(lua_isnumber(L, 2)) {
		format = static_cast<int>(lua_tonumber(L, 2));
	} else {
		lua_error(L, "invalid frame format");
		format = 0;
	}
	lua_pop(L, 1);
	// reading frame buffer name
	lua_pushstring(L, "name");
	lua_gettable(L, 1);
	if(lua_tag(L, 2) == LUA_TSTRING) {
		nm = lua_tostring(L, 2);
	} else {
		lua_error(L, "invalid frame name");
	}
	lua_pop(L, 1);
	// reading tracing depth
	lua_pushstring(L, "depth");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		depth = 1;
	} else if(lua_isnumber(L, 2)) {
		depth = static_cast<int>(lua_tonumber(L, 2));
		if(depth <= 0) {
			lua_error(L, "non-positive tracing depth");
		}
	} else {
		lua_error(L, "invalid tracing depth");
		depth = 0;
	}
	lua_pop(L, 1);
	// reading viewport width
	lua_pushstring(L, "width");
	lua_gettable(L, 1);
	if(lua_isnumber(L, 2)) {
		width = static_cast<int>(lua_tonumber(L, 2));
		if(width <= 0) {
			lua_error(L, "frame with non-positive width");
		}
	} else {
		lua_error(L, "invalid frame width");
		width = 0;
	}
	lua_pop(L, 1);
	// reading viewport height
	lua_pushstring(L, "height");
	lua_gettable(L, 1);
	if(lua_isnumber(L, 2)) {
		height = static_cast<int>(lua_tonumber(L, 2));
		if(height <= 0) {
			lua_error(L, "frame buffer with non-positive height");
		}
	} else {
		lua_error(L, "invalid frame height");
		height = 0;
	}
	lua_pop(L, 1);
	// reading ambient light
	lua_pushstring(L, "ambient");
	lua_gettable(L, 1);
	if(lua_isnil(L, 2)) {
		amb = Colour(0.1, 0.1, 0.1);
	} else if(lua_tag(L, 2) != s->_colour_tag) {
		lua_error(L, "invalid type for Frame.ambient");
	} else {
		amb = *(static_cast<Colour*>(lua_touserdata(L, 2)));
	}
	lua_pop(L, 1);
	// creating scene
	s->_sc = new Scene();
	s->_sc->setAmbient(amb);
	// creating the correct frame buffer
	switch(format) {
		case FB_PNG:
			s->_fb = new PNGFrameBuffer(nm.c_str(), width, height);
			break;
		case FB_TGA:
			s->_fb = new TGAFrameBuffer(nm.c_str(), width, height);
			break;
		default:
			lua_error(L, "invalid frame buffer type");
	}
	// now traversing table and adding objects to scene
	lua_pushnil(L);
	while(lua_next(L, 1)) {
		int tag = lua_tag(L, -1);
		if(tag == s->_camera_tag) {
			Camera* c = static_cast<Camera*>(lua_touserdata(L, -1));
			s->_sc->setCamera(*c);
		} else if(tag == s->_light_tag) {
			Light* l = static_cast<Light*>(lua_touserdata(L, -1));
			s->_sc->addLight(*l);
		} else if(tag == s->_csg_tag || s->isShape(tag)) {
			Shape* p = static_cast<Shape*>(lua_touserdata(L, -1));
			s->_sc->addShape(p);
		}
		lua_pop(L, 1);
	}
	// creating renderer
	s->_rd = new Renderer(*s->_sc, *s->_fb);
	s->_rd->setDepth(depth);
	cout << "Rendering frame " << nm << "...\n";
	s->_rd->render(s->_verbose);
	// cleaning up
	delete s->_rd; s->_rd = 0;
	delete s->_sc; s->_sc = 0;
	delete s->_fb; s->_fb = 0;

	return 0;
}

LuaScript::LuaScript()
	: _verbose(false), _lua_state(0), _sc(0), _rd(0), _fb(0)
{
	// this is now the currently running script
	_lua_script = this;

	// creating a new lua state
	_lua_state = lua_open(0);
	lua_baselibopen(_lua_state);
	lua_mathlibopen(_lua_state);

	// locking this script to avoid it being garbage collected
	lua_pushusertag(_lua_state, this, LUA_ANYTAG);
	_script_ref = lua_ref(_lua_state, 1);

	// framebuffer types
	lua_pushnumber(_lua_state, FB_PNG);
	lua_setglobal(_lua_state, "FB_PNG");
	lua_pushnumber(_lua_state, FB_TGA);
	lua_setglobal(_lua_state, "FB_TGA");

	// points
	_point_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _point_ctor, 1);
	lua_setglobal(_lua_state, "Point");
	// destructor
	lua_pushcfunction(_lua_state, _point_dtor);
	lua_settagmethod(_lua_state, _point_tag, "gc");
	// indexing
	lua_pushcfunction(_lua_state, _point_index);
	lua_settagmethod(_lua_state, _point_tag, "gettable");
	// adding
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _point_add, 1);
	lua_settagmethod(_lua_state, _point_tag, "add");
	// subtracting
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _point_sub, 1);
	lua_settagmethod(_lua_state, _point_tag, "sub");
	// multiplying
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _point_mul, 1);
	lua_settagmethod(_lua_state, _point_tag, "mul");
	// dividing
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _point_div, 1);
	lua_settagmethod(_lua_state, _point_tag, "div");

	// colours
	_colour_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _colour_ctor, 1);
	lua_setglobal(_lua_state, "Colour");
	// destructor
	lua_pushcfunction(_lua_state, _colour_dtor);
	lua_settagmethod(_lua_state, _colour_tag, "gc");
	// indexing
	lua_pushcfunction(_lua_state, _colour_index);
	lua_settagmethod(_lua_state, _colour_tag, "gettable");
	// adding
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _colour_add, 1);
	lua_settagmethod(_lua_state, _colour_tag, "add");
	// subtracting
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _colour_sub, 1);
	lua_settagmethod(_lua_state, _colour_tag, "sub");
	// multiplying
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _colour_mul, 1);
	lua_settagmethod(_lua_state, _colour_tag, "mul");
	// dividing
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _colour_div, 1);
	lua_settagmethod(_lua_state, _colour_tag, "div");
	// some useful constants
	lua_pushusertag(_lua_state, new Colour(0.0, 0.0, 0.0), _colour_tag);
	lua_setglobal(_lua_state, "Black");
	lua_pushusertag(_lua_state, new Colour(1.0, 0.0, 0.0), _colour_tag);
	lua_setglobal(_lua_state, "Red");
	lua_pushusertag(_lua_state, new Colour(0.0, 1.0, 0.0), _colour_tag);
	lua_setglobal(_lua_state, "Green");
	lua_pushusertag(_lua_state, new Colour(0.0, 0.0, 1.0), _colour_tag);
	lua_setglobal(_lua_state, "Blue");
	lua_pushusertag(_lua_state, new Colour(1.0, 1.0, 1.0), _colour_tag);
	lua_setglobal(_lua_state, "White");

	// vectors
	_vector_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _vector_ctor, 1);
	lua_setglobal(_lua_state, "Vector");
	// destructor
	lua_pushcfunction(_lua_state, _vector_dtor);
	lua_settagmethod(_lua_state, _vector_tag, "gc");
	// indexing
	lua_pushcfunction(_lua_state, _vector_index);
	lua_settagmethod(_lua_state, _vector_tag, "gettable");
	// some useful constants
	lua_pushusertag(_lua_state, new Vector(1.0, 0.0, 0.0), _vector_tag);
	lua_setglobal(_lua_state, "x");
	lua_pushusertag(_lua_state, new Vector(0.0, 1.0, 0.0), _vector_tag);
	lua_setglobal(_lua_state, "y");
	lua_pushusertag(_lua_state, new Vector(0.0, 0.0, 1.0), _vector_tag);
	lua_setglobal(_lua_state, "z");

	// lights
	_light_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _light_ctor, 1);
	lua_setglobal(_lua_state, "Light");
	// destructor
	lua_pushcfunction(_lua_state, _light_dtor);
	lua_settagmethod(_lua_state, _light_tag, "gc");

	// cameras
	_camera_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _camera_ctor, 1);
	lua_setglobal(_lua_state, "Camera");
	// destructor
	lua_pushcfunction(_lua_state, _camera_dtor);
	lua_settagmethod(_lua_state, _camera_tag, "gc");

	// csg
	_csg_tag = lua_newtag(_lua_state);
	// constructors
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _union_ctor, 1);
	lua_setglobal(_lua_state, "Union");
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _difference_ctor, 1);
	lua_setglobal(_lua_state, "Difference");
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _intersection_ctor, 1);
	lua_setglobal(_lua_state, "Intersection");

	// boxes
	_box_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _box_ctor, 1);
	lua_setglobal(_lua_state, "Box");

	// cylinders
	_cylinder_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _cylinder_ctor, 1);
	lua_setglobal(_lua_state, "Cylinder");

	// spheres
	_sphere_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _sphere_ctor, 1);
	lua_setglobal(_lua_state, "Sphere");

	// planes
	_plane_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _plane_ctor, 1);
	lua_setglobal(_lua_state, "Plane");

	// torii
	_torus_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _torus_ctor, 1);
	lua_setglobal(_lua_state, "Torus");

	// triangles
	_triangle_tag = lua_newtag(_lua_state);
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _triangle_ctor, 1);
	lua_setglobal(_lua_state, "Triangle");

	// surface shaders
	_surface_tag = lua_newtag(_lua_state);
	// matte surface constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _mattesurface_ctor, 1);
	lua_setglobal(_lua_state, "Matte");
	// plastic surface constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _plasticsurface_ctor, 1);
	lua_setglobal(_lua_state, "Plastic");
	// constant surface constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _constantsurface_ctor, 1);
	lua_setglobal(_lua_state, "Constant");

	// frames
	// constructor
	lua_getref(_lua_state, _script_ref);
	lua_pushcclosure(_lua_state, _frame_ctor, 1);
	lua_setglobal(_lua_state, "Frame");

	// exporting the Shader's API
	LuaScriptAPI::exportLuaScriptAPI(_lua_state);
}

LuaScript::~LuaScript()
{
	_lua_script = 0;

	lua_unref(_lua_state, _script_ref);
	lua_close(_lua_state);
	// cleaning up
	delete _sc;
	delete _rd;
	delete _fb;
}

void LuaScript::exportShaderEnv(const ShaderEnv& env)
{
	// surface colour
	Colour* Cs = new Colour(env.Cs());
	lua_pushusertag(_lua_state, Cs, _colour_tag);
	lua_setglobal(_lua_state, "Cs");
	// surface opacity
	Colour* Os = new Colour(env.Os());
	lua_pushusertag(_lua_state, Os, _colour_tag);
	lua_setglobal(_lua_state, "Os");
	// intersection point
	Point* P = new Point(env.P());
	lua_pushusertag(_lua_state, P, _point_tag);
	lua_setglobal(_lua_state, "P");
	// normal at intersection
	Vector* N = new Vector(env.N());
	lua_pushusertag(_lua_state, N, _vector_tag);
	lua_setglobal(_lua_state, "N");
	// surface parameters
	lua_pushnumber(_lua_state, env.u());
	lua_setglobal(_lua_state, "u");
	lua_pushnumber(_lua_state, env.v());
	lua_setglobal(_lua_state, "v");
	// texture coordinates
	lua_pushnumber(_lua_state, env.s());
	lua_setglobal(_lua_state, "s");
	lua_pushnumber(_lua_state, env.t());
	lua_setglobal(_lua_state, "t");
	// eye position
	Point* E = new Point(env.E());
	lua_pushusertag(_lua_state, E, _point_tag);
	lua_setglobal(_lua_state, "E");
	// incident ray direction
	Vector* I = new Vector(env.I());
	lua_pushusertag(_lua_state, I, _vector_tag);
	lua_setglobal(_lua_state, "I");
}

bool LuaScript::run(const char* filename, bool verbose)
{
	if(filename) {
		_verbose = verbose;
		if(lua_dofile(_lua_state, filename) != 0) {
			// cleaning up
			delete _sc; _sc = 0;
			delete _rd; _rd = 0;
			delete _fb; _fb = 0;
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

#endif

}

