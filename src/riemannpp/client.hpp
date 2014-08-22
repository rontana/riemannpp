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

#ifndef RIEMANNPP_CLIENT_HPP
#define RIEMANNPP_CLIENT_HPP

#include "message.hpp"

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	// The client_type enum is used by the client class to specify parameters
	// for connecting to the Riemann server.
	enum class client_type {
		none = RIEMANN_CLIENT_NONE,
		tcp  = RIEMANN_CLIENT_TCP,
		udp  = RIEMANN_CLIENT_UDP
	};

	// This class represents a connection to the Riemann server, and provides
	// the interface for connecting, disconnecting, sending and receiving
	// messages and queries.
	class client {
		riemann_client_t* d_client;

	public:
		// CONSTRUCTORS

		// Default constructor.
		client();

		// Constructor. Create a client object with an existing riemann_client_t
		// instance pointer. After this call, the object will assume ownership
		// of the pointer `c`.
		client(riemann_client_t* c);

		// Move constructor.
		client(client&& c);

		// Constructor. Create a client object and connect with the given
		// parameters.
		client(client_type type, const std::string& host, int port);

		// Destructor.
		~client();

		// Move assignment operator.
		client& operator=(client&& c);

		// MANIPULATORS

		// Connect to a server with the given parameters.
		void connect(client_type type, const std::string& host, int port);

		// Disconnect from a server.
		void disconnect();

		// Send a message.
		void send(message&& m);

		// Send an event.
		void send(event&& e);

		// Send a query.
		void send(query&& q);

		// Send a message.
		void send_oneshot(message&& m);

		// Send an event.
		void send_oneshot(event&& e);

		// Send a query.
		void send_oneshot(query&& q);

		// Stream operator to send a message.
		client& operator<<(message&& m);

		// Stream operator to send an event.
		client& operator<<(event&& e);

		// Stream operator to send a query.
		client& operator<<(query&& q);

		// Receive a message.
		std::unique_ptr<message> recv();

		// Stream operator to receive a message.
		client& operator>>(std::unique_ptr<message> &m);

		// Cast to riemann_client_t* operator. Use this method to get a handle
		// to the raw pointer.
		operator riemann_client_t*() const { return d_client; }

	private:
		// NOT IMPLEMENTED
		client(const client& c) = delete;
		client& operator=(const client& c) = delete;
	};

}

#endif // RIEMANNPP_CLIENT_HPP
