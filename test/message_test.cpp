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
