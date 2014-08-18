#include "message.hpp"
#include "exception.hpp"

using namespace riemannpp;

message::message() {
	d_message.reset(riemann_message_new());
}

message::message(message&& m) {
	*this = std::move(m);
}

message::message(event_list& events) {
	d_message.reset(riemann_message_new());
	set_events(events);
}

message::message(query& q) {
	d_message.reset(riemann_message_new());
	set_query(q);
}

message::~message() {
	if (d_message) {
		riemann_message_free(d_message.release());
	}
}

message&
message::operator=(message&& m) {
	d_message = std::move(m.d_message);
	return (*this);
}

void
message::set_event(event& e) {
	riemann_event_t* evp = (riemann_event_t*)e;
	int result = riemann_message_set_events_n(d_message.get(), 1, &evp);
	if (-1 == result) {
		throw new internal_exception();
	}
}

message&
message::operator<<(event &e) {
	return (*this);
}

void
message::set_events(event_list& events) {
	for (auto &e : events) {
		set_event(e);
	}
}

void
message::set_query(query& q) {
	int result = riemann_message_set_query(d_message.get(), (riemann_query_t*)q);
	if (-1 == result) {
		throw new internal_exception();
	}
}

message&
message::operator<<(query &q) {
	set_query(q);
	return (*this);
}
