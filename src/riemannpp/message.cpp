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

#include "message.hpp"
#include "exception.hpp"

#include <sstream>

using namespace riemannpp;

message::message()
	: d_message(riemann_message_new())
{}

message::message(riemann_message_t* m)
	: d_message(m)
{}

message::message(message&& m) {
	*this = std::move(m);
}

message::message(event& e) {
	d_message.reset(riemann_message_new());
	set_event(e);
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
	riemann_event_t* evp = e.release();
	int result = riemann_message_set_events_n(d_message.get(), 1, &evp);
	if (0 != result) {
		throw internal_exception();
	}
}

message&
message::operator<<(event& e) {
	return (*this);
}

void
message::set_query(query& q) {
	int result = riemann_message_set_query(d_message.get(), q.release());
	if (0 != result) {
		throw internal_exception();
	}
}

message&
message::operator<<(query& q) {
	set_query(q);
	return (*this);
}

bool
message::get_ok() const {
	if (d_message && d_message->has_ok) {
		return (d_message->ok != 0);
	} else {
		return false;
	}
}

std::string
message::get_error() const {
	if (d_message && d_message->error) {
		return (d_message->error);
	} else {
		return "";
	}
}

std::vector<event>
message::get_events() const {
	std::vector<event> result;
	if (d_message && d_message->n_events) {
		for (size_t i = 0; i < d_message->n_events; ++i) {
			result.push_back(event(d_message->events[i]));
		}
	}
	return result;
}

query
message::get_query() const {
	if (d_message && d_message->query) {
		return query(d_message->query);
	} else {
		return query();
	}
}

std::string
message::to_str() const {
	std::stringstream ss;
	if (d_message) {
		if (d_message->has_ok) {
			ss << "ok = " << (d_message->ok == 1) << std::endl;
		}
		if (d_message->error) {
			ss << "error = " << d_message->error << std::endl;
		}
		if (d_message->query) {
			query q(d_message->query);
			ss << "query = " << q.to_str() << std::endl;
			q.release();
		}
		for (size_t i = 0; i < d_message->n_events; ++i) {
			event e(d_message->events[i]);
			ss << "event #" << i << ":" << std::endl;
			ss << e.to_str() << std::endl << std::endl;
			e.release();
		}
	}
	return (ss.str());
}

std::ostream& operator<<(std::ostream &os, const riemannpp::message& m) {
    return os << m.to_str();
}
