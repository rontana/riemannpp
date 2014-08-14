#include "query.hpp"
#include "exception.hpp"

using namespace riemannpp;

query::query(const std::string& query) {
	d_query.reset(riemann_query_new(query.c_str()));
}

query::~query() {
	if (d_query) {
		riemann_query_free(d_query.release());
	}
}

void 
query::set_string(const std::string& query) {
	int result = riemann_query_set_string(d_query.get(), query.c_str());
	if (-1 == result) {
		throw new riemannpp_internal_exception();
	}
}
