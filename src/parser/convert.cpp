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

/**
 * @brief конвератция из vector<double> в string
 * 
 * @param input входной вектор
 * @return строка, в которую запишется значение из входного вектора
 */
std::string	vectDoubleToString(const vectDouble_t& input)
{
	std::string	tempStr;

	for (double i : input)
		tempStr += std::to_string(i);

	return (tempStr);
}

/**
 * @brief конвертация из vector<vector<double>> в vector<double>
 * 
 * @param writeVect двумерный вектор
 * @return одномерный вектор, в который запишется значение из двумерного вектора
 */
vectDouble_t	vect2ToVect(const vectDouble2d_t& writeVect)
{
	vectDouble_t	tempVect;
	
	for (const auto & vect : writeVect)
		for (double j : vect)
			tempVect.push_back(j);

	return (tempVect);
}
