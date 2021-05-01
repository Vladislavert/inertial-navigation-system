#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <sstream>
#include "typesData.hpp"

void			stringToVectDouble(const std::string &input, vectDouble_t &writeVect);
void			stringToVectDouble(const std::string &input, vectDouble2d_t &writeVect);
std::string		vectDoubleToString(const vectDouble_t &input);
vectDouble_t	vect2ToVect(const vectDouble2d_t &writeVect);

#endif
