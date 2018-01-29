// Author: Michael Doyle
// Date: 8/11/17
// PropertyType.cpp

#include "properties\PropertyType.hpp"

namespace ReplayParser {

	std::string PropertyType::property_type_strings[9] = {
		"None",
		"IntProperty",
		"StrProperty",
		"NameProperty",
		"BoolProperty",
		"QWordProperty",
		"ByteProperty",
		"FloatProperty",
		"ArrayProperty"
	};


	std::string PropertyType::property_type_to_string(PType property_type) {
		if (property_type == PType::NONE) {
			return property_type_strings[0];
		}
		else if (property_type == PType::INT_PROPERTY) {
			return property_type_strings[1];
		}
		else if (property_type == PType::STR_PROPERTY) {
			return property_type_strings[2];
		}
		else if (property_type == PType::NAME_PROPERTY) {
			return property_type_strings[3];
		}
		else if (property_type == PType::BOOL_PROPERTY) {
			return property_type_strings[4];
		}
		else if (property_type == PType::QWORD_PROPERTY) {
			return property_type_strings[5];
		}
		else if (property_type == PType::BYTE_PROPERTY) {
			return property_type_strings[6];
		}
		else if (property_type == PType::FLOAT_PROPERTY) {
			return property_type_strings[7];
		}
		else if (property_type == PType::ARRAY_PROPERTY) {
			return property_type_strings[8];
		}
		else {
			return "Error converting PType to std::string";
		}
	}


	PType PropertyType::string_to_property_type(std::string property_type) {
		if (property_type == property_type_strings[1]) {
			return PType::INT_PROPERTY;
		}
		else if (property_type == property_type_strings[2]) {
			return PType::STR_PROPERTY;
		}
		else if (property_type == property_type_strings[3]) {
			return PType::NAME_PROPERTY;
		}
		else if (property_type == property_type_strings[4]) {
			return PType::BOOL_PROPERTY;
		}
		else if (property_type == property_type_strings[5]) {
			return PType::QWORD_PROPERTY;
		}
		else if (property_type == property_type_strings[6]) {
			return PType::BYTE_PROPERTY;
		}
		else if (property_type == property_type_strings[7]) {
			return PType::FLOAT_PROPERTY;
		}
		else if (property_type == property_type_strings[8]) {
			return PType::ARRAY_PROPERTY;
		}
		else {
			return PType::NONE;
		}
	}

}
