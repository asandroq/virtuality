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

#ifndef __VIRTUALITY_DIFFERENCE_H__
#define __VIRTUALITY_DIFFERENCE_H__

#include <csgnode.hpp>

namespace Virtuality {

class Difference : public CSGNode {
public:
	//! Constructor
	Difference();

	//! Destructor
	virtual ~Difference();

	//! Queries if the ray hits the shape
	/*!
	 * the ray's direction is supposed to be normalised
	 */
	virtual void hit(const Ray& r, SpanList *sl) const;
};

inline Difference::Difference()
	: CSGNode()
{
}

inline Difference::~Difference()
{
}

}

#endif  // __VIRTUALITY_DIFFERENCE_H__
