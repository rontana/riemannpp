#include "message.hpp"
#include "exception.hpp"

using namespace riemannpp;

message::message() {
	d_message.reset(riemann_message_new());
}

message::message(const event_list& events) {
	d_message.reset(riemann_message_new());
	set_events(events);
}

message::message(const query& q) {
	d_message.reset(riemann_message_new());
	set_query(q);
}

message::~message() {
	if (d_message) {
		riemann_message_free(d_message.release());
	}
}

void
message::set_events(const event_list& events) {
	for (auto &event : events) {
		riemann_event_t* evp = (riemann_event_t*)event;
		int result = riemann_message_set_events_n(d_message.get(), 1, &evp);
		if (-1 == result) {
			throw new internal_exception();
		}
	}
}

void
message::set_query(const query& q) {
	int result = riemann_message_set_query(d_message.get(), (riemann_query_t*)q);
	if (-1 == result) {
		throw new internal_exception();
	}
}
