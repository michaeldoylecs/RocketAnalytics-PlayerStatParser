// Author: Michael Doyle
// Date: 8/12/17
// ByteValue.hpp

#ifndef BYTE_VALUE_H
#define BYTE_VALUE_H

#include <string>

namespace ReplayParser {

	class ByteValue {
		public:
			ByteValue();
			ByteValue(const ByteValue &byte);
			ByteValue(std::string identifier, std::string value);
			std::string get_identifer();
			std::string get_value();

		private:
			std::string byte_identifier;
			std::string byte_value;
	};
	
}

#endif
