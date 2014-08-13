#include "client.hpp"

using namespace riemannpp;

client::client() {
	d_client.reset(riemann_client_new());
}

client::client(client_type type, const std::string& host, int port) {
	d_client.reset(riemann_client_create(type, host.c_str(), port));
}

client::~client() {
	if (d_client) {
		riemann_client_free(d_client.release());
	}
}

void 
client::connect(client_type type, const std::string& host, int port) {
	int result = riemann_client_connect(d_client.get(), type, host.c_str(), port);
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

void 
client::disconnect() {
	int result = riemann_client_disconnect(d_client.get());
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

void 
client::send_message(const message& m) {
	int result = riemann_client_send_message(d_client.get(), m);
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

void 
client::send_message_oneshot(const message& m) {
	int result = riemann_client_send_message_oneshot(d_client.get(), m);
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

std::unique_ptr<message> 
client::recv() {
	return std::unique_ptr(riemann_client_recv_message(d_client.get()));
}