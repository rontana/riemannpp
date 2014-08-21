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

#include "attribute.hpp"
#include "exception.hpp"

#include <sstream>

using namespace riemannpp;

attribute::attribute()
	: d_attribute(riemann_attribute_new())
{}

attribute::attribute(riemann_attribute_t* a)
	: d_attribute(a)
{}

attribute::attribute(attribute&& a) {
	*this = std::move(a);
}

attribute::attribute(const std::string& key, const std::string& value)
	: d_attribute(riemann_attribute_create(key.c_str(), value.c_str()))
{}

attribute::~attribute() {
	if (d_attribute) {
		riemann_attribute_free(d_attribute.release());
	}
}

attribute&
attribute::operator=(attribute&& a) {
	d_attribute = std::move(a.d_attribute);
	return (*this);
}

void 
attribute::set(const std::string& key, const std::string& value) {
	int result = riemann_attribute_set(d_attribute.get(), 
		key.c_str(), value.c_str());
	if (-1 == result) {
		throw internal_exception();
	}
}

void 
attribute::set_key(const std::string& key) {
	int result = riemann_attribute_set_key(d_attribute.get(), key.c_str());
	if (-1 == result) {
		throw internal_exception();
	}
}

void 
attribute::set_value(const std::string& value) {
	int result = riemann_attribute_set_value(d_attribute.get(), value.c_str());
	if (-1 == result) {
		throw internal_exception();
	}
}

std::string
attribute::get_key() const {
	if (d_attribute) {
		return d_attribute->key;
	}
	return "";
}

std::string
attribute::get_value() const {
	if (d_attribute) {
		return d_attribute->value;
	}
	return "";
}

std::string
attribute::to_str() const {
	std::stringstream ss;
	if (d_attribute) {
		ss << d_attribute->key << " = " << d_attribute->value << std::endl;
	}
	return (ss.str());
}

std::ostream & operator<<(std::ostream &os, const riemannpp::attribute& a) {
    return os << a.to_str();
}
