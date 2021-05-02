#ifndef MATH_HPP
#define MATH_HPP

#include "typesData.hpp"

double	squaring(const double &argument);
Vec		integralEuler(Vec time, Vec data);
double	integralEuler(const double dataPast, const double dataCurrent, double dt);


#endif