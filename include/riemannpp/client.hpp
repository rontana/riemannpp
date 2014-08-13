#include <riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	enum class client_type {
		tcp = RIEMANN_CLIENT_TCP,
		udp = RIEMANN_CLIENT_UDP
	};

	class client {
		std::unique_ptr<riemann_client_t> d_client;
		riemann_client_type               d_type;

	public:
		client();

		client(client_type type, const std::string& host, int port);

		~client();

		void connect(client_type type, const std::string& host, int port);

		void disconnect();

		void send_message(const message& m);

		void send_message_oneshot(const message& m);

		std::unique_ptr<message> recv();

		operator riemann_client_t*() const { return d_client.get(); }
	};

}