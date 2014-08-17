#include "options.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace bpo = boost::program_options;

using namespace client;
using namespace std;

bpo::options_description 
miscellaneous_options()
{
	bpo::options_description options("Miscellaneous Options");
	options.add_options()
		( "version", "display version" )
		( "help",    "show this help page" )
		;
	return options;
}

options 
process_command_line(int argc, char const* argv[]) {
	bpo::positional_options_description arguments;
	arguments.add("operation", 1);

	bpo::options_description all;
	all.add_options()
		( "operation", "either query or send" )
		;
	all.add(miscellaneous_options());

	bpo::variables_map vm;
	options ops;

	try {
		bpo::store(bpo::command_line_parser(argc, argv).options(all).positional(arguments).run(), vm);
	} catch(bpo::too_many_positional_options_error& e) {
		cerr << "Too many arguments provided." << endl;
		ops.show_usage = true;
	} catch(bpo::unknown_option& e) {
		cerr << "Unknown option '" << e.get_option_name() << "'." << endl;
		ops.show_usage = true;
	} catch(bpo::error& e) {
		cerr << "command line parse error: " << e.what() << "'." << endl;
		ops.show_usage = true;
	}

	ops.show_version = ( vm.count( "version" ) > 0 );
	ops.show_help = ( vm.count( "help" ) > 0 );

	return ops;
}

ostream& 
show_usage(ostream& stream) {
	stream << "Usage: riemannpp query 'string'" << endl;
	return stream;
}

ostream& 
show_help(ostream& stream) {
	stream << miscellaneous_options() << endl;
	return stream;
}