#include "catch.hpp"

#include <riemannpp/event.hpp>

namespace riemann = riemannpp;

TEST_CASE("events can be created and set", "[event]") {
	SECTION("default constructor") {
		riemann::event event;
		REQUIRE((riemann_event_t*)event != nullptr);
	}
	SECTION("move constructor") {
		riemann::event event;
		riemann::event event2(std::move(event));
		REQUIRE((riemann_event_t*)event == nullptr);
		REQUIRE((riemann_event_t*)event2 != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::event event;
		riemann::event event2 = std::move(event);
		REQUIRE((riemann_event_t*)event == nullptr);
		REQUIRE((riemann_event_t*)event2 != nullptr);
	}
	SECTION("set field") {
		riemann::event event;
		event.set(riemann::event_field::state,       "ok");
		event.set(riemann::event_field::service,     "test");
		event.set(riemann::event_field::host,        "localhost");
		event.set(riemann::event_field::description, "description");
		event.set(riemann::event_field::ttl,         0.f);
		event.set(riemann::event_field::metrics64,   0);
		event.set(riemann::event_field::metricd,     0.0);
		event.set(riemann::event_field::metricf,     0.f);
	}
	SECTION("stream operator set field") {
		riemann::event event;
		event << std::make_tuple(riemann::event_field::state,       "ok")
		      << std::make_tuple(riemann::event_field::service,     "test")
		      << std::make_tuple(riemann::event_field::host,        "localhost")
		      << std::make_tuple(riemann::event_field::description, "description")
		      << std::make_tuple(riemann::event_field::ttl,         0.f)
		      << std::make_tuple(riemann::event_field::metrics64,   0)
		      << std::make_tuple(riemann::event_field::metricd,     0.0)
	          << std::make_tuple(riemann::event_field::metricf,     0.f);
	}
	SECTION("add tag") {
		riemann::event event;
		event.tag_add("tag");
	}
	SECTION("stream operator add tag") {
		riemann::event event;
		event << "tag";
	}
	SECTION("attribute add") {
		riemann::event event;
		event.attribute_add(riemann::attribute("key", "value"));
	}
	SECTION("stream operator attribute add") {
		riemann::event event;
		event << riemann::attribute("foo", "bar");
		event << riemann::attribute("key", "value")
		      << riemann::attribute("key2", "value2");
	}
}
