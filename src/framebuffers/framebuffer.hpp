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

#ifndef __VIRTUALITY_FRAMEBUFFER_H__
#define __VIRTUALITY_FRAMEBUFFER_H__

#include <color.hpp>

namespace Virtuality {

class FrameBuffer {
public:
	//! Constructor
	FrameBuffer(int w = 0, int h = 0);

	//! Destructor
	virtual ~FrameBuffer();

	//! Adds a new scanline to the frame buffer
	virtual bool addScanLine(const Colour* pixels) = 0;

	//! Queries the framebuffer's width
	int width() const;

	//! Queries the framebuffer's height
	int height() const;

private:
	// framebuffer's dimensions
	int _w, _h;
};

inline FrameBuffer::FrameBuffer(int w, int h)
	: _w(w), _h(h)
{
}

inline FrameBuffer::~FrameBuffer()
{
}

inline int FrameBuffer::width() const
{
	return _w;
}

inline int FrameBuffer::height() const
{
	return _h;
}

}

#endif  // __VIRTUALITY_FRAMEBUFFER_H__
