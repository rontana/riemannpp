#ifndef CLIENT_OPTIONS_HPP
#define CLIENT_OPTIONS_HPP

#include <iostream>
#include <string>

namespace client {

	struct options {
		// miscellaneous options
		bool        show_usage;
		bool        show_help;
		bool        show_version;

		// positional options
		std::string command;
		std::string rhost;
		int         rport;

		// send command options
		std::string state;
		std::string service;
		std::string host;
		std::string description;
		std::string attributes;
		std::string tags;
		int64_t     metric_sint64;
		double      metric_dbl;
		float       metric_flt;
		int         ttl;
		bool        tcp;
		bool        udp;

		// query command options
		std::string query;
		bool        result_json;

		options()
			: show_usage(false)
			, show_help(false)
			, show_version(false)
			, command("")
			, rhost("")
			, rport(0)
			, state("")
			, service("")
			, host("")
			, description("")
			, attributes("")
			, tags("")
			, metric_sint64(0)
			, metric_dbl(0.0)
			, metric_flt(0.f)
			, ttl(0)
			, result_json(false)
			, tcp(false)
			, udp(false)
		{}
	};

}

client::options process_command_line(int argc, char const* argv[]);
std::ostream& show_usage(std::ostream& stream);
std::ostream& show_help(std::ostream& stream);

#endif // CLIENT_OPTIONS_HPP
