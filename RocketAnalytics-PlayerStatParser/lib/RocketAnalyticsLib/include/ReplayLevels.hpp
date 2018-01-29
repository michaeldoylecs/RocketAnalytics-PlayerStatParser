// Author: Michael Doyle
// Date: 1/28/18
// ReplayLevels.hpp

#ifndef REPLAY_LEVELS_H
#define REPLAY_LEVELS_H

#include "BinaryReader.hpp"

using std::vector;
using std::string;

namespace ReplayParser {

	class ReplayLevels {
	public:
		ReplayLevels();
		static ReplayLevels deserialize_levels(BinaryReader& binary_reader);

		vector<string> get_levels();
		size_t get_level_count();

	private:
		vector<string> levels;
	};

}

#endif
