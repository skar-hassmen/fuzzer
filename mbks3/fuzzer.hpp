#include<vector>

int RandomInt(int left, int right);

int GetSizeHeaderOfConfig(std::string buffer);

std::string ChangeOneByte(std::string buffer, const char byte, const int index);
std::string ChangeBytes(std::string buffer, std::vector<int> bytes, const int index);

std::string AddOneByte(std::string buffer, const char byte, const int index);
std::string AddBytes(std::string buffer, std::vector<int> bytes, const int index);

std::string AddBytesToEnd(std::string buffer, std::vector<int> bytes, const int index);