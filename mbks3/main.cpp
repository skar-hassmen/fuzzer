#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <random>

#include "config.hpp"
#include "debug.hpp"
#include "files.hpp"
#include "fuzzer.hpp"


std::string startStateConfig;

std::string ReturnStartStateConfig(void) {
	return startStateConfig;
}


int GetSizeHeaderOfConfig(std::string buffer) {
	return buffer.find("/start");
}


int RandomInt(int left, int right) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(left, right);
	return dist(gen);
}


void AutoMode(std::string buffer) {
	int lengthHeader = GetSizeHeaderOfConfig(buffer);

	while (1) {
		int variantMove = RandomInt(1, 2);

		if (variantMove == 1) {
			int sizeBytes = RandomInt(1, 4);
			if (sizeBytes == 1) {
				std::vector<int> boundaryBytes = { 0x00, 0xFF };
				int numberByte = RandomInt(0, boundaryBytes.size() - 1);
				int index = RandomInt(1, lengthHeader - sizeBytes);
				int offset = RandomInt(1, (int)(lengthHeader - sizeBytes) / 2);
				buffer = ChangeOneByte(buffer, (char)boundaryBytes[numberByte], index);
				
				while (index + offset <= lengthHeader - sizeBytes) {
					index += offset;
					buffer = ChangeOneByte(buffer, (char)boundaryBytes[numberByte], index);
				}
			}
			else if (sizeBytes == 2) {
				std::vector<std::vector<int>> boundaryBytes = { {0xFF, 0xFF}, {0x7F, 0xFF}, {0x80, 0x00}, {0x7F, 0xFE} };
				int numberByte = RandomInt(0, boundaryBytes.size() - 1);
				int index = RandomInt(1, lengthHeader - sizeBytes);
				buffer = ChangeBytes(buffer, boundaryBytes[numberByte], index);
			}
			else if (sizeBytes == 3) {
				std::vector<int> boundaryBytes = { 0xFF, 0xFF, 0xFF };
				int index = RandomInt(1, lengthHeader - sizeBytes);
				buffer = ChangeBytes(buffer, boundaryBytes, index);
			}
			else {
				std::vector<int> boundaryBytes = { 0xFF, 0xFF, 0xFF, 0xFF };
				int index = RandomInt(1, lengthHeader - sizeBytes);
				buffer = ChangeBytes(buffer, boundaryBytes, index);
			}
		}
		else {
			std::vector<int> Bytes;
			int countSymbols = RandomInt(1, 500);

			for (int i = 0; i < countSymbols; i++)
				Bytes.push_back(0x24);

			buffer = AddBytesToEnd(buffer, Bytes, buffer.size() - 1);
		}

		WriteDataToConfigFile(pathDir + "\\" + configName, buffer);
		if (DebugMode() == true) return;

		WriteDataToConfigFile(pathDir + "\\" + configName, ReturnStartStateConfig());
	}
}


void PrintMainMenu(void) {
	std::cout << "======= Main menu =======" << std::endl;
	std::cout << "1. Change one byte (user)" << std::endl;
	std::cout << "2. Change bytes (user)" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "3. Add one byte (user)" << std::endl;
	std::cout << "4. Add bytes (user)" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "5. Add bytes to end (user)" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "6. Run debug mode (auto)" << std::endl;
	std::cout << "7. Run auto mode (auto)" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "8. Return start state config file (auto)" << std::endl;
	std::cout << "9. Print config (auto)" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "10. Exit (auto)" << std::endl;
	std::cout << "=========================\n" << std::endl;
}

int InputOperation(void) {
	int number;
	std::cout << "Input operation\n> ";
	std::cin >> std::dec >> number;
	
	return number;
}

void ChooseMove(void) {
	std::string config = ReturnStartStateConfig();

	while (1) {
		PrintMainMenu();
		int number = InputOperation();
		
		if (number == 1) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int byte;
			std::cout << "Input byte\n> ";
			std::cin >> std::hex >> byte;

			config = ChangeOneByte(config, (char)byte, index);
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 2) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<int> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back(byte);
			}

			config = ChangeBytes(config, bytes, index);
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 3) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int byte;
			std::cout << "Input byte\n> ";
			std::cin >> std::hex >> byte;

			config = AddOneByte(config, (char)byte, index);
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 4) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<int> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back(byte);
			}

			config = AddBytes(config, bytes, index);
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 5) {
			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<int> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back(byte);
			}

			config = AddBytesToEnd(config, bytes, config.size() - 1);
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 6) {
			DebugMode();
		}
		else if (number == 7) {
			AutoMode(config);
		}
		else if (number == 8) {
			config = ReturnStartStateConfig();
			WriteDataToConfigFile(pathDir + "\\" + configName, config);
		}
		else if (number == 9) {
			std::cout << config << std::endl;
		}
		else if (number == 10) {
			return;
		}
		else {
			std::cout << "Wrong operation!" << std::endl;
		}
	}
}


int main(void) {
	startStateConfig = ReadDataFromConfigFile(pathDir + "\\" + configName);
	ChooseMove();
	WriteDataToConfigFile(pathDir + "\\" + configName, startStateConfig);
	return 0;
}