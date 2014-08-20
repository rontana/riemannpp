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

		int64_t     get_time();

		std::string get_state();

		std::string get_service();

		std::string get_host();

		std::string get_description();

		float       get_ttl();

		template<typename T>
		T           get_metric();

		void set_state(std::string val);

		void set_service(std::string val);

		void set_host(std::string val);

		void set_description(std::string val);

		void set_ttl(float val);

		template<typename T>
		void set_metric(const T val);

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
			throw new internal_exception();
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
	int64_t event::get_metric();

	template<>
	float event::get_metric();

	template<>
	double event::get_metric();

	template<>
	void event::set_metric(const int64_t val);

	template<>
	void event::set_metric(const float val);

	template<>
	void event::set_metric(const double val);

}

#endif // RIEMANNPP_EVENT_HPP
