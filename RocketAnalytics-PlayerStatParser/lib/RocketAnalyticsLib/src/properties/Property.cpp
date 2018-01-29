// Author: Michael Doyle
// Date: 8/11/17
// Property.cpp

#include "PropertyValue.hpp"
#include "Property.hpp"

namespace ReplayParser {

	Property::Property() {
		set_none();
	}


	Property::Property(const Property &property) {
		property_name = property.property_name;
		property_value = property.property_value;
	}


	void Property::set_none() {
		property_name = "None";
		property_value.set_none();
	}


	void Property::set_int(std::string name, std::uint32_t value) {
		property_name = name;
		property_value.set_int(value);
	}


	void Property::set_string(std::string name, std::string value) {
		property_name = name;
		property_value.set_string(value);
	}


	void Property::set_name(std::string name, std::string value) {
		property_name = name;
		property_value.set_name(value);
	}


	void Property::set_bool(std::string name, std::uint8_t value) {
		property_name = name;
		property_value.set_bool(value);
	}


	void Property::set_qword(std::string name, std::uint64_t value) {
		property_name = name;
		property_value.set_qword(value);
	}

	
	void Property::set_byte(std::string name, std::string identifier, std::string value) {
		property_name = name;
		ByteValue byte(identifier, value);
		property_value.set_byte(byte);
	}


	void Property::set_float(std::string name, float value) {
		property_name = name;
		property_value.set_float(value);
	}


	void Property::set_array(std::string name, std::vector< std::vector<Property> > value) {
		property_name = name;
		property_value.set_array(value);
	}


	std::string Property::get_name() {
		return property_name;
	}


	PType Property::get_type() {
		return property_value.get_type();
	}

	PropertyValue Property::get_value() {
		return property_value;
	}


	std::string Property::get_value_as_string() {
		return property_value.get_value_as_string();
	}


	//IMPROVE: Maintain level of abstraction
	std::string Property::to_string() {
		std::string to_string_value = "";
		to_string_value += get_name() + ": ";
		if (get_type() == PType::ARRAY_PROPERTY) {
			to_string_value += "\n";
		}
		to_string_value += get_value_as_string();
		return to_string_value;
	}

}
