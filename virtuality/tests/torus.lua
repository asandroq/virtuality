-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "torus.png",
	width = 800,
	height = 600;

	-- creating camera
	Camera {
		direction = z
	},

	-- creating light
	Light {
		colour = White,
		position = Point { y = 30.0, z = -10.0 }
	},

	Torus {
		major = 1.0,
		minor = 0.5,
		colour = Blue,
		rotate = Vector { x = -45.0 },
		translate = Vector { z = 7.0 }
	},

	Torus {
		major = 1.0,
		minor = 0.5,
		colour = Red,
		rotate = Vector { x = -45.0 },
		translate = Vector { x = -3.0, z = 7.0 }
	},

	Torus {
		major = 1.0,
		minor = 0.5,
		colour = Green,
		rotate = Vector { x = -45.0 },
		translate = Vector { x = 3.0, z = 7.0 }
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
