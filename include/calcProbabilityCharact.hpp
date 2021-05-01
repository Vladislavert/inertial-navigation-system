#ifndef CALCPROBABILITYCHARACT_HPP
#define CALCPROBABILITYCHARACT_HPP

#include "typesData.hpp"
#include "math.hpp"

double	meanCalculate(const Vec &dataArray);
double	dispersionCalculate(const Vec &dataArray, const double &mean);

#endif