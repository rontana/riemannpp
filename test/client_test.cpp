#include "catch.hpp"

#include <riemannpp/client.hpp>

namespace riemann = riemannpp;

TEST_CASE("clients can be created and connect", "[client]") {
	SECTION("new and delete") {
		{
			riemann::client client;
			REQUIRE((riemann_client_t*)client != nullptr);
		}
		REQUIRE(errno == EINVAL);
	}
	SECTION("connect and disconnect") {

	}
	SECTION("send message") {
		
	}
}
