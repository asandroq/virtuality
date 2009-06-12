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

#include <union.hpp>

namespace Virtuality {

void Union::hit(const Ray& r0, SpanList* sl) const
{
	double f;

	// sanity checking
	if(_childs.empty() || !sl) {
		return;
	}
	// applying inverse transformation to ray
	Ray r = r0.transform(inverseTransformation(), &f);
	// possibly discarding ray
	if(!bounds().hit(r)) {
		return;
	}
	// hitting first child
	_childs[0]->hit(r, sl);
	// hitting remaining childs
	for(unsigned i = 1; i < _childs.size(); i++) {
		SpanList sl1, sl2;
		bool in = false, in1 = false, in2 = false;
		// intersect ray with child
		_childs[i]->hit(r, &sl1);
		if(sl1.empty()) {
			continue;
		}
		// merge the two spans
		SpanList::const_iterator it  = sl->begin();
		SpanList::const_iterator it1 = sl1.begin();
		while(1) {
			double t;
			const Shape* s;
			if(it == sl->end()) {
				if(it1 == sl1.end()) {
					break;
				} else {
					in1 = !in1;
					t = it1->first;
					s = it1->second;
					it1++;
				}
			} else {
				if(it1 == sl1.end()) {
					in = !in;
					t = it->first;
					s = it->second;
					it++;
				} else {
					if(it->first < it1->first) {
						in = !in;
						t = it->first;
						s = it->second;
						it++;
					} else {
						in1 = !in1;
						t = it1->first;
						s = it1->second;
						it1++;
					}
				}
			}
			// this point is in the shape
			if(in || in1) {
				if(!in2) {
					in2 = true;
					sl2.insert(SpanList::value_type(t*f,s));
				}
			} else {
				if(in2) {
					in2 = false;
					sl2.insert(SpanList::value_type(t*f,s));
				}
			}
		}
		swap(*sl, sl2);
	}
}

}
