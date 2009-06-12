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
 * To contact the author send eletronic mail to asandro@lcg.dc.ufc.br
 */

#ifndef __VIRTUALITY_LIGHT_H__
#define __VIRTUALITY_LIGHT_H__

#include <point.hpp>
#include <color.hpp>

namespace Virtuality {

class Light {
public:
	//! Constructor
	Light(const Point& pos, const Colour& col);

	//! Destructor
	~Light();

	//! Queries the light's position
	Point position() const;

	//! Queries the light's colour
	Colour colour() const;

private:
	// light's position
	Point _pos;
	// light's colour
	Colour _colour;
};

inline Light::Light(const Point& pos, const Colour& col)
	: _pos(pos), _colour(col)
{
}

inline Light::~Light()
{
}

inline Point Light::position() const
{
	return _pos;
}

inline Colour Light::colour() const
{
	return _colour;
}

}

#endif  // __VIRTUALITY_LIGHT_H__
