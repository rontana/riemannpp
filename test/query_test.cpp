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
