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

#ifndef RIEMANNPP_QUERY_HPP
#define RIEMANNPP_QUERY_HPP

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class query {
		std::unique_ptr<riemann_query_t> d_query;

	public:
		query();

		query(riemann_query_t* q);

		query(query&& q);

		query(const std::string& query);

		~query();

		query& operator=(query&& q);

		void set_string(const std::string& query);

		std::string get_string() const;

		std::string to_str() const;

		riemann_query_t* release() { return d_query.release(); }

		operator riemann_query_t*() const { return d_query.get(); }

	private:
		query(const query& q);

		query& operator=(const query& q);
	};

}

std::ostream & operator<<(std::ostream &os, const riemannpp::query& q);

#endif // RIEMANNPP_QUERY_HPP
