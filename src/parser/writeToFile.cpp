/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|writeToFile.cpp                   |*/
/*	|__________________________________|*/
/* ************************************ */

#include "writeToFile.hpp"

void	writeToFile(const vectDouble2d_t& data)
{
	std::ofstream		fileOutputData;

	fileOutputData.open("test.txt");
	for	(auto & i : data)
	{
		fileOutputData << std::fixed << i[1] << ","
					   << std::fixed << i[0] << ","
					   << std::fixed << i[2] << std::endl;
	}
	fileOutputData.close();
}