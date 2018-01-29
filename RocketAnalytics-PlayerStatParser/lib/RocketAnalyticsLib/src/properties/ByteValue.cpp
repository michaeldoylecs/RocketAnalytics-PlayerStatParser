// Author: Michael Doyle
// Date: 8/12/17
// ByteValue.cpp

#include "ByteValue.hpp"

namespace ReplayParser {
	
	ByteValue::ByteValue() {
		byte_identifier = "";
		byte_value = "";
	}


	ByteValue::ByteValue(const ByteValue &byte) {
		byte_identifier = byte.byte_identifier;
		byte_value = byte.byte_value;
	}


	ByteValue::ByteValue(std::string identifier, std::string value) {
		byte_identifier = identifier;
		byte_value = value;
	}


	std::string ByteValue::get_identifer() {
		return byte_identifier;
	}


	std::string ByteValue::get_value() {
		return byte_value;
	}

}
