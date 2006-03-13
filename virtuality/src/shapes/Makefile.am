#
# $Id$
# 
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
# Virtuality's shape library makefile
#

noinst_LIBRARIES = libshapes.a

libshapes_a_SOURCES = box.hpp box.cpp \
		      cylinder.hpp cylinder.cpp \
		      csgnode.hpp \
		      difference.hpp difference.cpp \
		      intersection.hpp intersection.cpp \
		      plane.hpp plane.cpp \
		      shape.hpp shape.cpp \
		      sphere.hpp sphere.cpp \
		      torus.hpp torus.cpp \
		      triangle.hpp triangle.cpp \
		      union.hpp union.cpp

INCLUDES = -I../shaders -I../virtuality
AM_CXXFLAGS = -Wall -Wno-trigraphs -ansi -ffast-math -fno-rtti -fno-exceptions

AUTOMAKE_OPTIONS = foreign

# Done.

