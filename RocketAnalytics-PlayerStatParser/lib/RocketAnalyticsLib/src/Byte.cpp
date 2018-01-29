// Author: Michael Doyle
// Date: 8/13/17
// Byte.cpp

#include "Byte.hpp"

namespace ReplayParser {

	Byte::Byte() {
		byte_value.value = 0;
	}


	Byte::Byte(std::uint8_t value) {
		byte_value.value = value;
	}


	Byte::Byte(const Byte &byte) {
		byte_value.value = byte.byte_value.value;
	}


	std::uint8_t Byte::get_value() {
		return byte_value.value;
	}


	int Byte::get_bit(int index) {
		std::uint8_t bit_value = 0;
		switch (index) {
			case 0:
				bit_value = byte_value.bits.bit1;
				break;
			case 1:
				bit_value = byte_value.bits.bit2;
				break;
			case 2:
				bit_value = byte_value.bits.bit3;
				break;
			case 3:
				bit_value = byte_value.bits.bit4;
				break;
			case 4:
				bit_value = byte_value.bits.bit5;
				break;
			case 5:
				bit_value = byte_value.bits.bit6;
				break;
			case 6:
				bit_value = byte_value.bits.bit7;
				break;
			case 7:
				bit_value = byte_value.bits.bit8;
				break;
			default:
				bit_value = 0;
				break;
		}
		return bit_value;
	}


	std::string Byte::to_string() {
		std::string bit1 = std::to_string(byte_value.bits.bit1);
		std::string bit2 = std::to_string(byte_value.bits.bit2);
		std::string bit3 = std::to_string(byte_value.bits.bit3);
		std::string bit4 = std::to_string(byte_value.bits.bit4);
		std::string bit5 = std::to_string(byte_value.bits.bit5);
		std::string bit6 = std::to_string(byte_value.bits.bit6);
		std::string bit7 = std::to_string(byte_value.bits.bit7);
		std::string bit8 = std::to_string(byte_value.bits.bit8);
		std::string output = bit8 + bit7 + bit6 + bit5 + bit4 + bit3 + bit2 + bit1;
		return output;
	}

}
