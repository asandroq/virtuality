-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "balls.png",
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

	-- creating blue sphere
	Sphere {
		radius = 1.0,
		colour = Blue,
		centre = Point { z = 7.0 }
	},

	-- creating red sphere
	Sphere {
		radius = 1.0,
		colour = Red,
		centre = Point { x = 2.0, z = 9.0 }
	},

	-- creating green sphere
	Sphere {
		radius = 1.0,
		colour = Green,
		centre = Point { x = -2.0, z = 5.0 }
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}