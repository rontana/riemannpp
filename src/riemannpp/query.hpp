#ifndef RIEMANNPP_QUERY_HPP
#define RIEMANNPP_QUERY_HPP

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class query {
		std::unique_ptr<riemann_query_t> d_query;

	public:
		query();

		query(query&& q);

		query(const std::string& query);

		~query();

		query& operator=(query&& q);

		void set_string(const std::string& query);

		riemann_query_t* release() { return d_query.release(); }

		operator riemann_query_t*() const { return d_query.get(); }

	private:
		query(const query& q);

		query& operator=(const query& q);
	};

}

#endif // RIEMANNPP_QUERY_HPP
