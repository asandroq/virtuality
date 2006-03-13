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

#ifndef __VIRTUALITY_COLOUR_H__
#define __VIRTUALITY_COLOUR_H__

#include <math.hpp>

namespace Virtuality {

//! This class represents a RGB-coded colour
/*!
 * The Colour class is used to encode the colour of the scene objects,
 * in a RGB format. The values allowed for each component is in the range
 * [0.0,1.0] or [0,255], but the latter is converted internally to the
 * former.
 */
class Colour
{
public:
	//! Colour constructor taking ints
	/*!
	 * \param r the red   component, in the range [0, 255]
	 * \param g the green component, in the range [0, 255]
	 * \param b the blue  component, in the range [0, 255]
	 */
	Colour(int r, int g = 0, int b = 0);

	//! Colour constructor taking doubles
	/*!
	 * \param r the red   component, in the range [0.0, 1.0]
	 * \param g the green component, in the range [0.0, 1.0]
	 * \param b the blue  component, in the range [0.0, 1.0]
	 */
	Colour(double r = 0.0, double g = 0.0, double b = 0.0);

	// acessing and setting red components
	double red() const;
	void setRed(int);
	void setRed(double);

	// acessing and setting green components
	double green() const;
	void setGreen(int);
	void setGreen(double);

	// acessing and setting blue components
	double blue() const;
	void setBlue(int);
	void setBlue(double);

	// scales a colour
	Colour& operator*=(double t);

	//! Adds a colour to this
	Colour& operator+=(const Colour& c);

	//! Multiplies component by component
	Colour& operator*=(const Colour& c);

private:
	// colour components
	double _r, _g, _b;
};

inline double Colour::red() const
{
	return _r;
}

inline void Colour::setRed(double r)
{
	_r = clamp(r, 0.0, 1.0);
}

inline double Colour::green() const
{
	return _g;
}

inline void Colour::setGreen(double g)
{
	_g = clamp(g, 0.0, 1.0);
}

inline double Colour::blue() const
{
	return _b;
}

inline void Colour::setBlue(double b)
{
	_b = clamp(b, 0.0, 1.0);
}

inline Colour& Colour::operator*=(double t)
{
	setRed(_r*t);
	setGreen(_g*t);
	setBlue(_b*t);

	return *this;
}

inline Colour& Colour::operator+=(const Colour& c)
{
	setRed(this->_r+c._r);	
	setGreen(this->_g+c._g);	
	setBlue(this->_b+c._b);	

	return *this;
}

inline Colour& Colour::operator*=(const Colour& c)
{
	setRed(this->_r*c._r);	
	setGreen(this->_g*c._g);	
	setBlue(this->_b*c._b);	

	return *this;
}

inline Colour operator*(double t, const Colour& c)
{
	Colour c1 = c;
	return c1 *= t;
}

inline Colour operator+(const Colour& c1, const Colour& c2)
{
	Colour c3  = c1;
	return c3 += c2;
}

inline Colour operator*(const Colour& c1, const Colour& c2)
{
	Colour c3  = c1;
	return c3 *= c2;
}

}

#endif // __VIRTUALITY_COLOUR_H__
