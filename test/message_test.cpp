#include "catch.hpp"

#include <riemannpp/message.hpp>

namespace riemann = riemannpp;

TEST_CASE("messages can be created and set", "[message]") {
	SECTION("default constructor") {
		riemann::message msg;
		REQUIRE((riemann_message_t*)msg != nullptr);
	}
	SECTION("move constructor") {
		riemann::message msg;
		riemann::message msg2(std::move(msg));
		REQUIRE((riemann_message_t*)msg == nullptr);
		REQUIRE((riemann_message_t*)msg2 != nullptr);
	}
	SECTION("construct with query") {
		riemann::query q("*");
		riemann::message msg(q);
		REQUIRE((riemann_message_t*)msg != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::message msg;
		riemann::message msg2 = std::move(msg);
		REQUIRE((riemann_message_t*)msg == nullptr);
		REQUIRE((riemann_message_t*)msg2 != nullptr);
	}
	SECTION("set event") {
//		riemann::event e();
//		riemann::message msg;
//		msg.set_event(e);
	}
	SECTION("stream operator set event") {
//		riemann::event e();
//		riemann::message msg;
//		msg << e;
	}
	SECTION("set query") {
		riemann::query q("*");
		riemann::message msg;
		msg.set_query(q);
	}
	SECTION("stream operator set query") {
		riemann::query q("*");
		riemann::message msg;
		msg << q;
	}
}
