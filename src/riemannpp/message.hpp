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

#ifndef RIEMANNPP_MESSAGE_HPP
#define RIEMANNPP_MESSAGE_HPP

#include "event.hpp"
#include "query.hpp"

#include <riemann/riemann-client.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace riemannpp {

	// Riemann messages are used to send events and queries to a Riemann server.
	// The message class can contain zero or one query, and zero or more events.
	class message {
		std::unique_ptr<riemann_message_t> d_message;

	public:
		// CONSTRUCTORS

		// Default constructor
		message();

		// Constructor. Create a message object with an existing riemann_message_t
		// instance pointer. After this call, the object will assume ownership
		// of the pointer `m`.
		explicit message(riemann_message_t* m);

		// Move constructor.
		message(message&& m);

		// Constructor. Create a message with an existing event.
		explicit message(event&& e);

		// Constructor. Create a message with an existing query.
		explicit message(query&& q);

		// Destructor.
		~message();

		// Move assignment operator.
		message& operator=(message&& m);

		// MANIPULATORS

		// Set an event.
		void set_event(event& e);

		// Stream operator set an event.
		message& operator<<(event &e);

		// Set the query.
		void set_query(query& q);

		// Stream operator set the query.
		message& operator<<(query &q);

		// Get the ok.
		bool get_ok() const;

		// Get the error.
		std::string get_error() const;

		// Get the events.
		std::vector<event> get_events() const;

		// Get the query.
		query get_query() const;

		// Convert this object to a string.
		std::string to_str() const;

		// Release the riemmann_message_t pointer. Use this function to
		// transfer ownership of the encapsulated pointer. After this call the
		// object will no longer own the pointer, and subsequent calls will
		// return a nullptr.
		riemann_message_t* release() { return d_message.release(); }

		// Cast to riemmann_message_t* operator. Use this method to get a
		// handle to the raw pointer.
		operator riemann_message_t*() const { return d_message.get(); }

	private:
		// NOT IMPLEMENTED
		message(const message& m) = delete;
		message& operator=(const message& m) = delete;
	};

}

// STREAM OPERATOR

std::ostream& operator<<(std::ostream &os, const riemannpp::message& m);

#endif // RIEMANNPP_MESSAGE_HPP
