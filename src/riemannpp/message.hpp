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

		message(const event_list& events);

		message(const query& q);

		~message();

		void set_events(const event_list& events);

		void set_query(const query& q);

		operator riemann_message_t*() const { return d_message.get(); }
	};

}

#endif // RIEMANNPP_MESSAGE_HPP