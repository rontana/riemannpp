#include "event.hpp"
#include "exception.hpp"

using namespace riemannpp;

event::event() {
	d_event.reset(riemann_event_new());
}

event::event(event&& e) {
	*this = std::move(e);
}

event::~event() {
	if (d_event) {
		riemann_event_free(d_event.release());
	}
}

event&
event::operator=(event&& e) {
	d_event = std::move(e.d_event);
	return (*this);
}

template<>
void event::set(const event_field field, const std::string& value) {
	int result = riemann_event_set(d_event.get(), field, value.c_str(), RIEMANN_EVENT_FIELD_NONE);
	if (-1 == result) {
		throw new internal_exception();
	}
}

void 
event::tag_add(const std::string& tag) {
	int result = riemann_event_tag_add(d_event.get(), tag.c_str());
	if (-1 == result) {
		throw new internal_exception();
	}
}

event&
event::operator<<(std::string t) {
	tag_add(t);
	return (*this);
}

void 
event::attribute_add(attribute&& a) {
	int result = riemann_event_attribute_add(d_event.get(), a.release());
	if (-1 == result) {
		throw new internal_exception();
	}
}

event&
event::operator<<(attribute&& a) {
	attribute_add(std::move(a));
	return (*this);
}
