// Author: Michael Doyle
// Date: 8/13/17
// BinaryReader.cpp

#include "BinaryReader.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <array>
#include <assert.h>

using std::runtime_error;
using std::ios;
using std::string;
using std::size_t;
using std::array;
using std::cout;
using std::endl;

//TODO: Add flag to see if file_bytes exist. Throw exception on bad read.

namespace ReplayParser {

	BinaryReader::BinaryReader(const string filepath) {
		try {
			byte_position = 0;
			bit_position = 0;
			read_file(filepath);
		}
		catch(const runtime_error &e) {
			file_bytes.resize(0);
			throw e;
		}
	}

	void BinaryReader::read_file(string filepath) {
		std::ifstream file_stream(filepath, ios::binary | ios::in);
		if (file_stream.is_open()) {
			size_t file_size = get_file_size(file_stream);
			file_bytes.resize(file_size);

			// HACK: Kinda hack to directly assign to Byte object memory space
			file_stream.read(reinterpret_cast<char*>(file_bytes.data()), file_size);
			file_stream.close();
		}
		else {
			throw runtime_error("Failed to open file exception");
		}
	}

	size_t BinaryReader::get_file_size(std::ifstream &file_stream) {
		size_t file_start = file_stream.tellg();
		file_stream.seekg(0, ios::end);
		size_t file_size = file_stream.tellg();
		file_stream.seekg(file_start, ios::beg);
		return file_size;
	}

	float BinaryReader::read_aligned_float() {
		try {
			const int FLOAT_SIZE = 4;
			array<Byte, FLOAT_SIZE> list_of_bytes;
			for (int index = 0; index < FLOAT_SIZE; index++) {
				list_of_bytes[index] = read_aligned_byte();
			}
			return bytes_to_float(list_of_bytes);
		}
		catch (runtime_error e) {
			cout << "Exception caught: " << e.what() << endl;
			return 0;
		}
	}

	float BinaryReader::bytes_to_float(array<Byte, 4> bytes) {
		float combined_value = 0.0f;
		memcpy(&combined_value, &bytes, sizeof(combined_value));
		return combined_value;
	}

	uint8_t BinaryReader::read_aligned_uint8() {
		try {
			Byte next_byte = read_aligned_byte();
			uint8_t read_value = next_byte.get_value();
			return read_value;
		}
		catch (runtime_error e) {
			cout << "Exception caught: " << e.what() << endl;
			return 0;
		}
	}

	uint32_t BinaryReader::read_aligned_uint32() {
		try {
			const int AMOUNT_OF_BYTES_TO_READ = 4;
			array<Byte, AMOUNT_OF_BYTES_TO_READ> list_of_bytes;
			for (int index = 0; index < AMOUNT_OF_BYTES_TO_READ; index++) {
				list_of_bytes[index] = read_aligned_byte();
			}
			uint32_t read_value = bytes_to_uint32(list_of_bytes);
			return read_value;
		}
		catch(runtime_error e){
			cout << "Exception caught: " << e.what() << endl;
			return 0;
		}
	}

	uint32_t BinaryReader::bytes_to_uint32(array<Byte, 4> bytes) {
		uint32_t combined_value = 0;
		memcpy(&combined_value, &bytes, sizeof(combined_value));
		return combined_value;
	}

	uint64_t BinaryReader::read_aligned_uint64() {
		try {
			const int AMOUNT_OF_BYTES_TO_READ = 8;
			array<Byte, AMOUNT_OF_BYTES_TO_READ> list_of_bytes;
			for (int index = 0; index < AMOUNT_OF_BYTES_TO_READ; index++) {
				list_of_bytes[index] = read_aligned_byte();
			}
			uint64_t read_value = bytes_to_uint64(list_of_bytes);
			return read_value;
		}
		catch (runtime_error e) {
			cout << "Exception caught: " << e.what() << endl;
			return 0;
		}
	}

	uint64_t BinaryReader::bytes_to_uint64(array<Byte, 8> bytes) {
		uint64_t combined_value = 0;
		memcpy(&combined_value, &bytes, sizeof(combined_value));
		return combined_value;
	}

	string BinaryReader::read_length_prefixed_string() {
		string string_value;
		uint32_t string_length = read_aligned_uint32();
		string_value = read_string_of_n_length(string_length);
		return string_value;
	}

	//TODO: Cleanup method
	string BinaryReader::read_string_of_n_length(uint32_t length) {
		try {
			char *string_array = new char[length];
			for (uint32_t index = 0; index < length; index++) {
				Byte next_byte = read_aligned_byte();
				uint8_t byte_value = next_byte.get_value();
				char next_char;
				memcpy(&next_char, &byte_value, sizeof(next_char));
				string_array[index] = next_char;
			}
			string string_value(string_array);
			delete string_array;
			return string_value;
		}
		catch (runtime_error e) {
			cout << "Exception caught: " << e.what() << endl;
			return string("READ_FAIL");
		}
	}

	Byte BinaryReader::read_aligned_byte() {
		if (bit_position != 0) {
			throw runtime_error(
				"Attempted to read byte with bit pointer misaligned"
			);
		}
		Byte next_byte = file_bytes.at(byte_position);
		increment_byte_position();
		return next_byte;
	}

	void BinaryReader::increment_byte_position() {
		byte_position++;
	}

	void BinaryReader::increment_bit_position() {
		bit_position++;
		if (bit_position > 7) {
			bit_position = 0;
			increment_byte_position();
		}
	}

	size_t BinaryReader::size() {
		return file_bytes.size();
	}

	void BinaryReader::close() {
		file_bytes.clear();
		byte_position = 0;
		bit_position = 0;
	}

}
