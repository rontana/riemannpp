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

#include "client.hpp"
#include "exception.hpp"

using namespace riemannpp;

client::client()
	: d_client(riemann_client_new())
{}

client::client(riemann_client_t* c)
	: d_client(c)
{}

client::client(client&& c) {
	*this = std::move(c);
}

client::client(client_type type, const std::string& host, int port) {
	d_client = riemann_client_create(riemann_client_type_t(type), host.c_str(), port);
	if (!d_client) {
		throw internal_exception();
	}
}

client::~client() {
	if (d_client) {
		riemann_client_free(d_client);
		d_client = nullptr;
	}
}

client&
client::operator=(client&& c) {
	d_client = c.d_client;
	c.d_client = nullptr;
	return (*this);
}

void 
client::connect(client_type type, const std::string& host, int port) {
	int result = riemann_client_connect(d_client, riemann_client_type_t(type), host.c_str(), port);
	if (0 != result) {
		throw internal_exception();
	}
}

void 
client::disconnect() {
	int result = riemann_client_disconnect(d_client);
	if (0 != result) {
		throw internal_exception();
	}
}

void 
client::send_message(message& m) {
	int result = riemann_client_send_message(d_client, m.release());
	if (0 != result) {
		throw internal_exception();
	}
}

void 
client::send_message_oneshot(message& m) {
	int result = riemann_client_send_message_oneshot(d_client, m.release());
	if (0 != result) {
		throw internal_exception();
	}
}

client&
client::operator<<(message &m) {
	send_message(m);
	return (*this);
}

client&
client::operator<<(event &e) {
	message m;
	send_message(m << e);
	return (*this);
}

client&
client::operator<<(query &q) {
	message m;
	send_message(m << q);
	return (*this);
}

std::unique_ptr<message>
client::recv() {
	return std::unique_ptr<message>(new message(riemann_client_recv_message(d_client)));
}

client&
client::operator>>(std::unique_ptr<message> &m) {
	m = std::move(recv());
	return (*this);
}
