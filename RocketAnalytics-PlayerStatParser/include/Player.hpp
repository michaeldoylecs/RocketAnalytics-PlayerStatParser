// Author: Michael Doyle
// Date: 1/28/18
// Player.hpp

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

namespace PlayerStatParser {

	class Player {
	public:
		string name;
		string platform;
		string onlineID;
		int team;
		int score;
		int goals;
		int assists;
		int saves;
		int shots;
		int games;

		Player();
	};

}

#endif
