#ifndef READFILE_HPP
#define READFILE_HPP

#include <iostream>
#include <fstream>
#include "typesData.hpp"

bool	checkOpenFile(std::ifstream &file);
void	readVectFile(std::ifstream &file, vectDouble_t &str);
void	readStrFile(std::ifstream &file, vectString_t &str);

#endif