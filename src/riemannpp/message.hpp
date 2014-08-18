#ifndef RIEMANNPP_MESSAGE_HPP
#define RIEMANNPP_MESSAGE_HPP

#include "event.hpp"
#include "query.hpp"

#include <riemann/riemann-client.h>

#include <memory>
#include <string>
#include <vector>

namespace riemannpp {

	typedef std::vector<event> event_list;

	class message {
		std::unique_ptr<riemann_message_t> d_message;

	public:
		message();

		message(message&& m);

		message(event_list& events);

		message(query& q);

		~message();

		message& operator=(message&& m);

		void set_event(event& e);

		message& operator<<(event &e);

		void set_events(event_list& events);

		void set_query(query& q);

		message& operator<<(query &q);

		operator riemann_message_t*() const { return d_message.get(); }

	private:
		message(const message& m);

		message& operator=(const message& m);
	};

}

#endif // RIEMANNPP_MESSAGE_HPP
