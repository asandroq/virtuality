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

#ifndef __VIRTUALITY_SHAPE_H__
#define __VIRTUALITY_SHAPE_H__

#include <map>

#include <ray.H>
#include <colour.H>
#include <matrix.H>

namespace Virtuality {

class Shape;

// list of hits
typedef map<double, const Shape*> SpanList;

class Shape {
public:
	//! Constructor
	/*!
	 * \param name the name of this shape
	 */
	Shape();

	//! Destructor
	virtual ~Shape() {}
	
	//! Queries the colour of this shape
	/*!
	 * \sa setColour()
	 */
	Colour colour() const;

	//! Sets the colour of this shape
	/*!
	 * \param colour the new colour of this shape
	 * \sa colour()
	 */
	void setColour(const Colour& colour);

	//! Scales this shape
	/*!
	 * \param x the scale in the x direction
 	 * \param x the scale in the x direction
 	 * \param x the scale in the x direction
	 */
	void scale(double x, double y, double z);

	//! Translates this shape
	/*!
	 * \param x the x component of the translation vector
	 * \param y the y component of the translation vector
	 * \param z the z component of the translation vector
	 */
	void translate(double x, double y, double z);

	//! Rotates this shape
	/*!
	 * \param ax the rotation angle around the x axis
	 * \param ay the rotation angle around the y axis
	 * \param az the rotation angle around the z axis
	 */
	void rotate(double ax, double ay, double az);

	//! transforms the ray with inverse shape's transformation
	Ray transformRay(const Ray& r) const;

	//! Queries if the ray hits the shape
	/*!
	 * the ray's direction is supposed to be normalised
	 */
	virtual void hit(const Ray& r, SpanList* sl) const = 0;

	//! Queries the normal vector at intersection
	virtual Vector normal(const Point& P) const = 0;

	//! Queries the reflected ray at intersection
	virtual Ray reflectedRay(const Ray& r, const Point& P) const;

	//! Queries the transmitted ray at intersection
	virtual Ray transmittedRay(const Ray& r, const Point& P) const;

private:
	// this shape's colour
	Colour _colour;
	// transformation matrix
	Matrix _trans;
	// inverse transfomation matrix
	Matrix _inv;
};

// inline member functions

inline Shape::Shape()
{
}
		
inline Colour Shape::colour() const
{
	return _colour;
}

inline void Shape::setColour(const Colour& c)
{
	_colour = c;
}

inline void Shape::scale(double x, double y, double z)
{
	// sanity checking
	if(isZero(x)) x = 1.0;
	if(isZero(y)) y = 1.0;
	if(isZero(z)) z = 1.0;
	// applying scaling transformation
	_trans *= Matrix(  x, 0.0, 0.0, 0.0,
			 0.0,   y, 0.0, 0.0,
			 0.0, 0.0,   z, 0.0,
			 0.0, 0.0, 0.0, 1.0);
	// applying inverse scaling
	_inv = Matrix(1/x, 0.0, 0.0, 0.0,
		      0.0, 1/y, 0.0, 0.0,
		      0.0, 0.0, 1/z, 0.0,
		      0.0, 0.0, 0.0, 1.0) * _inv;
}

inline void Shape::translate(double x, double y, double z)
{
	// applying translation transformation
	_trans *= Matrix(1.0, 0.0, 0.0,   x,
			 0.0, 1.0, 0.0,   y,
			 0.0, 0.0, 1.0,   z,
			 0.0, 0.0, 0.0, 1.0);
	// applying inverse translation
	_inv = Matrix(1.0, 0.0, 0.0,  -x,
		      0.0, 1.0, 0.0,  -y,
		      0.0, 0.0, 1.0,  -z,
		      0.0, 0.0, 0.0, 1.0) * _inv;
}

inline Ray Shape::transformRay(const Ray& r) const
{
	return _inv*r;
}

}

#endif // __VIRTUALITY_SHAPE_H__
