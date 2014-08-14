#include "event.hpp"
#include "exception.hpp"

using namespace riemannpp;

event::event() {
	d_event.reset(riemann_event_new());
}

event::event(const field_list& fields) {
	d_event.reset(riemann_event_new());
	set(fields);
}

event::~event() {
	if (d_event) {
		riemann_event_free(d_event.release());
	}
}

void 
event::set(const field_list& fields) {
	for (auto &t : fields) {
		int result = riemann_event_set(d_event.get(), std::get<0>(t), std::get<1>(t).c_str(), RIEMANN_EVENT_FIELD_NONE);
		if (-1 == result) {
			throw new internal_exception();
		}
	}
}

void 
event::tag_add(const std::string& tag) {
	int result = riemann_event_tag_add(d_event.get(), tag.c_str());
	if (-1 == result) {
		throw new internal_exception();
	}
}

void 
event::attribute_add(const attribute& a) {
	int result = riemann_event_attribute_add(d_event.get(), (riemann_attribute_t*)a);
	if (-1 == result) {
		throw new internal_exception();
	}
}
