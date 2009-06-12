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

#ifndef __VIRTUALITY_CAMERA_H__
#define __VIRTUALITY_CAMERA_H__

#include <vector.hpp>

namespace Virtuality {

class Camera {
public:
	//! Constructor
	Camera(const Point& pos = Point(),
		const Vector& dir = Vector(0.0, 0.0, 1.0),
		const Vector& up  = Vector(0.0, 1.0, 0.0),
		const Vector& rig = Vector(4.0/3.0, 0.0, 0.0));

	//! Destructor
	~Camera();

	//! Queries the camera location
	Point position() const;

	//! Queries the camera view direction
	Vector direction() const;

	//! Queries the view up vector
	Vector up() const;

	//! Queries the right vector
	Vector right() const;

private:
	Point _pos;
	Vector _dir, _up, _right;
};

inline Camera::Camera(const Point& pos, const Vector& dir,
			const Vector& up, const Vector& rig)
	: _pos(pos), _dir(dir), _up(up), _right(rig)
{
}

inline Camera::~Camera()
{
}

inline Point Camera::position() const
{
	return _pos;
}

inline Vector Camera::direction() const
{
	return _dir;
}

inline Vector Camera::up() const
{
	return _up;
}

inline Vector Camera::right() const
{
	return _right;
}

}

#endif  // __VIRTUALITY_CAMERA_H__
