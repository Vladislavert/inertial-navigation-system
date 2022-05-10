/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|filters.hpp                       |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_FILTERS_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_FILTERS_HPP_

#include "typesData.hpp"

void			lowPassFilter(vectDouble_t *input, const vectDouble_t *time, const double T);
// vectDouble_t	highPassFilter(const vectDouble_t *input, const vectDouble_t *time, const double T);
vectDouble_t	complementaryFilter(const vectDouble_t *angleAccelerometer, const vectDouble_t *angleGyroscope, const vectDouble_t *angleMagnetometer);

#endif // INERTIAL_NAVIGATION_SYSTEM_FILTERS_HPP_
