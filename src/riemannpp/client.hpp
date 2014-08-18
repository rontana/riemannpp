#ifndef RIEMANNPP_CLIENT_HPP
#define RIEMANNPP_CLIENT_HPP

#include "message.hpp"

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	enum class client_type {
		none = RIEMANN_CLIENT_NONE,
		tcp  = RIEMANN_CLIENT_TCP,
		udp  = RIEMANN_CLIENT_UDP
	};

	class client {
		riemann_client_t* d_client;

	public:
		client();

		client(client&& c);

		client(client_type type, const std::string& host, int port);

		~client();

		client& operator=(client&& c);

		void connect(client_type type, const std::string& host, int port);

		void disconnect();

		void send_message(const message& m);

		void send_message_oneshot(const message& m);

//		std::unique_ptr<message> recv();

		operator riemann_client_t*() const { return d_client; }

	private:
		client(const client& c);

		client& operator=(const client& c);
	};

}

#endif // RIEMANNPP_CLIENT_HPP
