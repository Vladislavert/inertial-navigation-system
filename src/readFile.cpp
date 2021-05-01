#include "readFile.hpp"
// #include <cmath>

bool	checkOpenFile(std::ifstream &file)
{
	if (!file)
	{
		std::cout << "file open error" << std::endl;
		return (0);
	}
	return (1);
}

void	readStrFile(std::ifstream &file, vectString_t &str)
{
	std::string temp;

	while (getline(file, temp))
		str.push_back(temp);
}
