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

#ifndef __VIRTUALITY_POINT_H__
#define __VIRTUALITY_POINT_H__

#include <math.H>

//! The namespace of all geometry and rendering 
/*!
 * The Virtuality namespace encapsulates all the geometry and rendering
 * algorithms used.
 */
namespace Virtuality {

//! This class represents a simple geometric point
/*!
 * The Point class represents a simple three-dimensional location
 * in space, useful for storing coordinates such as spheres' centres.
 * It may also be selected, meaning it's suitable for user operations.
 */
class Point {
public:
	//! Point's only constructor
	/*!
	 * \param x Point's x coordonate
	 * \param y Point's y coordonate
	 * \param z Point's z coordonate
	 */
	Point(double x = 0.0, double y = 0.0, double z = 0.0)
		: _x(x), _y(y), _z(z) {}

	//! Reads x coordinate
	/*!
	 * \return Point's x coordinate
	 */ 
	double x() const { return _x; }

	//! Reads y coordinate
	/*!
	 * \return Point's y coordinate
	 */ 
	double y() const { return _y; }

	//! Reads z coordinate
	/*!
	 * \return Point's z coordinate
	 */ 
	double z() const { return _z; }

private:
	// point coordinates
	double _x, _y, _z;
};

inline bool operator==(const Point& p1, const Point& p2)
{
	return isZero(p1.x()-p2.x()) &&
	       isZero(p1.y()-p2.y()) &&
	       isZero(p1.z()-p2.z());
}

}

#endif // __VIRTUALITY_POINT_H__
