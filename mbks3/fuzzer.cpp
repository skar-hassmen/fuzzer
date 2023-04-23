#include <iostream>
#include <string>
#include <vector>

#include "fuzzer.hpp"


std::string ChangeOneByte(std::string buffer, const char byte, const int index) {
	try {
		buffer[index] = byte;
	}
	catch (const std::exception& error) {
		std::cout << "Index out of range!" << std::endl;
	}
	return buffer;
}


std::string ChangeBytes(std::string buffer, std::vector<char> bytes, const int index) {
	for (int i = 0; i < bytes.size(); i++)
		buffer = ChangeOneByte(buffer, bytes[i], index + i);

	return buffer;
}


std::string AddOneByte(std::string buffer, const char byte, const int index) {
	try {
		std::string temp;
		temp.push_back(byte);
		buffer.insert(index, temp);
	}
	catch (const std::exception& error) {
		std::cout << "Index out of range!" << std::endl;
	}
	return buffer;
}


std::string AddBytes(std::string buffer, std::vector<char> bytes, const int index) {
	for (int i = 0; i < bytes.size(); i++)
		buffer = AddOneByte(buffer, bytes[i], index + i);

	return buffer;
}


std::string AddBytesToEnd(std::string buffer, std::vector<char> bytes, const int index) {
	return AddBytes(buffer, bytes, index);
}


void AutoMode(void) {
	/*std::vector<std::vector<int>> boundaryBytes = {{0x00, 0xFF}, {0xFFFF, 0x7FFF, 0x8000, 0x7FFE}, {0xFFFFFF}, {0xFFFFFF}};
	std::string temp;
	char er = (boundaryBytes[1][2] >> (8 * 0)) & 0xff;
	temp.push_back((char)((boundaryBytes[1][2] >> (8 * 0)) & 0xFF));
	int y;
	std::cin >> y;*/
}
