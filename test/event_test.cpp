#include "catch.hpp"

#include <riemannpp/event.hpp>

namespace riemann = riemannpp;

TEST_CASE("events can be created and set", "[event]") {
	SECTION("default constructor") {
		riemann::event event;
		REQUIRE((riemann_event_t*)event != nullptr);
	}
	SECTION("move constructor") {
		
	}
	SECTION("construct with list of fields") {

	}
	SECTION("move assignment operator") {

	}
	SECTION("set field") {

	}
	SECTION("stream operator set field") {

	}
	SECTION("set field list") {

	}
	SECTION("add tag") {

	}
	SECTION("stream operator add tag") {

	}
	SECTION("attribute add") {

	}
	SECTION("stream operator attribute add") {

	}
}
