/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|convert.cpp                       |*/
/*	|__________________________________|*/
/* ************************************ */

#include "convert.hpp" 

/**
 * @brief конвертация из string в vector<double>
 * 
 * @param input входная строка
 * @param writeVect вектор, в который запишется значение из входной строки
 */
void	stringToVectDouble(const std::string& input, vectDouble_t& writeVect)
{
	std::istringstream	iss(input);
	std::string			temp;

	while (iss >> temp)
		writeVect.push_back(atof(&temp[0]));
}

/**
 * @brief конвертация из string в vector<vector<double>>
 * 
 * @param input входная строка
 * @param writeVect двумерный вектор, в который запишется значение из входной строки
 */
void	stringToVectDouble(const std::string& input, vectDouble2d_t& writeVect)
{
	vectDouble_t 	tempVect;

	stringToVectDouble(input, tempVect);
	writeVect.push_back(tempVect);
}
