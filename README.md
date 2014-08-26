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

If you're a developer, Riemann uses [Google Protocol Buffers](http://code.google.com/p/protobuf/), so make sure that's installed and available on your system path.

The library uses autotools along with a dependency on the [Riemann C client library](https://github.com/algernon/riemann-c-client). The client also uses [boost](http://www.boost.org). First install Riemann-C-Client (instructions in README.md) and boost, then continue with the following commands to build and install riemannpp:

```bash
$ git clone git://github.com/bigdatadev/riemannpp.git
$ cd riemannpp
$ autoreconf -i
$ ./configure && make && make check && make install
```

## Getting Started

Here is a simple example of how to connect to a Riemann server using tcp and send an event:

```cpp
#include <riemannpp/riemannpp.hpp>
#include <tuple>

namespace rpp = riemannpp;
using namespace std;

int main() {
	try {
		rpp::client client(rpp::client_type::tcp, "localhost", 5555);
		
		rpp::event e;
		e << make_tuple(rpp::event_field::host,    "localhost")
		  << make_tuple(rpp::event_field::service, "demo-client")
		  << make_tuple(rpp::event_field::state,   "ok");
		client << e;
	} catch (rpp::internal_exception &e) {
		std::cerr << "Error: " << e.error() << " - " << e.reason() << "." << std::endl;
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
```

You can receive events in a similar way:

```cpp
std::unique_ptr<rpp::message> rcv;
client >> rcv;

// print all the events
for (auto& e : rcv->get_events()) {
	std::cout << e << std::endl;
}
```

This can be useful if you want to run a query:

```cpp
rpp::query q("service = \"superdooper\"");
client << q;
```

You can also send multiple events:

```cpp
rpp::message m;
rpp::event e1;
e1 << make_tuple(rpp::event_field::host,    "localhost")
   << make_tuple(rpp::event_field::service, "demo-client-memory")
   << make_tuple(rpp::event_field::state,   "critical");
rpp::event e2;
e2 << make_tuple(rpp::event_field::host,    "localhost")
   << make_tuple(rpp::event_field::service, "demo-client-cpu")
   << make_tuple(rpp::event_field::state,   "ok");
m << e1 << e2;
client << m;
```

## Command Line Client

### Usage

```bash
$ riemannpp COMMAND [options...] [HOST] [PORT]
```

The HOST and PORT arguments are optional, and they default to
"localhost" and 5555, respectively.

Command can be either `send` or `query`.

### Send Command Options
* `-s [ --state ] arg`         Set the state of the event.
* `-S [ --service ] arg`       Set the service sending the event.
* `-h [ --host ] arg`          Set the origin host of the event.
* `-D [ --description ] arg`   Set the description of the event.
* `-a [ --attribute ] arg`     Add a new attribute to the event.
* `-t [ --tag ] arg`           Add a tag to the event.
* `-i [ --metric-sint64 ] arg` Set the 64-bit integer metric of the event.
* `-d [ --metric-d ] arg`      Set the double metric of the event.
* `-f [ --metric-f ] arg`      Set the float metric of the event.
* `-L [ --ttl ] arg`           Set the TTL of the event.
* `-T [ --tcp ] arg (=1)`      Send the message over TCP (default).
* `-U [ --udp ] arg`           Send the message over UDP.

### Query Command Options
* `-q [ --query ] arg`    Query to send to Riemann.

### Miscellaneous Options
* `-V [ --version ]`      Display version.
* `-? [ --help ]`         Show this help page.

## Contributing

Just send me a pull request. Please take a look at the project issues and see how you can help. Here are some tips:
* please add more tests.
* please check your syntax.

## Author

Christopher Gilbert

* Web: [http://cjgilbert.me](http://cjgilbert.me)
* Twitter: [@bigdatadev](https://twitter.com/bigdatadev)
* Linkedin: [/in/christophergilbert](https://www.linkedin.com/in/christophergilbert)

## Copyright

See [LICENSE](LICENSE) document