/*
 * Copyright (C) 2014 Christopher Gilbert <christopher.john.gilbert@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
