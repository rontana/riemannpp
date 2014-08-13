#ifndef RIEMANNPP_QUERY_HPP
#define RIEMANNPP_QUERY_HPP

#include <riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class query {
		std::unique_ptr<riemann_query_t> d_query;

	public:
		query(const std::string& query);

		~query();

		void set_string(const std::string& query);

		operator riemann_query_t*() const { return d_query.get(); }
	};

}

#endif // RIEMANNPP_QUERY_HPP