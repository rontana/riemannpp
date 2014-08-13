# riemannpp (C++)

## Introduction

C++ client library for [Riemann](https://github.com/aphyr/riemann).

This client library was inspired by [Riemann C client library](https://github.com/algernon/riemann-c-client).

Features:
* Sending events over TCP and UDP
* Launching queries (TCP only)
* Support for tags and attributes on events
* Ability to send multiple events in a single message
* Convenient API
* Test suite

## Installation

The library uses autotools along with a dependency on the [Riemann C client library](https://github.com/algernon/riemann-c-client):

```bash
$ git clone git://github.com/bigdatadev/riemannpp.git
$ cd riemannpp
$ autoreconf -i
$ ./configure && make && make check && make install
```

If you're a developer, Riemann uses [Google Protocol Buffers](http://code.google.com/p/protobuf/), so make sure that's installed and available on your PATH.

## Getting Started

First we'll need to import the library:

```cpp
#include <riemannpp/riemannpp.hpp>

namespace rpp = riemannpp;

int main() {
	try {
		rpp::client client(rpp::client_type::tcp, "localhost", 5555);
		client.send_message(rpp::message(rpp::event(
			rpp::event_field::host,    "localhost",
			rpp::event_field::service, "demo-client",
			rpp::event_field::state,   "ok"))
		);
	} catch (rpp::internal_exception &e) {
		std::cerr << e.what() << endl;
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
```

## Contributing

Just send me a pull request. Please take a look at the project issues and see how you can help. Here are some tips:
- please add more tests.
- please check your syntax.

## Author

Christopher Gilbert

* Web: [http://cjgilbert.me](http://cjgilbert.me)
* Twitter: [@bigdatadev](https://twitter.com/bigdatadev)
* Linkedin: [/in/christophergilbert](https://www.linkedin.com/in/christophergilbert)

## Copyright

See [LICENSE](LICENSE) document