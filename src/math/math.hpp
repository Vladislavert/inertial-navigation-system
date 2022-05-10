/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|math.hpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_MATH_MATH_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_MATH_MATH_HPP_

#include <../libraries/eigen3/Eigen/Dense>
#include "typesData.hpp"
#include "cmath"

double			degToRad(double deg);
double			radToDeg(double rad);
double			squaring(double argument);
vectDouble_t	integralEuler(const vectDouble_t& time, const vectDouble_t& data, double initialData);
double			integralEuler(double dataPast, double dataCurrent, double dt)
;

#endif // INERTIAL_NAVIGATION_SYSTEM_MATH_MATH_HPP_