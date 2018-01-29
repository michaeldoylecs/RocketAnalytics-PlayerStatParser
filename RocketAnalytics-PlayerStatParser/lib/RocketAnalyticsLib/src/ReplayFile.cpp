// Author: Michael Doyle
// Date: 8/10/17
// ReplayFile.cpp

#include "ReplayFile.hpp"
#include "BinaryReader.hpp"
#include "ReplayHeader.hpp"

namespace ReplayParser {

	ReplayFile::ReplayFile(std::string filepath) {
		BinaryReader file_reader = BinaryReader(filepath);
		replay_header = ReplayHeader::deserialize_header(file_reader);
		replay_levels = ReplayLevels::deserialize_levels(file_reader);
		file_reader.close();
	}

	ReplayHeader ReplayFile::get_header() {
		return replay_header;
	}

	ReplayLevels ReplayFile::get_levels() {
		return replay_levels;
	}

}
