/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|readFile.cpp                      |*/
/*	|__________________________________|*/
/* ************************************ */

#include "readFile.hpp"

/**
 * @brief проверка на открытия файла
 * 
 * @param file файловый дескриптор
 * @return true файл существует 
 * @return false ошибка открытия файла
 */
bool	checkOpenFile(std::ifstream &file)
{
	if (!file)
	{
		std::cout << "file open error" << std::endl;
		return (0);
	}
	return (1);
}

/**
 * @brief запись в vector<string> из файла
 * 
 * @param file файловый дескриптор
 * @param str vector<string>, в который записались данные из файла
 */
void	readStrFile(std::ifstream &file, vectString_t &str)
{
	std::string temp;

	while (getline(file, temp))
		str.push_back(temp);
}
