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

	// Riemann events can optionally contain multiple attributes consisting of
	// key / value pairs. Attributes are a method of adding metadata to events
	// for the purpose of specifying arbitrary properties that cannot be
	// provided by the standard structure.
	class attribute {
		std::unique_ptr<riemann_attribute_t> d_attribute;

	public:
		// CONSTRUCTORS

		// Default constructor.
		attribute();

		// Constructor. Create an attribute object with an existing
		// riemann_attribute_t instance pointer. After this call, the object
		// will assume ownership of the pointer `a`.
		attribute(riemann_attribute_t* a);

		// Move constructor.
		attribute(attribute&& a);

		// Constructor.
		attribute(const std::string& key, const std::string& value);

		// Default destructor. The destructor will free the underlying pointer
		// to a riemann_attribute_t if necessary. If the pointer has been
		// transferred via a call to release, or if the object has not yet been
		// allocated then the destructor will do nothing.
		~attribute();

		// Move assignment operator.
		attribute& operator=(attribute&& a);

		// MANIPULATORS

		// Set the key and the value.
		void set(const std::string& key, const std::string& value);

		// Set the key only. It is possible to set a key without a value if this
		// function is called without a matching call to set_value.
		void set_key(const std::string& key);

		// Set the value only. It is not possible to set a value without a call
		// first to set_key to create the key.
		void set_value(const std::string& value);

		// Get the key.
		std::string get_key() const;

		// Get the value.
		std::string get_value() const;

		// Convert this object to a string.
		std::string to_str() const;

		// Release the riemann_attribute_t pointer. Use this function to
		// transfer ownership of the encapsulated pointer. After this call the
		// object will no longer own the pointer, and subsequent calls will
		// return a nullptr.
		riemann_attribute_t* release() { return d_attribute.release(); }

		// Cast to riemmann_attribute_t* operator. Use this method to get a
		// handle to the raw pointer.
		operator riemann_attribute_t*() const { return d_attribute.get(); }

	private:
		// NOT IMPLEMENTED
		attribute(const attribute& a);
		attribute& operator=(const attribute& a);
	};

}

// STREAM OPERATOR

std::ostream & operator<<(std::ostream &os, const riemannpp::attribute& a);

#endif // RIEMANNPP_ATTRIBUTE_HPP
