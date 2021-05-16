#include "readConfigFile.hpp"

/**
 * @brief парсер для данных из файлов, записанных в vector<string>
 * 
 * @param str данные из файла
 * @param gtInputVector двумерный вектор, в который запишутся данные из файла
 * @param numbeOfLines количество строк, которые нужно пропустить(например: шапка файла)
 */

/**
 * @brief 
 * 
 * @param str 
 * @param numbeOfLines 
 */
static unsigned int	*inputConfigData(const vectString_t &str, const size_t numbeOfLines = 0)
{
	size_t		j;
	size_t		i;
	size_t		index;
	std::string	gtInput;
	unsigned int *result;

	result = new unsigned int(str.size());
	i = 1;
	for (; i <= numbeOfLines; i++);
	for	(; i < str.size(); i++)
	{
		gtInput = "";
		j = 0;	

		index = str[i].find(":");
		for (size_t k = index + 1; str[i][k] != ' '; k++)
		{
			gtInput += str[i][k];
		}
		result[i] = std::stoul(gtInput);
	}
	return (result);
}

unsigned int *readConfigFile()
{
	vectString_t	str;
	std::ifstream	file;
	unsigned int	*indxColumnsData;

	file.open(nameConfigFile);
	if (checkOpenFile(file))
	{
		readStrFile(file, str);
		indxColumnsData = inputConfigData(str, 1);
	}
	else
		std::cout << std::endl << "Error open config files. Check config file" << std::endl;
	return (indxColumnsData);
}