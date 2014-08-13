#include <riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

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