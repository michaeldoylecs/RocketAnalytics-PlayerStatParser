// Author: Michael Doyle
// Date: 8/11/17
// PropertyType.hpp

#ifndef PROPERTY_TYPE_H
#define PROPERTY_TYPE_H

#include <string>

namespace ReplayParser {

	// QUESTION: Can this be moved to the source file?
	enum class PType {
		NONE,
		INT_PROPERTY,
		STR_PROPERTY,
		NAME_PROPERTY,
		BOOL_PROPERTY,
		QWORD_PROPERTY,
		BYTE_PROPERTY,
		FLOAT_PROPERTY,
		ARRAY_PROPERTY
	};


	class PropertyType {
		public:
			static std::string property_type_to_string(PType property_type);
			static PType string_to_property_type(std::string property_type);

		private:
			static std::string property_type_strings[];
	};

}

#endif
