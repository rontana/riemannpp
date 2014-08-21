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

#ifndef RIEMANNPP_ATTRIBUTE_HPP
#define RIEMANNPP_ATTRIBUTE_HPP

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class attribute {
		std::unique_ptr<riemann_attribute_t> d_attribute;

	public:
		attribute();

		attribute(riemann_attribute_t* a);

		attribute(attribute&& a);

		attribute(const std::string& key, const std::string& value);

		~attribute();

		attribute& operator=(attribute&& a);

		void set(const std::string& key, const std::string& value);

		void set_key(const std::string& key);

		void set_value(const std::string& value);

		std::string get_key() const;

		std::string get_value() const;

		std::string to_str() const;

		riemann_attribute_t* release() { return d_attribute.release(); }

		operator riemann_attribute_t*() const { return d_attribute.get(); }

	private:
		attribute(const attribute& a);

		attribute& operator=(const attribute& a);
	};

}

std::ostream & operator<<(std::ostream &os, const riemannpp::attribute& a);

#endif // RIEMANNPP_ATTRIBUTE_HPP
