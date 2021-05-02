#include "inputData.hpp"

#include <iostream>

/**
 * @brief парсер для данных из файлов, записанных в vector<string>
 * 
 * @param str данные из файла
 * @param gtInputVector двумерный вектор, в который запишутся данные из файла
 * @param numbeOfLines количество строк, которые нужно пропустить(например: шапка файла)
 */
void	inputData(const vectString_t &str, vectDouble2d_t &gtInputVector, const size_t numbeOfLines)
{
	size_t		j;
	size_t		i;
	std::string	gtInput;

	i = 1;
	for (; i <= numbeOfLines; i++);
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
