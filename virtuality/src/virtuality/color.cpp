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

#include <color.hpp>

namespace Virtuality {

Colour::Colour(int r, int g, int b)
{
	setRed(r);
	setGreen(g);
	setBlue(b);
}

Colour::Colour(double r, double g, double b)
{
	setRed(r);
	setGreen(g);
	setBlue(b);
}

void Colour::setRed(int r)
{
	r = clamp(r, 0, 255);
	// converting to 0.0-1.0
	_r = r / 255.0;
}

void Colour::setGreen(int g)
{
	g = clamp(g, 0, 255);
	// converting to 0.0-1.0
	_g = g / 255.0;
}

void Colour::setBlue(int b)
{
	b = clamp(b, 0, 255);
	// converting to 0.0-1.0
	_b = b / 255.0;
}

}

// Done.
