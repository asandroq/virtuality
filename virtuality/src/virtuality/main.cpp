/*
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
 * To contact the author send eletronic mail to ventonegro@ventonegro.org
 */

#include <ctime>
#include <unistd.h>
#include <iostream>

#include <luascript.hpp>

using namespace Virtuality;

static void usage()
{
	std::cout << "Program usage:\n\n";
	std::cout << "virtuality [options] scene-file\n\n";
	std::cout << "Options:\n\n";
	std::cout << "  -h\tShow this help screen\n";
	std::cout << "  -v\tPrint diagnostics to standard output\n";
}

int main(int argc, char *argv[])
{
	int i;
	bool verbose = false;

	// the usual copyright notice
	std::cout << "The Virtuality Renderer\n";
	std::cout << "Copyright (c) 2001 Alex Sandro Queiroz e Silva\n";
	std::cout << "This program comes with no warranty!\n\n";
	// reading options
	opterr = 0;
	while((i = getopt(argc, argv, "hv")) != -1) {
		switch(i) {
			case 'h':
				usage();
				exit(0);
			case 'v':
				verbose = true;
				break;
			case '?':
				char c = static_cast<char>(optopt);
				std::cerr << argv[0] << ": option -" << c;
				std::cerr << " is invalid\n";
				std::cerr << "Use '"<< argv[0]<< " -h' for a ";
				std::cerr << "complete list of options\n";
				exit(1);
		};
	}
	// checking if we have a file
	if(!argv[optind]) {
		usage();
		exit(1);
	}
	srand(time(0));
	// running file
	LuaScript script;
	std::cout << "Processing " << argv[optind] << "...\n";
	script.run(argv[optind], verbose);
	std::cout << "Processing of " << argv[optind] << " finished.\n";

	return 0;
}
