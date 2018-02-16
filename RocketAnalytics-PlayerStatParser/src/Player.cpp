// Author: Michael Doyle
// Date: 1/28/18
// Player.cpp

#include "Player.hpp"

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
