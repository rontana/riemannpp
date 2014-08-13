#ifndef RIEMANNPP_ATTRIBUTE_HPP
#define RIEMANNPP_ATTRIBUTE_HPP

#include <riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class attribute {
		std::unique_ptr<riemann_attribute_t> d_attribute;

	public:
		attribute();

		attribute(const std::string& key, const std::string& value);

		~attribute();

		void set(const std::string& key, const std::string& value);

		void set_key(const std::string& key);

		void set_value(const std::string& value);

		operator riemann_attribute_t*() const { return d_attribute.get(); }
	};

}

#endif // RIEMANNPP_ATTRIBUTE_HPP