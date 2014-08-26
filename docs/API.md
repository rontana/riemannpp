# API Reference

## Introduction

The riemannpp library is a C++11 library that utilises move semantics, unique_ptr and nullptr where appropriate. For this reason, and many others besides, I strongly urge users of riemannpp to use at least a C++11 compliant compiler such as GCC 4.8.

I have gone to some effort to make riemannpp *feel* like a C++ library: RAII, unexpected errors throw exceptions, stream operators work as you would expect, and containers such as std::string are used everywhere.

The library also provides seamless integration with the riemann-c-client library, providing a convenient upgrade path for existing library users who wish to adopt riemannpp. All objects can be constructed by passing the relevant pointer, which can then later be retrieved using the appropriate cast operator, or to transfer ownership back to the program call the appropriate release method.

No assumptions are made about thread-safety, thus no guarantees are given regarding thread-safe use of the library. For this reason, I strongly urge developers using riemannpp in a multi-threaded program to create their own thread-safety strategy when using the library.

## Getting Started

Initially, you may import the entire riemannpp API by including the master header file `riemannpp.hpp`.

```cpp
#include <riemannpp/riemannpp.hpp>
```

## Exceptions

Before exploring more of the API, it is important to discuss the topic of exceptions. If an unexpected error is encountered during runtime, an `riemannpp::internal_exception` will be thrown. This is a subclass of `riemannpp::exception`, however it provides an interface for accessing additional information about the cause.

Ideally you should enclose all riemannpp methods in a try / catch block to ensure safe use of the library, RAII ensures all riemannpp resources will be cleaned up upon destruction.

```cpp
try {
	// ...
} catch (riemannpp::internal_exception &e) {
	std::cerr << "Error: " << e.error() << " - " << e.reason() << "." << std::endl
}
```

## Clients

The `riemannpp::client` provides an interface for controlling a connection to a Riemann server, and sending and receiving messages.

### client::connect

To connect to a server, you may either invoke the `client::connect` method, or construct an object with the appropriate parameters. Riemann clients may send events either by TCP or UDP.

```cpp
riemannpp::client client(riemannpp::client_type::tcp, "localhost", 5555);
```

### client::send

Once a connection is established, messages can be sent by using the overloaded `client::send` method, or by using the stream operator. Ownership of the underlying memory representing the message is transferred at the point of calling one of the methods via use of std::move.

```cpp
riemannpp::message m;
// ...
client.send(std::move(m));
// OR
client << std::move(m);
```

### client::recv

If a connection is established via TCP, then it is also possible to receive messages from the Riemann server.

```cpp
std::unique_ptr<message> recv;
recv = client.recv();
// OR
client >> recv;
```

### client::operator riemann_client_t*

A cast operator is provided to get a handle to the underlying raw riemann_client_t pointer. It is advised to use caution when using this method, as the object will retain ownership until `client::release` is called.

```cpp
riemann_client_t* ptr = client;
// OR
riemann_client_t* ptr = client.release();
```

## Messages

The `riemannpp::message` provides an interface for manipulating Riemann messages, which represent zero or more events and zero or one query to send to the server, or just zero or more events received from the server.

### message::set_event

To set an event on a message, use the `message::set_event` method or use the stream operator. To call this method, the `riemannpp::event` must be passed by rvalue reference using `std::move`, which will transfer ownership of the event resources to the message object.

```cpp
riemannpp::event e;
// Construct with e
riemannpp::message m(e);
// OR call set_event
riemannpp::message m;
m.set_event(std::move(e));
// OR use stream operator
riemannpp::message m;
m << std::move(e);
```

### message::set_query

To set a query on a message, use the `message::set_query` method, or use the stream operator. A message may contain zero or one query.

```cpp
riemannpp::query q;
// Construct with q
riemannpp::message m(q);
// OR call set_query
riemannpp::message m;
m.set_event(std::move(q));
// OR use stream operator
riemannpp::message m;
m << std::move(q);
```

### message::operator riemann_message_t*

A cast operator is provided to get a handle to the underlying raw riemann_message_t pointer. It is advised to use caution when using this method, as the object will retain ownership until `message::release` is called.

```cpp
riemann_message_t* ptr = m;
// OR
riemann_message_t* ptr = m.release();
```

## Events

The `riemannpp::event` provides an interface for manipulating Riemann events, which contain fields such as metrics, zero or more attributes, and zero or more tags.

### event::set

To set a field on an event, the developer has a few choices. Fields can either be set using the generic `event::set` method, which takes a tuple containing a field identifier and a value, or by using one of the named set_<field> methods such as `event::set_service`.

```cpp
riemannpp::event e;
e.set(riemann::event_field::state, "ok");
// OR 
e << std::make_tuple(riemann::event_field::state, "ok");
// OR
e.set_state("ok");
```

### event::get

To get a field from an event, use one of the named get_<field> methods such as `event::get_service`.

```cpp
std::string service = e.get_service();
```

### event::tag_add

Tags may be added to the event by either invoking the `event::tag_add` method, or by using the stream operator.

```cpp
riemannpp::event e;
e.tag_add("tag1");
// OR
e << "tag1";
```

### event::attribute_add

Attributes may be added to the event by either invoking the `event::attribute_add` method, or by using the stream operator.

```cpp
riemannpp::event e;
e.attribute_add(riemannpp::attribute("key", "value"));
// OR
e << riemannpp::attribute("key", "value");
```

### event::operator riemann_event_t*

A cast operator is provided to get a handle to the underlying raw riemann_event_t pointer. It is advised to use caution when using this method, as the object will retain ownership until `event::release` is called.

```cpp
riemann_event_t* ptr = e;
// OR
riemann_event_t* ptr = e.release();
```

## Attributes

The `riemannpp::attribute` provides an interface for manipulating Riemann attributes, which comprise a key value pair.

### attribute::set

To set the key / value, you may either invoke the `query::set` method, or construct an object with the appropriate parameters.

```cpp
riemannpp::attribute a("key", "value");
// OR
riemannpp::attribute a;
a.set("key", "value");
```

### attribute::operator riemann_attribute_t*

A cast operator is provided to get a handle to the underlying raw riemann_attribute_t pointer. It is advised to use caution when using this method, as the object will retain ownership until `attribute::release` is called.

```cpp
riemann_attribute_t* ptr = a;
// OR
riemann_attribute_t* ptr = a.release();
```

## Queries

The `riemannpp::query` provides an interface for manipulating Riemann queries, which consist of a string representing the query.

### query::set_string

To set the query string, you may either invoke the `query::set_string` method, or construct an object with the appropriate parameter. Note that validation of the query is conducted by the server at the time of receiving the message containing the query.

```cpp
riemannpp::query q("true");
// OR
riemannpp::query q;
q.set_string("true");
```

### query::operator riemann_query_t*

A cast operator is provided to get a handle to the underlying raw riemann_query_t pointer. It is advised to use caution when using this method, as the object will retain ownership until `query::release` is called.

```cpp
riemann_query_t* ptr = q;
// OR
riemann_query_t* ptr = q.release();
```

## Further Reading

* [Riemann C client library](https://github.com/algernon/riemann-c-client)
* Read the client code and tests.
