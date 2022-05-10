/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|inputData.hpp                     |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_PARSER_INPUT_DATA_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_PARSER_INPUT_DATA_HPP_

#include <sstream>
#include "convert.hpp"
#include "typesData.hpp"

void			inputData(const vectString_t& str, vectDouble2d_t& gtInputVector, size_t numberOfLines = 0);

#endif // INERTIAL_NAVIGATION_SYSTEM_PARSER_INPUT_DATA_HPP_
