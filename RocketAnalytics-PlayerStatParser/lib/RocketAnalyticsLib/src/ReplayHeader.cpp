// Author: Michael Doyle
// Date: 8/24/17
// ReplayHeader.cpp

#include "ReplayHeader.hpp"
#include <iostream>

using std::uint32_t;
using std::string;
using std::vector;

namespace ReplayParser {

	ReplayHeader::ReplayHeader() {
	}

	ReplayHeader ReplayHeader::deserialize_header(BinaryReader& binary_reader) {
		ReplayHeader replay_header;
		replay_header.parse_header_size(binary_reader);
		replay_header.parse_crc1(binary_reader);
		replay_header.parse_version(binary_reader);
		replay_header.check_for_empty_bits(binary_reader);
		replay_header.parse_replay_identifier(binary_reader);
		replay_header.parse_properties(binary_reader, replay_header.replay_properties);
		replay_header.parse_body_size(binary_reader);
		replay_header.parse_crc2(binary_reader);
		return replay_header;
	}

	void ReplayHeader::parse_header_size(BinaryReader& binary_reader) {
		uint32_t parsed_header_size = binary_reader.read_aligned_uint32();
		header_size = parsed_header_size;
	}

	void ReplayHeader::parse_crc1(BinaryReader& binary_reader) {
		uint32_t parsed_crc1 = binary_reader.read_aligned_uint32();
		crc1 = parsed_crc1;
	}

	void ReplayHeader::parse_version(BinaryReader& binary_reader) {
		uint32_t version_major = binary_reader.read_aligned_uint32();
		uint32_t version_minor = binary_reader.read_aligned_uint32();
		version.set_version(version_major, version_minor);
	}

	void ReplayHeader::parse_replay_identifier(BinaryReader& binary_reader) {
		string parsed_replay_identifier = binary_reader.read_length_prefixed_string();
		replay_identifier = parsed_replay_identifier;
	}

	//IMPROVE: There must be a better way to handle discrepancies between replay versions
	void ReplayHeader::check_for_empty_bits(BinaryReader& binary_reader) {
		if (version.get_major_value() >= 868 && version.get_minor_value() >= 18) {
			binary_reader.read_aligned_uint32();
		}
	}

	void ReplayHeader::parse_properties(BinaryReader& binary_reader, vector<Property>& properties) {
		while (true) {
			Property property = parse_property(binary_reader);
			properties.push_back(property);
			if (property.get_type() == PType::NONE) {
				break;
			}
		}
	}

	//IMPROVE: Reduce function size and maintain levels of abstraction
	Property ReplayHeader::parse_property(BinaryReader& binary_reader) {
		// Property values
		Property property;
		string property_name;
		string type_string;
		PType property_type;

		// Potentially used variables
		uint8_t int8_value;
		uint32_t int32_value;
		uint64_t int64_value;
		string string_value;
		string identifier_value;
		vector<Property> array_property_list;
		float float_value;

		// More specific used variables
		uint32_t array_property_count;
		vector< vector<Property> > array_value;

		// Read property name
		property_name = binary_reader.read_length_prefixed_string();
		if (property_name == "None") {
			property.set_none();
			return property;
		}
		// Read property type
		type_string = binary_reader.read_length_prefixed_string();
		property_type = PropertyType::string_to_property_type(type_string);

		// Read property value based on type
		switch (property_type) {
		case PType::INT_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			int32_value = binary_reader.read_aligned_uint32();
			property.set_int(property_name, int32_value);
			break;
		case PType::STR_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			string_value = binary_reader.read_length_prefixed_string();
			property.set_string(property_name, string_value);
			break;
		case PType::NAME_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			string_value = binary_reader.read_length_prefixed_string();
			property.set_name(property_name, string_value);
			break;
		case PType::BOOL_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			int8_value = binary_reader.read_aligned_uint8();
			property.set_bool(property_name, int8_value);
			break;
		case PType::QWORD_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			int64_value = binary_reader.read_aligned_uint64();
			property.set_qword(property_name, int64_value);
			break;
		case PType::BYTE_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			identifier_value = binary_reader.read_length_prefixed_string();
			string_value = binary_reader.read_length_prefixed_string();
			property.set_byte(property_name, identifier_value, string_value);
			break;
		case PType::FLOAT_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			float_value = binary_reader.read_aligned_float();
			property.set_float(property_name, float_value);
			break;
		case PType::ARRAY_PROPERTY:
			binary_reader.read_aligned_uint64(); // Read length bytes away
			array_property_count = binary_reader.read_aligned_uint32();
			for (uint32_t i = 0; i < array_property_count; i++) {
				parse_properties(binary_reader, array_property_list);
				array_value.push_back(array_property_list);
				array_property_list.clear();
			}
			property.set_array(property_name, array_value);
			break;
		default:
			property.set_none();
		}

		return property;
	}

	void ReplayHeader::parse_body_size(BinaryReader& binary_reader) {
		uint32_t parsed_body_size = binary_reader.read_aligned_uint32();
		body_size = parsed_body_size;
	}

	void ReplayHeader::parse_crc2(BinaryReader& binary_reader) {
		uint32_t parsed_crc2 = binary_reader.read_aligned_uint32();
		crc2 = parsed_crc2;
	}

	uint32_t ReplayHeader::get_header_size() {
		return header_size;
	}

	uint32_t ReplayHeader::get_crc1() {
		return crc1;
	}

	string ReplayHeader::get_version_string() {
		return version.to_string();
	}

	uint32_t ReplayHeader::get_version_major() {
		return version.get_major_value();
	}

	uint32_t ReplayHeader::get_version_minor() {
		return version.get_minor_value();
	}

	string ReplayHeader::get_replay_identifier() {
		return replay_identifier;
	}

	vector<Property> ReplayHeader::get_properties() {
		return replay_properties;
	}

	uint32_t ReplayHeader::get_body_size() {
		return body_size;
	}

	uint32_t ReplayHeader::get_crc2() {
		return crc2;
	}

}
