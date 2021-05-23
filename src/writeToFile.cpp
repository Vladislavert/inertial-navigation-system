#include "writeToFile.hpp"

void	writeToFile(vectDouble2d_t *data)
{
	std::ofstream		fileOutputData;

	fileOutputData.open("test.txt");
	for	(unsigned int i = 0; i < (*data).size(); i++)
	{
		fileOutputData << std::fixed << (*data)[i][1] << ","
					   << std::fixed << (*data)[i][0] << ","
					   << std::fixed << (*data)[i][2] << std::endl;
	}
	fileOutputData.close();
}