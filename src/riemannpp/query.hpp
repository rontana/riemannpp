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

	// Riemann queries are used to fetch events from the server that match a
	// query string.
	class query {
		std::unique_ptr<riemann_query_t> d_query;

	public:
		// CONSTRUCTORS
		
		// Default constructor.
		query();

		// Constructor. Create a query object with an existing riemann_query_t
		// instance pointer. After this call, the object will assume ownership
		// of the pointer `q`.
		query(riemann_query_t* q);

		// Move constructor.
		query(query&& q);

		// Constructor.
		query(const std::string& query);

		// Destructor. The destructor will free the underlying riemann_query_t
		// pointer if necessary. If the pointer has not yet been transferred
		// via a call to release, or if the object has not yet been allocated
		// then the destructor will do nothing.
		~query();

		// Move assignment operator.
		query& operator=(query&& q);

		// MANIPULATORS

		// Set the query string.
		void set_string(const std::string& query);

		// Get the query string.
		std::string get_string() const;

		// Convert this object to a string.
		std::string to_str() const;

		// Release the riemann_query_t pointer. Use this function to transfer
		// ownership of the encapsulated pointer. After this call the object
		// will no longer own the pointer, and subsequent calls to will return
		// a nullptr.
		riemann_query_t* release() { return d_query.release(); }

		// Cast to riemann_query_t* operator. Use this method to get a handle
		// to the raw pointer.
		operator riemann_query_t*() const { return d_query.get(); }

	private:
		// NOT IMPLEMENTED
		query(const query& q) = delete;
		query& operator=(const query& q) = delete;
	};

}

// STREAM OPERATOR

std::ostream & operator<<(std::ostream &os, const riemannpp::query& q);

#endif // RIEMANNPP_QUERY_HPP
