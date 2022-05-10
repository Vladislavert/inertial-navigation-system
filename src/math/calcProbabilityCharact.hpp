/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|calcProbabilityCharact.hpp        |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_MATH_CALC_PROBABILITY_CHARACT_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_MATH_CALC_PROBABILITY_CHARACT_HPP_

#include "typesData.hpp"
#include "math.hpp"

double	meanCalculate(const vectDouble_t& dataArray);
double	dispersionCalculate(const vectDouble_t& dataArray, double mean);

#endif // INERTIAL_NAVIGATION_SYSTEM_MATH_CALC_PROBABILITY_CHARACT_HPP_