#ifndef RIEMANNPP_EXCEPTION_HPP
#define RIEMANNPP_EXCEPTION_HPP

#include <riemann/riemann-client.h>

#include <errno.h>
#include <string.h>

#include <stdexcept>
#include <string>

namespace riemannpp {

	class exception : public std::runtime_error {
	public:
		exception(std::string const& message)
			: std::runtime_error(message) {}
	};

	class riemannpp_internal_exception : public exception {
		int         d_error;
		std::string d_reason;
	public:
		riemannpp_internal_exception()
			: exception(strerror(errno))
			, d_error(errno)
			, d_reason(strerror(errno)) {}

		riemannpp_internal_exception(const std::string& reason)
			: exception(strerror(errno))
			, d_error(errno)
			, d_reason(reason) {}

		~riemannpp_internal_exception() throw() {}

		int error() const { return d_error; }

		std::string const& reason() const { return d_reason; }
	};

}

#endif // RIEMANNPP_EXCEPTION_HPP
