// Author: Michael Doyle
// Date: 7/23/17
// ReplayFileReader.cpp

#include "../include/ReplayFileReader.hpp"
#include <iostream>

namespace ReplayParser {

	ReplayFileReader::ReplayFileReader() {

	}

	ReplayFileReader::ReplayFileReader(std::string filepath) {
		this->replay_file_stream.open(filepath, std::ios::binary);
		this->replay_file_path = filepath;
		if (this->replay_file_stream.is_open()) {
			std::cout << "Failed to open file stream for '" << replay_file_path << "'";
		}
	}

	ReplayFileReader::~ReplayFileReader() {
		if (replay_file_stream.is_open()) {
			replay_file_stream.close();
		}
	}

	std::int8_t ReplayFileReader::read_int8_from_file() {
		std::int8_t raw_int = 0;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_int;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_int), sizeof(raw_int));
		return raw_int;
	}

	std::int32_t ReplayFileReader::read_int32_from_file() {
		std::int32_t raw_int = 0;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_int;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_int), sizeof(raw_int));
		return raw_int;
	}

	std::int64_t ReplayFileReader::read_int64_from_file() {
		std::int64_t raw_int = 0;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_int;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_int), sizeof(raw_int));
		return raw_int;
	}

	float ReplayFileReader::read_float_from_file() {
		float raw_float = 0.0;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_float;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_float), sizeof(raw_float));
		return raw_float;
	}

	bool ReplayFileReader::read_bool_from_file() {
		bool raw_bool = false;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_bool;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_bool), sizeof(raw_bool));
		return raw_bool;
	}

	std::string ReplayFileReader::read_string_from_file(int length) {
		std::string raw_string;
		if (!replay_file_stream) {
			std::cout << "File stream not open for '" << replay_file_path << "'";
			return raw_string;
		}
		replay_file_stream.read(reinterpret_cast<char *>(&raw_string), length);
		return raw_string;
	}

}
