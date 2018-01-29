// Author: Michael Doyle
// Date: 8/10/17
// ReplayHeader.hpp

#ifndef REPLAY_HEADER_H
#define REPLAY_HEADER_H

#include "properties\Property.hpp"
#include "Version.hpp"
#include "BinaryReader.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace ReplayParser {

	class ReplayHeader {
	public:
		ReplayHeader();
		// Deserializing in each header is an issue. shouldn't be public.
		static ReplayHeader deserialize_header(BinaryReader& binary_reader);

		std::uint32_t get_header_size();
		std::uint32_t get_crc1();
		std::string get_version_string();
		std::uint32_t get_version_major();
		std::uint32_t get_version_minor();
		std::string get_replay_identifier();
		std::vector<Property> get_properties();
		std::uint32_t get_body_size();
		std::uint32_t get_crc2();

	private:
		std::uint32_t header_size;
		std::uint32_t crc1;
		Version version;
		std::string replay_identifier;
		std::vector<Property> replay_properties;
		std::uint32_t body_size;
		std::uint32_t crc2;

		void parse_header_size(BinaryReader& binary_reader);
		void parse_crc1(BinaryReader& binary_reader);
		void parse_version(BinaryReader& binary_reader);
		void check_for_empty_bits(BinaryReader& binary_reader);
		void parse_replay_identifier(BinaryReader& binary_reader);
		void parse_properties(BinaryReader& binary_reader, std::vector<Property>& properties);
		Property parse_property(BinaryReader& binary_reader);
		void parse_body_size(BinaryReader& binary_reader);
		void parse_crc2(BinaryReader& binary_reader);

	};

}

#endif
