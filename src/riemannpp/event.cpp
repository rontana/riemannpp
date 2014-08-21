/*
 * Copyright (C) 2014 Christopher Gilbert <christopher.john.gilbert@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "event.hpp"
#include "exception.hpp"

#include <ctime>
#include <sstream>

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
	int result = riemann_event_set(d_event.get(), field, value.c_str(), 
		RIEMANN_EVENT_FIELD_NONE
	);
	if (-1 == result) {
		throw internal_exception();
	}
}

void 
event::tag_add(const std::string& tag) {
	int result = riemann_event_tag_add(d_event.get(), tag.c_str());
	if (-1 == result) {
		throw internal_exception();
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
		throw internal_exception();
	}
}

event&
event::operator<<(attribute&& a) {
	attribute_add(std::move(a));
	return (*this);
}

int64_t
event::get_time() const {
	if (d_event) {
		return (d_event->time);
	}
	return 0;
}

std::string
event::get_state() const {
	if (d_event && d_event->state) {
		return (d_event->state);
	}
	return "";
}

std::string
event::get_service() const {
	if (d_event && d_event->service) {
		return (d_event->service);
	}
	return "";
}

std::string
event::get_host() const {
	if (d_event && d_event->host) {
		return (d_event->host);
	}
	return "";
}

std::string
event::get_description() const {
	if (d_event && d_event->description) {
		return (d_event->description);
	}
	return "";
}

float
event::get_ttl() const {
	if (d_event && d_event->has_ttl) {
		return (d_event->ttl);
	}
	return 0.f;
}

template<>
int64_t event::get_metric() const {
	if (d_event && d_event->has_metric_sint64) {
		return (d_event->metric_sint64);
	}
	return 0;
}

template<>
float event::get_metric() const {
	if (d_event && d_event->has_metric_f) {
		return (d_event->metric_f);
	}
	return 0.f;
}

template<>
double event::get_metric() const {
	if (d_event && d_event->has_metric_d) {
		return (d_event->metric_d);
	}
	return 0.;
}

std::vector<std::string>
event::get_tags() const {
	std::vector<std::string> result;
	if (d_event && d_event->n_tags) {
		for (size_t i = 0; i < d_event->n_tags; ++i) {
			result.push_back(d_event->tags[i]);
		}
	}
	return result;
}

std::vector<attribute>
event::get_attributes() const {
	std::vector<attribute> result;
	if (d_event && d_event->n_attributes) {
		for (size_t i = 0; i < d_event->n_attributes; ++i) {
			result.push_back(d_event->attributes[i]);
		}
	}
	return result;
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

std::string
event::to_str() const {
	std::stringstream ss;
	if (d_event) {
		if (d_event->has_time != 0) {
			time_t t = d_event->time;
			ss << "time = " << d_event->time << " - " << std::ctime(&t);
		}
		ss << "state = " << d_event->state << std::endl;
		ss << "service = " << d_event->service << std::endl;
		ss << "host = " << d_event->host << std::endl;
		ss << "description = " << d_event->description << std::endl;
		if (d_event->has_ttl != 0) {
			ss << "ttl = " << d_event->ttl << std::endl;
		}
		if (d_event->has_metric_sint64 != 0) {
			ss << "ttl = " << d_event->metric_sint64 << std::endl;
		}
		if (d_event->has_metric_d != 0) {
			ss << "ttl = " << d_event->metric_d << std::endl;
		}
		if (d_event->has_metric_f != 0) {
			ss << "ttl = " << d_event->metric_f << std::endl;
		}
		ss << "tags = [ ";
		for (size_t i = 0; i < d_event->n_tags; ++i) {
			ss << d_event->tags[i] << " ";
		}
		ss << "]" << std::endl;
		ss << "attributes = { " << std::endl;
		for (size_t i = 0; i < d_event->n_attributes; ++i) {
			ss << "  " << d_event->attributes[i]->key << " = " 
			<< d_event->attributes[i]->value << std::endl;
		}
		ss << "}" << std::endl;
	}
	return (ss.str());
}

std::ostream & operator<<(std::ostream &os, const riemannpp::event& e) {
    return os << e.to_str();
}
