#include<vector>

std::string ChangeOneByte(std::string buffer, const char byte, const int index);
std::string ChangeBytes(std::string buffer, std::vector<char> bytes, const int index);

std::string AddOneByte(std::string buffer, const char byte, const int index);
std::string AddBytes(std::string buffer, std::vector<char> bytes, const int index);

std::string AddBytesToEnd(std::string buffer, std::vector<char> bytes, const int index);

void AutoMode(void);
