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
#include <boundingbox.H>

#include <surfaceshader.H>

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
	virtual ~Shape();
	
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

	//! Queries the surface shader of this shape
	SurfaceShader* surfaceShader() const;

	//! Sets the shader of this shape
	void setSurfaceShader(SurfaceShader* shader);

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

	//! queries the transformation matrix
	Matrix transformation() const;

	//! queries the inverse transformation matrix
	Matrix inverseTransformation() const;

	//! transforms a normal vector, keeping it normal
	Vector transformNormal(const Vector& v) const;

	//! queries the bounding box of this object
	BoundingBox bounds() const;

	//! sets the bounding box for this object
	void setBounds(const BoundingBox& bb);

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
	// this shape's shader
	SurfaceShader* _shader;
	// transformation matrix
	Matrix _trans;
	// inverse transfomation matrix
	Matrix _inv;
	// bounding box
	BoundingBox _bb;
};

// inline member functions

inline Shape::Shape()
	: _shader(0)
{
}
		
inline Shape::~Shape()
{
	delete _shader;
}

inline Colour Shape::colour() const
{
	return _colour;
}

inline void Shape::setColour(const Colour& c)
{
	_colour = c;
}

inline SurfaceShader* Shape::surfaceShader() const
{
	return _shader;
}

inline void Shape::setSurfaceShader(SurfaceShader* shader)
{
	_shader = shader;
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

inline Matrix Shape::transformation() const
{
	return _trans;
}

inline Matrix Shape::inverseTransformation() const
{
	return _inv;
}

inline Vector Shape::transformNormal(const Vector& v) const
{
	/* 
	 * to transform the normal, we multiply it by the transpose
	 * of the inverse transformation
	 */
	Matrix tmp(_inv.e11(), _inv.e21(), _inv.e31(), 0.0,
		   _inv.e12(), _inv.e22(), _inv.e32(), 0.0,
		   _inv.e13(), _inv.e23(), _inv.e33(), 0.0,
			  0.0,        0.0,        0.0, 1.0);

	return tmp * v;
}

inline BoundingBox Shape::bounds() const
{
	return _bb;
}

inline void Shape::setBounds(const BoundingBox& bb)
{
	_bb = bb;
}

}

#endif  // __VIRTUALITY_SHAPE_H__
