/*
 * $Id$
 *
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
 * To contact the author send eletronic mail to asandro@lcg.dc.ufc.br
 */

#include <ctime>
#include <unistd.h>
#include <iostream>

#include <script.H>

using namespace Virtuality;

static void usage()
{
	cout << "Program usage:\n\n";
	cout << "virtuality [options] scene-file\n\n";
	cout << "Options:\n\n";
	cout << "  -h\tShow this help screen\n";
	cout << "  -v\tPrint diagnostics to standard output\n";
}

int main(int argc, char *argv[])
{
	int i;
	bool verbose = false;

	// the usual copyright notice
	cout << "The Virtuality Renderer\n";
	cout << "Copyright (c) 2001, Alex Sandro Queiroz e Silva\n";
	cout << "This program comes with no warranty!\n\n";
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
				cerr << argv[0] << ": option -" << c;
				cerr << " is invalid\n";
				cerr << "Use '" << argv[0] << " -h' for a ";
				cerr << "complete list of options\n";
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
	Script script;
	cout << "Processing " << argv[optind] << "...\n";
	script.run(argv[optind], verbose);
	cout << "Processing of " << argv[optind] << " finished.\n";

	return 0;
}
