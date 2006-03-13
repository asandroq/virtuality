#
# $Id$
#
# The Virtuality Renderer
# Copyright (C) 2001 Alex Sandro Queiroz e Silva
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# To contact the author send eletronic mail to asandro@lcg.dc.ufc.br
#

#
# Virtuality's executable makefile
#

bin_PROGRAMS = virtuality

virtuality_SOURCES = boundingbox.hpp boundingbox.cpp \
		     camera.hpp \
		     colour.hpp colour.cpp \
		     light.hpp \
		     luascript.hpp luascript.cpp \
		     luascriptapi.hpp luascriptapi.cpp \
		     main.cpp \
		     math.hpp math.cpp \
		     matrix.hpp matrix.cpp \
		     point.hpp \
		     ray.hpp \
		     renderer.hpp renderer.cpp \
		     scene.hpp scene.cpp \
		     scriptapi.hpp scriptapi.cpp \
		     shaderenv.hpp \
		     vector.hpp
virtuality_LDADD =   ../framebuffers/libframebuffers.a \
		     ../shaders/libshaders.a \
		     ../shapes/libshapes.a

INCLUDES = -I../framebuffers -I../shaders -I../shapes
AM_CXXFLAGS = -Wall -Wno-trigraphs -ansi -D_XOPEN_SOURCE -ffast-math -fno-rtti -fno-exceptions

AUTOMAKE_OPTIONS = foreign

# Done.

