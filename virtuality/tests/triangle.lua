-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "triangle.png",
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

	Sphere {
		radius = 0.5,
		colour = Blue,
		surface = Matte {},
		centre = Point { x = -1.0, y = 2.0, z = 7.0 }
	},

	Triangle {
		colour = Red,
		surface = Matte {},
		point1 = Point { x =  0.0, y = 3.0, z = 10.0 },
		point2 = Point { x =  3.0, y = 1.0, z =  8.0 },
		point3 = Point { x = -3.0, y = 0.0, z =  6.0 }
	},

	Triangle {
		colour = Red,
		surface = Matte {},
		point1 = Point { x =  0.0, y = 3.0, z = 10.0 },
		point2 = Point { x = -6.0, y = 4.0, z =  8.0 },
		point3 = Point { x = -3.0, y = 0.0, z =  6.0 }
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		surface = Matte {},
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
