#ifndef RIEMANNPP_EVENT_HPP
#define RIEMANNPP_EVENT_HPP

#include "attribute.hpp"

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

	typedef std::tuple<event_field, std::string> field;
	typedef std::vector<field>                   field_list;

	class event {
		std::unique_ptr<riemann_event_t> d_event;

	public:
		event();

		event(event&& e);

		event(const field_list& fields);

		~event();

		event& operator=(event&& e);

		void set(const field& field);

		event& operator<<(field &f);

		void set(const field_list& fields);

		void tag_add(const std::string& tag);

		event& operator<<(std::string &t);

		void attribute_add(attribute& a);

		event& operator<<(attribute &a);

		operator riemann_event_t*() const { return d_event.get(); }

	private:
		event(const event& e);

		event& operator=(const event& e);
	};

}

#endif // RIEMANNPP_EVENT_HPP
