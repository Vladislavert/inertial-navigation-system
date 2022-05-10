/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|initialExhibition.hpp             |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_INITIAL_EXHIBITION_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_INITIAL_EXHIBITION_HPP_

#include "math.hpp"
#include "initParams.hpp"
#include "typesData.hpp"
#include "calcProbabilityCharact.hpp"

void	getCorrectData(vectDouble2d_t &dataIMU, const vectDouble2d_t &dataInitIMU, double g);
double	*accumulationPositionGNSS(vectDouble2d_t &dataInitGNSS);

#endif // INERTIAL_NAVIGATION_SYSTEM_INITIAL_EXHIBITION_HPP_
