#ifndef RIEMANNPP_ATTRIBUTE_HPP
#define RIEMANNPP_ATTRIBUTE_HPP

#include <riemann/riemann-client.h>

#include <memory>
#include <string>

namespace riemannpp {

	class attribute {
		std::unique_ptr<riemann_attribute_t> d_attribute;

	public:
		attribute();

		attribute(riemann_attribute_t* a);

		attribute(attribute&& a);

		attribute(const std::string& key, const std::string& value);

		~attribute();

		attribute& operator=(attribute&& a);

		void set(const std::string& key, const std::string& value);

		void set_key(const std::string& key);

		void set_value(const std::string& value);

		std::string get_key() const;

		std::string get_value() const;

		std::string to_str() const;

		riemann_attribute_t* release() { return d_attribute.release(); }

		operator riemann_attribute_t*() const { return d_attribute.get(); }

	private:
		attribute(const attribute& a);

		attribute& operator=(const attribute& a);
	};

}

std::ostream & operator<<(std::ostream &os, const riemannpp::attribute& a);

#endif // RIEMANNPP_ATTRIBUTE_HPP
