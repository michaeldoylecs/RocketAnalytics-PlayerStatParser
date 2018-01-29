// Author: Michael Doyle
// Date: 7/23/17
// ReplayFileReader.hpp

#ifndef REPLAY_FILE_READER_H
#define REPLAY_FILE_READER_H

#include <cstdint>
#include <string>
#include <fstream>

namespace ReplayParser {

	class ReplayFile;

	class ReplayFileReader {
		public:
			ReplayFileReader();
			ReplayFileReader(std::string filepath);
			~ReplayFileReader();
			std::int8_t	read_int8_from_file();  // Return 1 byte from file stream
			std::int32_t read_int32_from_file();  // Return 4 bytes from file stream
			std::int64_t read_int64_from_file();  // Return 8 bytes from file stream
			float read_float_from_file();  // Return float from file stream
			bool read_bool_from_file();  // Return bool from file stream
			std::string	read_string_from_file(int length);  // Return string from file stream


		private:
			std::ifstream replay_file_stream;
			std::string replay_file_path;
	};

}
#endif
