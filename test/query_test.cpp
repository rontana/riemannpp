#include "catch.hpp"

#include <riemannpp/query.hpp>

namespace riemann = riemannpp;

TEST_CASE("queries can be created and set", "[query]") {
	SECTION("default constructor") {
		riemann::query q;
		REQUIRE((riemann_query_t*)q == nullptr);
	}
	SECTION("move constructor") {
		riemann::query q1("query");
		riemann::query q2(std::move(q1));
		REQUIRE((riemann_query_t*)q2 != nullptr);
	}
	SECTION("overridden constructor") {
		riemann::query q("query");
		REQUIRE((riemann_query_t*)q != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::query q1("query");
		riemann::query q2;
		q2 = std::move(q1);
		REQUIRE((riemann_query_t*)q2 != nullptr);
	}
	SECTION("set query string") {
		riemann::query q;
		REQUIRE_NOTHROW(q.set_string("query"));
	}
}
