#include "catch.hpp"

#include <riemannpp/message.hpp>

namespace riemann = riemannpp;

TEST_CASE("messages can be created and set", "[message]") {
	SECTION("default constructor") {
		riemann::message msg;
		REQUIRE((riemann_message_t*)msg != nullptr);
	}
	SECTION("move constructor") {

	}
	SECTION("construct with query") {

	}
	SECTION("move assignment operator") {

	}
	SECTION("set event") {

	}
	SECTION("stream operator set event") {

	}
	SECTION("set query") {

	}
	SECTION("stream operator set query") {

	}
}
