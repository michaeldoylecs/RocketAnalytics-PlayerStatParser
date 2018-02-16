// Author: Michael Doyle
// Date: 1/28/18
// Player.hpp

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Property.hpp"

using ReplayParser::Property;
using std::string;
using std::vector;

namespace PlayerStatParser {

	class Player {
	public:
		string name;
		string platform;
		string onlineID;
		int team;
		int mvp;
		int score;
		int goals;
		int assists;
		int saves;
		int shots;
		int games;

		Player();
		Player(vector<Property> properties);

		Player& operator+=(const Player& player);
	};

}

#endif
