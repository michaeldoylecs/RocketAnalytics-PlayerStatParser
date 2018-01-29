// Author: Michael Doyle
// Date: 8/10/17
// Version.cpp

#include "Version.hpp"

namespace ReplayParser {

	Version::Version() {
		version_major = 0;
		version_minor = 0;
	}


	Version::Version(std::uint32_t major, std::uint32_t minor) {
		set_version(major, minor);
	}


	Version::~Version() {
	}


	void Version::set_version(std::uint32_t major, std::uint32_t minor) {
		version_major = major;
		version_minor = minor;
	}


	std::uint32_t Version::get_major_value() {
		return version_major;
	}


	std::uint32_t Version::get_minor_value() {
		return version_minor;
	}


	std::string Version::to_string() {
		return std::to_string(version_major) +
				"." + std::to_string(version_minor);
	}
}
