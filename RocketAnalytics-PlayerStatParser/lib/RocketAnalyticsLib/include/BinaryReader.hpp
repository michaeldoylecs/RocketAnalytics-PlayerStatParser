// Author: Michael Doyle
// Date: 8/13/17
// BinaryReader.hpp

#ifndef BINARY_READER_H
#define BINARY_READER_H

#include "Byte.hpp"
#include <vector>

namespace ReplayParser {

	class ifstream;

	class BinaryReader {
		public:
			BinaryReader(const std::string file_path);
			float read_aligned_float();
			std::uint8_t read_aligned_uint8();
			std::uint32_t read_aligned_uint32();
			std::uint64_t read_aligned_uint64();
			std::string read_length_prefixed_string();
			std::size_t size();
			void close();

		private:                                                               
			std::vector<Byte> file_bytes;
			int byte_position;
			int bit_position;

			void read_file(std::string filepath);
			Byte read_aligned_byte();
			float bytes_to_float(std::array<Byte, 4> bytes);
			std::uint32_t bytes_to_uint32(std::array<Byte, 4> bytes);
			std::uint64_t bytes_to_uint64(std::array<Byte, 8> bytes);
			std::string read_string_of_n_length(std::uint32_t length);
			std::size_t get_file_size(std::ifstream &file_stream);
			void increment_byte_position();
			void increment_bit_position();
	};

}

#endif
