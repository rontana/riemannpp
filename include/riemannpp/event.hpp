#ifndef RIEMANNPP_EVENT_HPP
#define RIEMANNPP_EVENT_HPP

#include <riemann-client.h>

#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace riemannpp {

	enum class event_field {
		none        = RIEMANN_EVENT_FIELD_NONE,
		empty       = RIEMANN_EVENT_FIELD_EMPTY,
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
		std::unique_ptr<riemann_event_t> d_attribute;

	public:
		event();

		event(const field_list& fields);

		~event();

		void set(const field_list& fields);

		void tag_add(const std::string& tag);

		void attribute_add(const attribute& a);

		operator riemann_event_t*() const { return d_event.get(); }
	};

}

#endif // RIEMANNPP_EVENT_HPP