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

#ifndef __VIRTUALITY_SCENE_H__
#define __VIRTUALITY_SCENE_H__

#include <vector>

#include <light.hpp>
#include <shape.hpp>
#include <camera.hpp>

namespace Virtuality {

//! This class contains the rendering state
class Scene {
public:
	//! Constructor
	/*!
	 */
	Scene();

	//! Destructor
	virtual ~Scene();

	//! Inserts a shape into list
	/*!
	 * \param s pointer to shape which will be inserted
	 */
	void addShape(Shape* s);

	//! Queries the ambient light
	Colour ambient() const;

	//! Sets the ambient light
	void setAmbient(const Colour& c);

	//! Queries one of the lights
	Light light(unsigned i) const;

	//! Queries the number of lights
	unsigned numLights() const;

	//! Inserts a light into scene
	void addLight(const Light& l);

	//! Fires the ray in the scene
	double hit(const Ray& r, Shape** s) const;

	//! Queries if one point "see"  the other
	bool occluded(const Point& p1, const Point& p2) const;

	//! Clears the scene
	void clear();

	//! Queries the scene's camera
	Camera camera() const;

	//! Sets the camera
	void setCamera(const Camera& c);

	//! Queries the background colour
	Colour backgroundColour() const;

	//! Sets the background colour
	void setBackgroundColour(const Colour& c);

private:
	// camera
	Camera _cam;
	// ambient light
	Colour _ambient;
	// background colour
	Colour _bg_colour;
	// list of lights
	vector<Light> _lights;
	// list of shapes
	vector<Shape*> _shapes;
};

inline Scene::Scene()
{
}

inline Scene::~Scene()
{
	clear();
}

inline void Scene::addShape(Shape* s)
{
	if(s) {
		_shapes.push_back(s);
	}
}

inline Colour Scene::ambient() const
{
	return _ambient;
}

inline void Scene::setAmbient(const Colour& c)
{
	_ambient = c;
}

inline Light Scene::light(unsigned i) const
{
	if(i < _lights.size()) {
		return _lights[i];
	} else {
		return Light(Point(), Colour());
	}
}

inline unsigned Scene::numLights() const
{
	return _lights.size();
}

inline void Scene::addLight(const Light& l)
{
	_lights.push_back(l);
}

inline void Scene::clear()
{
	vector<Shape*>::iterator it;

	// simply runs through list of shapes and deletes them
	for(it = _shapes.begin(); it != _shapes.end(); it++) {
		delete *it;
	}
	_shapes.clear();
}

inline Camera Scene::camera() const
{
	return _cam;
}

inline void Scene::setCamera(const Camera& c)
{
	_cam = c;
}

inline Colour Scene::backgroundColour() const
{
	return _bg_colour;
}

inline void Scene::setBackgroundColour(const Colour& c)
{
	_bg_colour = c;
}

}

#endif // __VIRTUALITY_SCENE_H__
