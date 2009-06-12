-- Scene with tree balls
-- Alex Sandro Queiroz e Silva

Frame {
	format = FB_PNG,
	name = "balls.png",
	width = 800,
	height = 600,
	ambient = Colour { red = 0.2, green = 0.2, blue = 0.2 };

	-- creating camera
	Camera {
		position  = Point  { y =  3.0 },
		direction = Vector { y = -3.0, z = 7.0 }
	},

	-- creating light
	Light {
		colour = White,
		position = Point { y = 30.0, z = -10.0 }
	},

	-- creating blue box
	Box {
		colour = Blue,
		surface = Matte {},
		point1 = Point { x = -1.0, y = -1.0, z = -1.0 },
		point2 = Point { x =  1.0, y =  1.0, z =  1.0 },

		rotate = Vector { y = 45.0 },
		translate = Vector { z = 7.0 }
	},

	-- creating red sphere
	Sphere {
		radius = 1.0,
		colour = Red,
		centre = Point {},
		surface = Matte {},

		scale  = Vector { y = 2.0, z = 2.0 },
		translate = Vector { x = 2.0, y = 1.0, z = 9.0 }
	},

	-- creating green sphere
	Sphere {
		radius = 1.0,
		colour = Green,
		surface = Matte {},
		centre = Point { x = -2.0, z = 5.0 }
	},

	-- creating plane
	Plane {
		normal = y,
		distance = -1.0,
		surface = Matte {},
		colour = Colour { red = 0.7, green = 0.7, blue = 0.7 }
	}
}
