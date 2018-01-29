// Author: Michael Doyle
// Date: 8/24/17
// ReplayHeader.cpp

#include <iostream>
#include "ReplayLevels.hpp"

using std::uint32_t;
using std::string;
using std::vector;

namespace ReplayParser {

	ReplayLevels::ReplayLevels() {
	}

	ReplayLevels ReplayLevels::deserialize_levels(BinaryReader& binary_reader) {
		ReplayLevels replay_levels;
		uint32_t level_count = binary_reader.read_aligned_uint32();
		string level;
		for (uint32_t i = 0; i < level_count; i++) {
			level = binary_reader.read_length_prefixed_string();
			replay_levels.levels.push_back(level);
		}
		return replay_levels;
	}

	vector<string> ReplayLevels::get_levels() {
		return levels;
	}

	size_t ReplayLevels::get_level_count() {
		return levels.size();
	}

}
