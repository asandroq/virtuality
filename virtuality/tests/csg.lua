-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "csg.png",
	width = 640,
	height = 480;

	-- creating camera
	Camera {
		position = Point { y = 3.0 },
		direction = Vector { y = -3.0, z = 7.0 }
	},

	-- creating light
	Light {
		colour = White,
		position = Point { y = 30.0, z = -10.0 }
	},

	Difference {
		-- creating red sphere
		Sphere {
			radius = 1.0,
			colour = Red,
			centre = Point { x = 0.5, z = 7.5 }
		},
		-- creating blue sphere
		Sphere {
			radius = 1.0,
			colour = Blue,
			centre = Point { z = 7.0 }
		}
	},

	Intersection {
		-- creating green sphere
		Sphere {
			radius = 1.0,
			colour = Green,
			centre = Point { x = -2.0, z = 5.0 }
		},
		-- creating yellow sphere
		Sphere {
			radius = 1.0,
			colour = Colour { red = 1.0, green = 1.0 },
			centre = Point { x = -1.5, z = 5.5 }
		}
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
