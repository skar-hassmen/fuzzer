#include <iostream>
#include <string>
#include <fstream>

#include "files.hpp"


std::string ReadDataFromConfigFile(std::string path) {
	std::string buffer;

	std::ifstream file(path.c_str());
	if (file.is_open())
		getline(file, buffer);
	else
		std::cout << "Error open file for read!" << std::endl;
	file.close();

	return buffer;
}


void WriteDataToConfigFile(std::string path, std::string buffer) {
	std::ofstream file(path.c_str());
	if (file.is_open())
		file << buffer;
	else 
		std::cout << "Error open file for write!" << std::endl;
	file.close();
}