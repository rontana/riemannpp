#include "catch.hpp"

#include <riemannpp/message.hpp>

namespace riemann = riemannpp;

TEST_CASE("messages can be created and set", "[message]") {
	SECTION("new and delete") {
		{
			riemann::message msg();
			REQUIRE((riemann_message_t*)msg != nullptr)
		}
		REQUIRE(errno == EINVAL);
	}
	SECTION("message set events") {
		riemann::message msg();
		REQUIRE((riemann_message_t*)msg != nullptr)
	}
	SECTION("message set query") {
		riemann::message msg("", "");
		REQUIRE((riemann_message_t*)msg != nullptr)
	}
}