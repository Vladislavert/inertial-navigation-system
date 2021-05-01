#include "convert.hpp" 

void	stringToVectDouble(const std::string &input, vectDouble_t &writeVect)
{
	std::istringstream	iss(input);
	std::string			temp;

	while (iss >> temp)
		writeVect.push_back(atof(&temp[0]));
}

void	stringToVectDouble(const std::string &input, vectDouble2d_t &writeVect)
{
	vectDouble_t 	tempVect;

	stringToVectDouble(input, tempVect);
	writeVect.push_back(tempVect);
}

std::string	vectDoubleToString(const vectDouble_t &input)
{
	std::string	tempStr;

	for (size_t i = 0; i < input.size(); i++)
	{
		tempStr += std::to_string(input[i]); 
	}	
	return (tempStr);
}

vectDouble_t	vect2ToVect(const vectDouble2d_t &writeVect)
{
	vectDouble_t	tempVect;
	
	for (size_t i = 0; i < writeVect.size(); i++)
		for (size_t j = 0; j < writeVect[i].size(); j++)
			tempVect.push_back(writeVect[i][j]);
	return (tempVect);
}
