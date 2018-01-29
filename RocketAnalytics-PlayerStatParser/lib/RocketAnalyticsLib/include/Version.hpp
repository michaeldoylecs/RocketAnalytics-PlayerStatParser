// Author: Michael Doyle
// Date: 8/10/17
// Version.hpp

#ifndef VERSION_H
#define VERSION_H

#include <cstdint>
#include <string>

namespace ReplayParser {

	class Version {
		public:
			Version();
			Version(std::uint32_t major, std::uint32_t minor);
			~Version();
			std::uint32_t get_major_value();
			std::uint32_t get_minor_value();
			void set_version(std::uint32_t major, std::uint32_t minor);
			std::string to_string();

		private:
			std::uint32_t version_major;
			std::uint32_t version_minor;
	};

}

#endif
