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


std::string ChangeBytes(std::string buffer, std::vector<int> bytes, const int index) {
	for (int i = 0; i < bytes.size(); i++)
		buffer = ChangeOneByte(buffer, (char)bytes[i], index + i);

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


std::string AddBytes(std::string buffer, std::vector<int> bytes, const int index) {
	for (int i = 0; i < bytes.size(); i++)
		buffer = AddOneByte(buffer, (char)bytes[i], index + i);

	return buffer;
}


std::string AddBytesToEnd(std::string buffer, std::vector<int> bytes, const int index) {
	return AddBytes(buffer, bytes, index);
}
