#include "attribute.hpp"
#include "exception.hpp"

using namespace riemannpp;

attribute::attribute() {
	d_attribute.reset(riemann_attribute_new());
}

attribute::attribute(const std::string& key, const std::string& value) {
	d_attribute.reset(riemann_attribute_create(key.c_str(), value.c_str()));
}

attribute::~attribute() {
	if (d_attribute) {
		riemann_attribute_free(d_attribute.release());
	}
}

void 
attribute::set(const std::string& key, const std::string& value) {
	int result = riemann_attribute_set(d_attribute.get(), key.c_str(), value.c_str());
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

void 
attribute::set_key(const std::string& key) {
	int result = riemann_attribute_set_key(d_attribute.get(), key.c_str());
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}

void 
attribute::set_value(const std::string& value) {
	int result = riemann_attribute_set_value(d_attribute.get(), value.c_str());
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}
