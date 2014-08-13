#include "message.hpp"
#include "exception.hpp"

using namespace riemannpp;

message::message() {
	d_client.reset(riemann_message_new());
}

message(const event_list& events) {
	d_client.reset(riemann_message_new());
	set_events(events);
}

message(const query& q) {
	d_client.reset(riemann_message_new());
	set_query(q);
}

message::~message() {
	if (d_message) {
		riemann_message_free(d_message.release());
	}
}

void set_events(const event_list& events) {
	for (auto event : events) {
		int result = riemann_message_set_events_n(d_message.get(), 1, event);
		if (-1 == result) {
			throw new riemann_internal_exception();
		}
	}
}

void set_query(const query& q) {
	int result = riemann_message_set_query(d_message.get(), q);
	if (-1 == result) {
		throw new riemann_internal_exception();
	}
}