#include "catch.hpp"

#include <riemannpp/client.hpp>

namespace riemann = riemannpp;

TEST_CASE("clients can be created and connect", "[client]") {
	SECTION("default constructor") {
		riemann::client client;
		REQUIRE((riemann_client_t*)client != nullptr);
	}
	SECTION("move constructor") {

	}
	SECTION("construct with parameters") {
		
	}
	SECTION("move assignment operator") {

	}
	SECTION("connect and disconnect") {

	}
	SECTION("send message") {

	}
	SECTION("stream operator send message") {

	}
	SECTION("receive message") {

	}
	SECTION("stream operator receive message") {

	}
}
