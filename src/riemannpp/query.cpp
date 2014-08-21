#include "query.hpp"
#include "exception.hpp"

#include <sstream>

using namespace riemannpp;

query::query()
	: d_query(nullptr)
{}

query::query(riemann_query_t* q)
	: d_query(q)
{}

query::query(query&& q) {
	*this = std::move(q);
}

query::query(const std::string& query) {
	d_query.reset(riemann_query_new(query.c_str()));
}

query::~query() {
	if (d_query) {
		riemann_query_free(d_query.release());
	}
}

query&
query::operator=(query&& q) {
	d_query = std::move(q.d_query);
	return *this;
}

void 
query::set_string(const std::string& query) {
	int result = riemann_query_set_string(d_query.get(), query.c_str());
	if (-1 == result) {
		throw internal_exception();
	}
}

std::string
query::get_string() const {
	if (d_query) {
		return (d_query->string);
	}
	return "";
}

std::string
query::to_str() const {
	std::stringstream ss;
	if (d_query) {
		ss << d_query->string << std::endl;
	}
	return (ss.str());
}

std::ostream & operator<<(std::ostream &os, const riemannpp::query& q) {
    return os << q.to_str();
}
