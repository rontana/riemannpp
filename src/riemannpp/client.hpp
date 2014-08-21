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

	enum class client_type {
		none = RIEMANN_CLIENT_NONE,
		tcp  = RIEMANN_CLIENT_TCP,
		udp  = RIEMANN_CLIENT_UDP
	};

	class client {
		riemann_client_t* d_client;

	public:
		client();

		client(riemann_client_t* c);

		client(client&& c);

		client(client_type type, const std::string& host, int port);

		~client();

		client& operator=(client&& c);

		void connect(client_type type, const std::string& host, int port);

		void disconnect();

		void send_message(message& m);

		void send_message_oneshot(message& m);

		client& operator<<(message &m);

		client& operator<<(event &e);

		client& operator<<(query &q);

		std::unique_ptr<message> recv();

		client& operator>>(std::unique_ptr<message> &m);

		operator riemann_client_t*() const { return d_client; }

	private:
		client(const client& c);

		client& operator=(const client& c);
	};

}

#endif // RIEMANNPP_CLIENT_HPP
