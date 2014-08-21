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

#include "query.hpp"
#include "exception.hpp"

#include <sstream>

using namespace riemannpp;

query::query()
	: d_query(nullptr)
{}

query::query(riemann_query_t* q)
	: d_query(q)
{}

query::query(query&& q) {
	*this = std::move(q);
}

query::query(const std::string& query) {
	d_query.reset(riemann_query_new(query.c_str()));
}

query::~query() {
	if (d_query) {
		riemann_query_free(d_query.release());
	}
}

query&
query::operator=(query&& q) {
	d_query = std::move(q.d_query);
	return *this;
}

void 
query::set_string(const std::string& query) {
	int result = riemann_query_set_string(d_query.get(), query.c_str());
	if (-1 == result) {
		throw internal_exception();
	}
}

std::string
query::get_string() const {
	if (d_query) {
		return (d_query->string);
	}
	return "";
}

std::string
query::to_str() const {
	std::stringstream ss;
	if (d_query) {
		ss << d_query->string << std::endl;
	}
	return (ss.str());
}

std::ostream & operator<<(std::ostream &os, const riemannpp::query& q) {
    return os << q.to_str();
}
