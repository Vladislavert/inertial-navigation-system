/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|readFile.hpp                      |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_PARSER_READ_FILE_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_PARSER_READ_FILE_HPP_

#include <iostream>
#include <fstream>
#include "typesData.hpp"

bool	checkOpenFile(std::ifstream &file);
void	readVectFile(std::ifstream &file, vectDouble_t &str);
void	readStrFile(std::ifstream &file, vectString_t &str);

#endif // INERTIAL_NAVIGATION_SYSTEM_PARSER_READ_FILE_HPP_
