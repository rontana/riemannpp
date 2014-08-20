#include "event.hpp"
#include "exception.hpp"

using namespace riemannpp;

event::event()
	: d_event(riemann_event_new())
{}

event::event(riemann_event_t* e)
	: d_event(e)
{}

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

int64_t
event::get_time() {
	if (d_event) {
		return (d_event->time);
	}
	return 0;
}

std::string
event::get_state() {
	if (d_event && d_event->state) {
		return (d_event->state);
	}
	return "";
}

std::string
event::get_service() {
	if (d_event && d_event->service) {
		return (d_event->service);
	}
	return "";
}

std::string
event::get_host() {
	if (d_event && d_event->host) {
		return (d_event->host);
	}
	return "";
}

std::string
event::get_description() {
	if (d_event && d_event->description) {
		return (d_event->description);
	}
	return "";
}

float
event::get_ttl() {
	if (d_event && d_event->has_ttl) {
		return (d_event->ttl);
	}
	return 0.f;
}

template<>
int64_t event::get_metric() {
	if (d_event && d_event->has_metric_sint64) {
		return (d_event->metric_sint64);
	}
	return 0;
}

template<>
float event::get_metric() {
	if (d_event && d_event->has_metric_f) {
		return (d_event->metric_f);
	}
	return 0.f;
}

template<>
double event::get_metric() {
	if (d_event && d_event->has_metric_d) {
		return (d_event->metric_d);
	}
	return 0.;
}

void event::set_state(std::string val) {
	set(event_field::state, val);
}

void event::set_service(std::string val) {
	set(event_field::service, val);
}

void event::set_host(std::string val) {
	set(event_field::host, val);
}

void event::set_description(std::string val) {
	set(event_field::description, val);
}

void event::set_ttl(float val) {
	set(event_field::ttl, val);
}

template<>
void event::set_metric(const int64_t val) {
	set(event_field::metrics64, val);
}

template<>
void event::set_metric(const float val) {
	set(event_field::metricf, val);
}

template<>
void event::set_metric(const double val) {
	set(event_field::metricd, val);
}
