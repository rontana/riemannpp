#include "options.hpp"
#include <riemannpp/riemannpp.hpp>
#include <riemann/riemann-client.h>
#include <iostream>

namespace rpp = riemannpp;

using namespace client;
using namespace std;

int main(int argc, char const* argv[]) {
	options const ops = process_command_line(argc, argv);
	if (ops.show_version) {
		cout << "riemannpp version 0.1.0" << endl;
		return EXIT_FAILURE;
	}
	if (ops.show_usage || ops.show_help) {
		show_usage(cout);
		if (ops.show_help) {
			cout << endl << show_help(cout);
		}
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}