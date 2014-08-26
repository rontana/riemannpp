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

#include <riemannpp/client.hpp>

namespace riemann = riemannpp;

TEST_CASE("clients can be created and connect", "[client]") {
	SECTION("default constructor") {
		riemann::client client;
		REQUIRE((riemann_client_t*)client != nullptr);
	}
	SECTION("move constructor") {
		riemann::client client1;
		riemann::client client2(std::move(client1));
		REQUIRE((riemann_client_t*)client1 == nullptr);
		REQUIRE((riemann_client_t*)client2 != nullptr);
	}
	SECTION("construct with parameters") {
		riemann::client client(riemann::client_type::tcp, "localhost", 5555);
		REQUIRE((riemann_client_t*)client != nullptr);
	}
	SECTION("move assignment operator") {
		riemann::client client1;
		riemann::client client2 = std::move(client1);
		REQUIRE((riemann_client_t*)client1 == nullptr);
		REQUIRE((riemann_client_t*)client2 != nullptr);
	}
	SECTION("connect and disconnect") {
		riemann::client client;
		client.connect(riemann::client_type::tcp, "localhost", 5555);
		client.disconnect();
		REQUIRE((riemann_client_t*)client != nullptr);
	}
	SECTION("send message") {
		riemann::client client(riemann::client_type::tcp, "localhost", 5555);
		riemann::message m;
		client.send(std::move(m));
		REQUIRE((riemann_message_t*)m == nullptr);
	}
	SECTION("stream operator send message") {
		riemann::client client(riemann::client_type::tcp, "localhost", 5555);
		riemann::message m;
		client << std::move(m);
		REQUIRE((riemann_message_t*)m == nullptr);
	}
}
