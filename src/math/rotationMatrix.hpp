/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|rotationMatrix.hpp                |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_MATH_ROTATION_MATRIX_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_MATH_ROTATION_MATRIX_HPP_

#include "math.hpp"

Eigen::Matrix3d	rotationMatrix(const vectDouble_t &angl);
double			c(const double angl);
double			s(const double angl);

#endif // INERTIAL_NAVIGATION_SYSTEM_MATH_ROTATION_MATRIX_HPP_