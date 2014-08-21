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

#ifndef RIEMANNPP_EVENT_HPP
#define RIEMANNPP_EVENT_HPP

#include "attribute.hpp"
#include "exception.hpp"

#include <riemann/riemann-client.h>

#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace riemannpp {

	enum class event_field {
		none        = RIEMANN_EVENT_FIELD_NONE,
		time        = RIEMANN_EVENT_FIELD_TIME,
		state       = RIEMANN_EVENT_FIELD_STATE,
		service     = RIEMANN_EVENT_FIELD_SERVICE,
		host        = RIEMANN_EVENT_FIELD_HOST,
		description = RIEMANN_EVENT_FIELD_DESCRIPTION,
		tags        = RIEMANN_EVENT_FIELD_TAGS,
		ttl         = RIEMANN_EVENT_FIELD_TTL,
		attributes  = RIEMANN_EVENT_FIELD_ATTRIBUTES,
		metrics64   = RIEMANN_EVENT_FIELD_METRIC_S64,
		metricd     = RIEMANN_EVENT_FIELD_METRIC_D,
		metricf     = RIEMANN_EVENT_FIELD_METRIC_F
	};

	class event {
		std::unique_ptr<riemann_event_t> d_event;

	public:
		event();

		event(riemann_event_t* e);

		event(event&& e);

		~event();

		event& operator=(event&& e);

		template<typename T>
		void set(const event_field field, const T& value);

		template<typename T>
		event& operator<<(std::tuple<event_field, T> f);

		void tag_add(const std::string& tag);

		event& operator<<(std::string t);

		void attribute_add(attribute&& a);

		event& operator<<(attribute&& a);

		int64_t     get_time() const;

		std::string get_state() const;

		std::string get_service() const;

		std::string get_host() const;

		std::string get_description() const;

		float       get_ttl() const;

		template<typename T>
		T           get_metric() const;

		std::vector<std::string> get_tags() const;

		std::vector<attribute> get_attributes() const;

		void set_state(std::string val);

		void set_service(std::string val);

		void set_host(std::string val);

		void set_description(std::string val);

		void set_ttl(float val);

		template<typename T>
		void set_metric(const T val);

		std::string to_str() const;

		riemann_event_t* release() { return d_event.release(); }

		operator riemann_event_t*() const { return d_event.get(); }

	private:
		event(const event& e);

		event& operator=(const event& e);
	};

	template<typename T>
	void event::set(const event_field field, const T& value) {
		int result = riemann_event_set(d_event.get(), field, value, RIEMANN_EVENT_FIELD_NONE);
		if (-1 == result) {
			throw internal_exception();
		}
	}

	template<>
	void event::set(const event_field field, const std::string& value);

	template<typename T>
	event& event::operator<<(std::tuple<event_field, T> f) {
		set(std::get<0>(f), std::get<1>(f));
		return (*this);
	}

	template<>
	int64_t event::get_metric() const;

	template<>
	float event::get_metric() const;

	template<>
	double event::get_metric() const;

	template<>
	void event::set_metric(const int64_t val);

	template<>
	void event::set_metric(const float val);

	template<>
	void event::set_metric(const double val);

}

std::ostream & operator<<(std::ostream &os, const riemannpp::event& e);

#endif // RIEMANNPP_EVENT_HPP
