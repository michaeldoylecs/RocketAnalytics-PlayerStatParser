// Author: Michael Doyle
// Date: 8/13/17
// Byte.hpp

#ifndef BYTE_H
#define BYTE_H

#include <cstdint>
#include <string>

namespace ReplayParser {

	class Byte {
		public:
			Byte();
			Byte(std::uint8_t value);
			Byte(const Byte &byte);
			std::uint8_t get_value();
			int get_bit(int index);
			std::string to_string();

		private:
			union {
				uint8_t value;
				struct {
					std::uint8_t bit1 : 1; // Least Significant
					std::uint8_t bit2 : 1; // 
					std::uint8_t bit3 : 1; // 
					std::uint8_t bit4 : 1; // System dependant, but how my system
					std::uint8_t bit5 : 1; // currently reads replays.
					std::uint8_t bit6 : 1; // 
					std::uint8_t bit7 : 1; // 
					std::uint8_t bit8 : 1; // Most Significant
				}bits;
			}byte_value;
	};

}

#endif
