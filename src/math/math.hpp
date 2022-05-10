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

double			degToRad(const double &deg);
double			radToDeg(const double &rad);
double			squaring(const double &argument);
vectDouble_t	integralEuler(const vectDouble_t *time, const vectDouble_t *data, const double initialData);
double			integralEuler(const double dataPast, const double dataCurrent, double dt)
;

#endif // INERTIAL_NAVIGATION_SYSTEM_MATH_MATH_HPP_