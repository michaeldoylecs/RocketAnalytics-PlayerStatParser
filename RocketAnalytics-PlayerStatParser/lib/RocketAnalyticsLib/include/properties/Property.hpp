// Author: Michael Doyle
// Date: 8/10/17
// Property.hpp

#ifndef PROPERTY_H
#define PROPERTY_H

#include "PropertyValue.hpp"
#include <vector>
#include <string>
#include <cstdint>

namespace ReplayParser {

	enum class PType;

	class Property {
		public:
			Property();
			Property(const Property &property);

			void set_none();
			void set_int(std::string name, std::uint32_t value);
			void set_string(std::string name, std::string value);
			void set_name(std::string name, std::string value);
			void set_bool(std::string name, std::uint8_t value);
			void set_qword(std::string name, std::uint64_t value);
			void set_byte(std::string name, std::string identifier, std::string value);
			void set_float(std::string name, float value);
			void set_array(std::string name, std::vector< std::vector<Property> > value);

			std::string get_name();
			PType get_type();
			PropertyValue get_value();
			std::string get_value_as_string();
			std::string to_string();

		private:
			std::string property_name;
			PropertyValue property_value;

	};

}

#endif
