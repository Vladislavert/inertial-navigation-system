/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|convert.hpp                       |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_PARSER_CONVERT_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_PARSER_CONVERT_HPP_

#include <sstream>
#include "typesData.hpp"

void			stringToVectDouble(const std::string& input, vectDouble_t& writeVect);
void			stringToVectDouble(const std::string& input, vectDouble2d_t& writeVect);
std::string		vectDoubleToString(const vectDouble_t& input);
vectDouble_t	vect2ToVect(const vectDouble2d_t& writeVect);

#endif // INERTIAL_NAVIGATION_SYSTEM_PARSER_CONVERT_HPP_
