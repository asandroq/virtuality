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

#ifndef __VIRTUALITY_PNGFRAMEBUFFER_H__
#define __VIRTUALITY_PNGFRAMEBUFFER_H__

#if defined(HAVE_PNG_H) && defined(HAVE_LIBPNG)
#  define HAVE_PNG
#endif

#ifdef HAVE_PNG
#  include <png.h>
#endif

#include <framebuffer.hpp>

namespace Virtuality {

class PNGFrameBuffer : public FrameBuffer {
public:
	//! Constructor
	PNGFrameBuffer(const char* path = 0, int w = 0, int h = 0);

	//! Destructor
	~PNGFrameBuffer();

	//! Adds a scanline to the framebuffer
	bool addScanLine(const Colour* pixels);

private:
#ifdef HAVE_PNG
	// libpng data
	png_infop info_ptr;
	png_structp png_ptr;
#endif
};

}

#endif  // __VIRTUALITY_PNGFRAMEBUFFER_H__
