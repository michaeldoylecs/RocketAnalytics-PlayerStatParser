// Author: Michael Doyle
// Date: 1/28/18
// Player.cpp

#include <vector>
#include "Player.hpp"

using namespace ReplayParser;

using std::vector;

namespace PlayerStatParser {

	Player::Player() {
		name = "";
		platform = "";
		onlineID = "";
		team = -1;
		mvp = 0;
		score = 0;
		goals = 0;
		assists = 0;
		saves = 0;
		shots = 0;
		games = 0;
	}

	Player::Player(vector<Property> properties) {
		name = properties.at(0).get_value_as_string();
		platform = properties.at(1).get_value_as_string();
		onlineID = properties.at(2).get_value_as_string();
		team = stoi(properties.at(3).get_value_as_string());
		mvp = 0;
		score = stoi(properties.at(4).get_value_as_string());
		goals = stoi(properties.at(5).get_value_as_string());
		assists = stoi(properties.at(6).get_value_as_string());
		saves = stoi(properties.at(7).get_value_as_string());
		shots = stoi(properties.at(8).get_value_as_string());
		games = 1;
	}

	Player& Player::operator+=(const Player& player) {
		this->mvp += player.mvp;
		this->score += player.score;
		this->goals += player.goals;
		this->assists += player.assists;
		this->saves += player.saves;
		this->shots += player.shots;
		this->games += player.games;
		return *this;
	}

}
