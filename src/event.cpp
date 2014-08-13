#include "event.hpp"

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
set(const field_list& fields) {
	for (auto t : fields) {
		int result = riemann_event_set_one(d_event.get(), std::get<0>(t), std::get<1>(t));
		if (-1 == result) {
			throw new riemann_internal_exception();
		}
	}
}

void 
tag_add(const std::string& tag) {
	int result = riemann_event_tag_add(d_event.get(), tag.c_str());
	if (-1 == result) {
		throw new riemann_internal_exception();
	}
}

void 
attribute_add(const attribute& a) {
	int result = riemann_event_tag_add(d_event.get(), a;
	if (-1 == result) {
		throw new riemann_internal_exception();
	}
}