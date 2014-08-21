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

#include <riemannpp/event.hpp>

namespace riemann = riemannpp;

TEST_CASE("events can be created and set", "[event]") {
	SECTION("default constructor") {
		riemann::event event;
		REQUIRE((riemann_event_t*)event != nullptr);
	}
	SECTION("move constructor") {
		riemann::event event;
		riemann::event event2(std::move(event));
		REQUIRE((riemann_event_t*)event == nullptr);
		REQUIRE((riemann_event_t*)event2 != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::event event;
		riemann::event event2 = std::move(event);
		REQUIRE((riemann_event_t*)event == nullptr);
		REQUIRE((riemann_event_t*)event2 != nullptr);
	}
	SECTION("set field") {
		riemann::event event;
		event.set(riemann::event_field::state, "ok");
		REQUIRE(event.get_state() == "ok");
		event.set(riemann::event_field::service, "test");
		REQUIRE(event.get_service() == "test");
		event.set(riemann::event_field::host, "localhost");
		REQUIRE(event.get_host() == "localhost");
		event.set(riemann::event_field::description, "description");
		REQUIRE(event.get_description() == "description");
		event.set(riemann::event_field::ttl, 0.f);
		REQUIRE(event.get_ttl() == 0.f);
		event.set(riemann::event_field::metrics64, 0);
		REQUIRE(event.get_metric<int64_t>() == 0);
		event.set(riemann::event_field::metricd, 0.0);
		REQUIRE(event.get_metric<double>() == 0.0);
		event.set(riemann::event_field::metricf, 0.f);
		REQUIRE(event.get_metric<float>() == 0.f);
	}
	SECTION("stream operator set field") {
		riemann::event event;
		event << std::make_tuple(riemann::event_field::state, "ok");
		REQUIRE(event.get_state() == "ok");
		event << std::make_tuple(riemann::event_field::service, "test");
		REQUIRE(event.get_service() == "test");
		event << std::make_tuple(riemann::event_field::host, "localhost");
		REQUIRE(event.get_host() == "localhost");
		event << std::make_tuple(riemann::event_field::description, "description");
		REQUIRE(event.get_description() == "description");
		event << std::make_tuple(riemann::event_field::ttl, 0.f);
		REQUIRE(event.get_ttl() == 0.f);
		event << std::make_tuple(riemann::event_field::metrics64, 0);
		REQUIRE(event.get_metric<int64_t>() == 0);
		event << std::make_tuple(riemann::event_field::metricd, 0.0);
		REQUIRE(event.get_metric<double>() == 0.0);
		event << std::make_tuple(riemann::event_field::metricf, 0.f);
		REQUIRE(event.get_metric<float>() == 0.f);
	}
	SECTION("set field by name") {
		riemann::event event;
		event.set_state("ok");
		REQUIRE(event.get_state() == "ok");
		event.set_service("test");
		REQUIRE(event.get_service() == "test");
		event.set_host("localhost");
		REQUIRE(event.get_host() == "localhost");
		event.set_description("description");
		REQUIRE(event.get_description() == "description");
		event.set_ttl(0.f);
		REQUIRE(event.get_ttl() == 0.f);
		event.set_metric(int64_t(0));
		REQUIRE(event.get_metric<int64_t>() == 0);
		event.set_metric(0.f);
		REQUIRE(event.get_metric<float>() == 0.f);
		event.set_metric(0.);
		REQUIRE(event.get_metric<double>() == 0.0);
	}
	SECTION("add tag") {
		riemann::event event;
		event.tag_add("tag");
		REQUIRE(event.get_tags().size() == 1);
	}
	SECTION("stream operator add tag") {
		riemann::event event;
		event << "tag1" << "tag2";
		REQUIRE(event.get_tags().size() == 2);
	}
	SECTION("attribute add") {
		riemann::event event;
		event.attribute_add(riemann::attribute("key", "value"));
	}
	SECTION("stream operator attribute add") {
		riemann::event event;
		event << riemann::attribute("foo", "bar");
		event << riemann::attribute("key", "value")
		      << riemann::attribute("key2", "value2");
	}
}
