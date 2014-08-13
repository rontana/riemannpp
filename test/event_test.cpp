#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <riemannpp/event.hpp>

namespace riemann = riemannpp;

TEST_CASE("events can be created and set", "[event]") {
	SECTION("new and delete") {
		{
			riemann::event event();
			REQUIRE((riemann_event_t*)event != nullptr)
		}
		REQUIRE(errno == EINVAL);
	}
	SECTION("event create") {
		
	}
	SECTION("event set") {

	}
	SECTION("event add tag") {

	}
	SECTION("event add attribute") {

	}
}