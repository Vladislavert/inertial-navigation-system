/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|inputData.cpp                     |*/
/*	|__________________________________|*/
/* ************************************ */

#include "inputData.hpp"

/**
 * @brief парсер для данных из файлов, записанных в vector<string>
 * 
 * @param str данные из файла
 * @param gtInputVector двумерный вектор, в который запишутся данные из файла
 * @param numberOfLines количество строк, которые нужно пропустить(например: шапка файла)
 */
void			inputData(const vectString_t& str, vectDouble2d_t& gtInputVector, size_t numberOfLines)
{
	size_t		j;
	size_t		i;
	std::string	gtInput;

	i = 1;
	for (; i <= numberOfLines; i++);
	for	(; i < str.size(); i++)
	{
		gtInput = "";
		j = 0;	
		for (; j < str[i].size(); j++)
		{
			if (str[i][j] != ',')
			{
				gtInput += str[i][j];
			}
			else
				gtInput += " ";
		}
		stringToVectDouble(gtInput, gtInputVector);
	}
}
