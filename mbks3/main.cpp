#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>

#include "config.hpp"
#include "debug.hpp"
#include "files.hpp"
#include "fuzzer.hpp"

std::string startStateConfig;

std::string ReturnStartStateConfig(void) {
	return startStateConfig;
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
	std::cin >> number;
	
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
		}
		else if (number == 2) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<char> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back((char)byte);
			}

			config = ChangeBytes(config, bytes, index);
		}
		else if (number == 3) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int byte;
			std::cout << "Input byte\n> ";
			std::cin >> std::hex >> byte;

			config = AddOneByte(config, (char)byte, index);
		}
		else if (number == 4) {
			int index;
			std::cout << "Input index\n> ";
			std::cin >> std::dec >> index;

			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<char> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back((char)byte);
			}

			config = AddBytes(config, bytes, index);
		}
		else if (number == 5) {
			int len;
			std::cout << "Input len\n> ";
			std::cin >> std::dec >> len;

			std::vector<char> bytes;

			for (int i = 0; i < len; i++) {
				int byte;
				std::cout << "Input byte " << "[" << i + 1 << "]" << "\n> ";
				std::cin >> std::hex >> byte;

				bytes.push_back((char)byte);
			}

			config = AddBytesToEnd(config, bytes, config.size());
		}
		else if (number == 6) {
			DebugMode();
		}
		else if (number == 7) {
			AutoMode();
		}
		else if (number == 8) {
			config = ReturnStartStateConfig();
		}
		else if (number == 9) {
			std::cout << config << std::endl;
		}
		else if (number == 10) {
			exit(0);
		}
		else {
			std::cout << "Wrong operation!" << std::endl;
		}
	}
}


int main(void) {
	startStateConfig = ReadDataFromConfigFile(pathDir + "\\" + configName);
	ChooseMove();
	return 0;
}