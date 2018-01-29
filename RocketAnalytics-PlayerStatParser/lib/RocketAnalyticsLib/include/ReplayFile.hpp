// Author: Michael Doyle
// Date: 7/23/17
// ReplayFileReader.hpp

#ifndef REPLAY_FILE_H
#define REPLAY_FILE_H

#include <cstdint>
#include <string>
#include <fstream>
#include "ReplayHeader.hpp"
#include "ReplayLevels.hpp"

namespace ReplayParser {

	class ReplayFile {
		public:
			ReplayFile(std::string filepath);

			ReplayHeader get_header();
			ReplayLevels get_levels();

		private:
			std::string replay_file_path;

			ReplayHeader replay_header;
			ReplayLevels replay_levels;
	};

}
#endif
