#ifndef RIEMANNPP_MESSAGE_HPP
#define RIEMANNPP_MESSAGE_HPP

#include "event.hpp"
#include "query.hpp"

#include <riemann/riemann-client.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace riemannpp {

	class message {
		std::unique_ptr<riemann_message_t> d_message;

	public:
		message();

		message(riemann_message_t* m);

		message(message&& m);

		message(query& q);

		~message();

		message& operator=(message&& m);

		void set_event(event& e);

		message& operator<<(event &e);

		void set_query(query& q);

		message& operator<<(query &q);

		bool get_ok() const;

		std::string get_error() const;

		std::vector<event> get_events() const;

		query get_query() const;

		std::string to_str() const;

		riemann_message_t* release() { return d_message.release(); }

		operator riemann_message_t*() const { return d_message.get(); }

	private:
		message(const message& m);

		message& operator=(const message& m);
	};

}

std::ostream& operator<<(std::ostream &os, const riemannpp::message& m);

#endif // RIEMANNPP_MESSAGE_HPP
