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

#ifndef __VIRTUALITY_CSGNODE_H__
#define __VIRTUALITY_CSGNODE_H__

#include <vector>

#include <shape.H>

namespace Virtuality {

class CSGNode : public Shape {
public:
	//! Constructor
	CSGNode();

	//! Destructor
	virtual ~CSGNode();

	//! Adds a child to this node
	void addChild(const Shape* s);

	//! Queries the normal vector at intersection
	virtual Vector normal(const Point& P) const;

protected:
	// childs
	vector<const Shape*> _childs;
};

inline CSGNode::CSGNode()
{
}

inline CSGNode::~CSGNode()
{
	vector<const Shape*>::iterator it;

	// simply runs through list of shapes and deletes them
	for(it = _childs.begin(); it != _childs.end(); it++) {
		delete *it;
	}
	_childs.clear();
}

inline void CSGNode::addChild(const Shape* s)
{
	if(s) {
		_childs.push_back(s);
	}

}

inline Vector CSGNode::normal(const Point& P) const
{
	return Vector(1.0, 0.0, 0.0);
}

}

#endif  // __VIRTUALITY_CSGNODE_H__
