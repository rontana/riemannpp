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

#ifndef RIEMANNPP_EXCEPTION_HPP
#define RIEMANNPP_EXCEPTION_HPP

#include <riemann/riemann-client.h>

#include <errno.h>
#include <string.h>

#include <stdexcept>
#include <string>

namespace riemannpp {

	// The base exception class for all riemannpp exceptions.
	class exception : public std::runtime_error {
	public:
		// Construct an exception with the given message.
		exception(std::string const& message)
			: std::runtime_error(message) {}
	};

	// The internal_exception class encapsulates errors caused by calls to
	// the riemann client library that return an error code. These errors are
	// identified by their errorcode given by errno, and their associated
	// reason string deduced by strerror.
	class internal_exception : public exception {
		int         d_error;
		std::string d_reason;
	public:
		// Default constructor. Will construct the base exception class with
		// the string error deduced by strerror, and store errno.
		internal_exception()
			: exception(strerror(errno))
			, d_error(errno)
			, d_reason(strerror(errno)) {}

		// Construct an internal exception with the given reason. Behaves the
		// same as the default constructor, with the exception being that the
		// reason string is overridden by the given parameter.
		internal_exception(const std::string& reason)
			: exception(strerror(errno))
			, d_error(errno)
			, d_reason(reason) {}

		// Destructor.
		~internal_exception() throw() {}

		// MANIPULATORS

		// Get the error code associated with this exception.
		int error() const { return d_error; }

		// Get the reason string describing this exception.
		std::string const& reason() const { return d_reason; }
	};

}

#endif // RIEMANNPP_EXCEPTION_HPP
