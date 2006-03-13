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

#ifndef __VIRTUALITY_RENDERER_H__
#define __VIRTUALITY_RENDERER_H__

#include <ctime>

#include <scene.hpp>
#include <framebuffer.hpp>

namespace Virtuality {

class Renderer {
public:
	//! Constructor
	Renderer(const Scene& s, FrameBuffer& f);

	//! Destructor
	virtual ~Renderer();

	//! Queries maximum recursive depth
	unsigned depth() const;

	//! Sets maximum recursive depth
	void setDepth(unsigned d);
	
	//! Renders the scene into the frame buffer
	virtual void render(bool verbose) const;

private:
	// max recursive depth
	unsigned _max_depth;
	// current recursive depth
	mutable unsigned _curr_depth;
	// pointer to scene
	const Scene *_scn;
	// pointer to frame buffer
	FrameBuffer *_fb;
	// print statistics
	void printStatistics(clock_t t, int h, int i) const;
	// traces rays into scene
	Colour shade(const Ray& r) const;
};

inline Renderer::Renderer(const Scene& s, FrameBuffer& f)
	: _max_depth(2), _curr_depth(0), _scn(&s), _fb(&f)
{
}

inline Renderer::~Renderer()
{
}

inline unsigned Renderer::depth() const
{
	return _max_depth;
}

inline void Renderer::setDepth(unsigned d)
{
	_max_depth = d;
}

}

#endif // __VIRTUALITY_RENDERER_H__
