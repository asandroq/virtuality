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

#include <pngframebuffer.H>

namespace Virtuality {

PNGFrameBuffer::PNGFrameBuffer(const char* path, int w, int h)
	: FrameBuffer(w, h), info_ptr(0), png_ptr(0)
{
#ifdef HAVE_PNG
	FILE* fp = 0;

	// cannot have a non-positive size framebuffer
	if(!(width() > 0 && height() > 0)) {
		return;
	}
	// tries to open output file
	fp = fopen(path, "wb");
	if(!fp) {
		return;
	}
	// create png_struct
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);
	// setting up io
	png_init_io(png_ptr, fp);
	// writing reader
	png_set_IHDR(png_ptr, info_ptr, w, h, 8,
		PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_set_gAMA(png_ptr, info_ptr, 1.0);
	png_write_info(png_ptr, info_ptr);
#endif
}

PNGFrameBuffer::~PNGFrameBuffer()
{
#ifdef HAVE_PNG
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
#endif
}

bool PNGFrameBuffer::addScanLine(const Colour* pixels)
{
#ifdef HAVE_PNG
	// sanity checking
	if(!pixels || !png_ptr) {
		return false;
	}
	png_bytep sl = new png_byte[3*width()];
	for(int i = 0; i < width(); i++) {
		sl[3*i]   = static_cast<png_byte>(pixels[i].red()  *255.0);
		sl[3*i+1] = static_cast<png_byte>(pixels[i].green()*255.0);
		sl[3*i+2] = static_cast<png_byte>(pixels[i].blue() *255.0);
	}
	png_write_rows(png_ptr, &sl, 1);
	delete sl;

	return true;
#endif
}

}
