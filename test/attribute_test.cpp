#include "catch.hpp"

#include <riemannpp/attribute.hpp>

namespace riemann = riemannpp;

TEST_CASE("attributes can be created and set", "[attribute]") {
	SECTION("default constructor") {
		riemann::attribute attrib;
		REQUIRE((riemann_attribute_t*)attrib != nullptr);
	}
	SECTION("move constructor") {
		riemann::attribute attrib1;
		riemann::attribute attrib2(std::move(attrib1));
		REQUIRE((riemann_attribute_t*)attrib2 != nullptr);
	}
	SECTION("overridden constructor") {
		riemann::attribute attrib("key", "value");
		REQUIRE((riemann_attribute_t*)attrib != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::attribute attrib1("key", "value");
		riemann::attribute attrib2;
		attrib2 = std::move(attrib1);
		REQUIRE((riemann_attribute_t*)attrib2 != nullptr);
	}
	SECTION("attribute set") {
		riemann::attribute attrib;
		REQUIRE_NOTHROW(attrib.set_key("key"));
		REQUIRE_NOTHROW(attrib.set_value("value"));
		REQUIRE_NOTHROW(attrib.set("key", "value"));
		REQUIRE(std::string("key") == std::string(static_cast<riemann_attribute_t*>(attrib)->key));
		REQUIRE(std::string("value") == std::string(static_cast<riemann_attribute_t*>(attrib)->value));
	}
	SECTION("attribute create") {
		riemann::attribute attrib("key", "value");
		REQUIRE((riemann_attribute_t*)attrib != nullptr);
	}
}
