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

#include <cstring>
#include <tgaframebuffer.H>

namespace Virtuality {

typedef unsigned char byte;

TGAFrameBuffer::TGAFrameBuffer(const char* path, int w, int h)
	: FrameBuffer(w, h)
{
	// cannot have a non-positive size framebuffer
	if(!(width() > 0 && height() > 0)) {
		return;
	}
	// tries to open output file
	_file.open(path);
	if(!_file.is_open()) {
		return;
	}
	// writes file header
	byte header[18];
	memset(header, 0x00, 18*sizeof(byte));
	header[2] = 2;
	header[12] = width()  % 256;
	header[13] = width()  / 256;
	header[14] = height() % 256;
	header[15] = height() / 256;
	header[16] = 24;
	header[17] = 0x20;
	_file.write(header, 18*sizeof(byte));
}

TGAFrameBuffer::~TGAFrameBuffer()
{
	_file.close();
}

bool TGAFrameBuffer::addScanLine(const Colour* pixels)
{
	// sanity checking
	if(!pixels || !_file.is_open()) {
		return false;
	}
	// writing scanline
	byte* b = new byte[3*width()];
	for(int i = 0; i < width(); i++) {
		b[3*i  ] = static_cast<byte>(pixels[i].blue() *255.0);
		b[3*i+1] = static_cast<byte>(pixels[i].green()*255.0);
		b[3*i+2] = static_cast<byte>(pixels[i].red()  *255.0);
	}
	_file.write(b, 3*sizeof(byte)*width());
	delete [] b;

	return true;
}

}
