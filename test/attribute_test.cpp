#include "catch.hpp"

#include <riemannpp/attribute.hpp>

namespace riemann = riemannpp;

TEST_CASE("attributes can be created and set", "[attribute]") {
	SECTION("new and delete") {
		{
			riemann::attribute attrib();
			REQUIRE((riemann_attribute_t*)attrib != nullptr)
		}
		REQUIRE(errno == EINVAL);
	}
	SECTION("attribute set") {
		riemann::attribute attrib();
		REQUIRE_NOTHROW(attrib.set_key(""));
		REQUIRE_NOTHROW(attrib.set_value(""));
		REQUIRE_NOTHROW(attrib.set("", ""));
	}
	SECTION("attribute create") {
		riemann::attribute attrib("", "");
		REQUIRE((riemann_attribute_t*)attrib != nullptr)
	}
}