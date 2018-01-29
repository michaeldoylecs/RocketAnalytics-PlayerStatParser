// Author: Michael Doyle
// Date: 8/12/17
// PropertyValue.cpp

#include "ByteValue.hpp"
#include "PropertyType.hpp"
#include "PropertyValue.hpp"
#include "Property.hpp"

namespace ReplayParser {

	PropertyValue::PropertyValue() {
		set_none();
	}


	PropertyValue::PropertyValue(const PropertyValue &propertyValue) {
		PType type = propertyValue.property_type;
		if (type == PType::INT_PROPERTY) {
			set_int(propertyValue.property_value.int32);
		}
		else if (type == PType::STR_PROPERTY) {
			set_string(propertyValue.property_value.string);
		}
		else if (type == PType::NAME_PROPERTY) {
			set_name(propertyValue.property_value.string);
		}
		else if (type == PType::BOOL_PROPERTY) {
			set_bool(propertyValue.property_value.int8);
		}
		else if (type == PType::QWORD_PROPERTY) {
			set_qword(propertyValue.property_value.int64);
		}
		else if (type == PType::BYTE_PROPERTY) {
			set_byte(propertyValue.property_value.byte);
		}
		else if (type == PType::FLOAT_PROPERTY) {
			set_float(propertyValue.property_value.f);
		}
		else if (type == PType::ARRAY_PROPERTY) {
			set_array(propertyValue.property_value.list);
		}
		else {
			set_none();
		}
	}


	PropertyValue &PropertyValue::operator=(const PropertyValue &propertyValue) {
		PType type = propertyValue.property_type;
		if (type == PType::INT_PROPERTY) {
			set_int(propertyValue.property_value.int32);
		}
		else if (type == PType::STR_PROPERTY) {
			set_string(propertyValue.property_value.string);
		}
		else if (type == PType::NAME_PROPERTY) {
			set_name(propertyValue.property_value.string);
		}
		else if (type == PType::BOOL_PROPERTY) {
			set_bool(propertyValue.property_value.int8);
		}
		else if (type == PType::QWORD_PROPERTY) {
			set_qword(propertyValue.property_value.int64);
		}
		else if (type == PType::BYTE_PROPERTY) {
			set_byte(propertyValue.property_value.byte);
		}
		else if (type == PType::FLOAT_PROPERTY) {
			set_float(propertyValue.property_value.f);
		}
		else if (type == PType::ARRAY_PROPERTY) {
			set_array(propertyValue.property_value.list);
		}
		else {
			set_none();
		}

		return *this;
	}


	PropertyValue::~PropertyValue() {
		deconstruct_union_values_if_necessary();
	}


	void PropertyValue::set_none() {
		property_type = PType::NONE;
	}


	void PropertyValue::set_int(std::uint32_t int32) {
		deconstruct_union_values_if_necessary();
		property_type = PType::INT_PROPERTY;
		property_value.int32 = int32;
	}


	void PropertyValue::set_string(std::string string) {
		deconstruct_union_values_if_necessary();
		property_type = PType::STR_PROPERTY;
		new (&property_value.string) std::string(string); // HACK: Is this proper?
	}


	void PropertyValue::set_name(std::string name) {
		deconstruct_union_values_if_necessary();
		property_type = PType::NAME_PROPERTY;
		new (&property_value.string) std::string(name); //HACK: Is this proper?
	}


	void PropertyValue::set_bool(std::uint8_t int8) {
		deconstruct_union_values_if_necessary();
		property_type = PType::BOOL_PROPERTY;
		property_value.int8 = int8;
	}


	void PropertyValue::set_qword(std::uint64_t int64) {
		deconstruct_union_values_if_necessary();
		property_type = PType::QWORD_PROPERTY;
		property_value.int64 = int64;
	}


	void PropertyValue::set_byte(ByteValue byte) {
		deconstruct_union_values_if_necessary();
		property_type = PType::BYTE_PROPERTY;
		new (&property_value.byte) ByteValue(byte); //HACK: Is this proper?
	}


	void PropertyValue::set_byte(std::string identifier, std::string value) {
		deconstruct_union_values_if_necessary();
		property_type = PType::BYTE_PROPERTY;
		new (&property_value.byte) ByteValue(identifier, value); //HACK: Is this proper?
	}


	void PropertyValue::set_float(float f) {
		deconstruct_union_values_if_necessary();
		property_type = PType::FLOAT_PROPERTY;
		property_value.f = f;
	}


	void PropertyValue::set_array(std::vector< std::vector<Property> > property_list) {
		deconstruct_union_values_if_necessary();
		property_type = PType::ARRAY_PROPERTY;
		new (&property_value.list) std::vector< std::vector<Property> >(property_list); // HACK: Is this proper?
	}


	void PropertyValue::deconstruct_union_values_if_necessary() {
		if (property_type == PType::STR_PROPERTY) {
			property_value.string.~basic_string();
		}
		else if (property_type == PType::NAME_PROPERTY) {
			property_value.string.~basic_string();
		}
		else if (property_type == PType::BYTE_PROPERTY) {
			property_value.byte.~ByteValue();
		}
		else if (property_type == PType::ARRAY_PROPERTY) {
			property_value.list.~vector();
		}
	}


	PType PropertyValue::get_type() {
		return property_type;
	}


	std::string PropertyValue::get_value_as_string() {
		if (property_type == PType::INT_PROPERTY) {
			std::uint32_t stored_value = property_value.int32;
			std::string converted_value = std::to_string(stored_value);
			return converted_value;
		}
		else if (property_type == PType::STR_PROPERTY) {
			std::string stored_value = property_value.string;
			return stored_value;
		}
		else if (property_type == PType::NAME_PROPERTY) {
			std::string stored_value = property_value.string;
			return stored_value;
		}
		else if (property_type == PType::BOOL_PROPERTY) {
			bool stored_value = property_value.int8;
			std::string converted_value = std::to_string(stored_value);
			return converted_value;
		}
		else if (property_type == PType::QWORD_PROPERTY) {
			std::uint64_t stored_value = property_value.int64;
			std::string converted_value = std::to_string(stored_value);
			return converted_value;
		}
		else if (property_type == PType::BYTE_PROPERTY) {
			ByteValue byte = property_value.byte;
			std::string byte_identifier = byte.get_identifer();
			std::string byte_value = byte.get_value();
			std::string converted_value = byte_identifier + ": " + byte_value;
			return converted_value;
		}
		else if (property_type == PType::FLOAT_PROPERTY) {
			float stored_value = property_value.f;
			std::string converted_value = std::to_string(stored_value);
			return converted_value;
		}
		else if (property_type == PType::ARRAY_PROPERTY) {
			std::string converted_value = array_properties_to_string();
			return converted_value;
		}
		else {
			return "None";
		}
	}


	//IMPROVE: Function is a bit long and low level
	std::string PropertyValue::array_properties_to_string() {
		std::string string_value = "";
		size_t property_count = property_value.list.size();
		std::vector<Property> property_array;
		for (int i = 0; i < property_count; i++) {
			property_array = property_value.list[i];
			Property property;
			int index = 0;
			string_value += std::to_string(i) + ":\n\t";
			while (true) {
				property = property_array[index];
				if (property.get_type() == PType::NONE) {
					string_value += "\n";
					break;
				}
				else {
					if (index > 0) {
						string_value += ",\n\t";
					}
					string_value += property.get_name() + ": ";
					string_value += property.get_value_as_string();
					index++;
				}
			}

		}
		return string_value;
	}


	PropertyValue::UValue::UValue() {

	}


	PropertyValue::UValue::~UValue() {

	}

}
