-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	kind = FB_PNG,
	name = "cylinder.png",
	width = 800,
	height = 600,
	ambient = Colour { red = 0.2, green = 0.2, blue = 0.2 };

	-- creating camera
	Camera {
		direction = z
	},

	-- creating light
	Light {
		colour = White,
		position = Point { y = 30.0, z = -10.0 }
	},

	Cylinder {
		radius = 1.0,
		colour = Blue,
		point1 = Point { x =  3.0, z =  7.0 },
		point2 = Point { x = -3.0, z = 50.0 },
		surface = Matte { ka = 0.7, kd = 0.7 }
	},

	Cylinder {
		radius = 1.0,
		colour = Red,
		surface = Plastic {},
		point1 = Point { x =  2.0, y = 1.0, z = 8.0 },
		point2 = Point { x = -2.0, y = 2.0, z = 8.0 }
	},

	Cylinder {
		radius = 1.0,
		colour = Green,
		scale = Vector { z = 2.0 },
		translate = Vector { z = 7.0 },
		point1 = Point { x = -3.0, y = -1.0 },
		point2 = Point { x = -3.0, y =  1.0 },
		surface = Plastic { ka = 0.5, kd = 0.7,
					ks = 0.7, roughness = 0.02 }
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		surface = Matte {},
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
