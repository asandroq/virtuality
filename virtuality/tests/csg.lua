-- CSG demo
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "csg.png",
	width = 640,
	height = 480;

	-- creating camera
	Camera {
		position = Point { x = -1.0, y = 2.0 },
		direction = Vector { x = 1.0, y = -2.0, z = 7.0 }
	},

	-- creating light
	Light {
		colour = White,
		position = Point { y = 30.0, z = -10.0 }
	},

	Intersection {
		-- creating red box
		Box {
			colour = Red,
			point1 = Point { x = -0.5, y = -1.0, z = 6.5 },
			point2 = Point { x =  1.5, y =  1.0, z = 8.5 }
		},
		-- creating blue sphere
		Sphere {
			radius = 1.0,
			colour = Blue,
			centre = Point { z = 7.0 }
		}
	},

	Difference {
		-- creating yellow sphere
		Sphere {
			radius = 1.0,
			colour = Colour { red = 1.0, green = 1.0 },
			centre = Point { x = -1.5, z = 5.5 }
		},
		-- creating green sphere
		Sphere {
			radius = 1.0,
			colour = Green,
			centre = Point { x = -2.0, z = 5.0 }
		}
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
