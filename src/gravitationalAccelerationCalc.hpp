/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|gravitationalAccelerationCalc.hpp |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_GRAVITATIONAL_ACCELERATION_CALC_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_GRAVITATIONAL_ACCELERATION_CALC_HPP_

#include "typesData.hpp"
#include "math.hpp"

const double g0 = 9.780327; // ускорение силы тяжести на экваторе

double	gravitationalAccelerationCalc(double phi, double h);

#endif // INERTIAL_NAVIGATION_SYSTEM_GRAVITATIONAL_ACCELERATION_CALC_HPP_
