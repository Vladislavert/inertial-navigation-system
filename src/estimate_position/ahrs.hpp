/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|ahrs.hpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_AHRS_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_AHRS_HPP_

#include "typesData.hpp"
#include "filters.hpp"
#include <math.hpp>
#include "initParams.hpp"

vectDouble2d_t	getOrientation(const vectDouble_t initOrientation, const vectDouble2d_t *dataIMU, const vectDouble_t *dataTime);
vectDouble_t	getAngleAccelerometer(const vectDouble_t *dataAccelerometer);
vectDouble_t	getAngleGyroscope(const vectDouble_t *dataGyroscopePast, const vectDouble_t *dataGyroscopeCurrent, const double dt);
vectDouble_t	getAngleMagnetometer(const vectDouble_t *dataMagnetometer);
double			absRad(const double rad);

#endif // INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_AHRS_HPP_
