/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|estimatePositionWgs.hpp           |*/
/*	|__________________________________|*/
/* ************************************ */


#ifndef INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_ESTIMATE_POSITION_WGS_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_ESTIMATE_POSITION_WGS_HPP_

#include "ahrs.hpp"
#include "filters.hpp"
#include "rotationMatrix.hpp"
#include "coordinateTransform.hpp"
#include "estimatePositionWgs.hpp"
#include "calcProbabilityCharact.hpp"
#include "gravitationalAccelerationCalc.hpp"

vectDouble2d_t	estimatePositionWgs(vectDouble2d_t& dataIMU, const vectDouble2d_t& dataGNSS, const double* meanInitGNSS, const vectDouble_t& dataTime);

#endif // INERTIAL_NAVIGATION_SYSTEM_ESTIMATE_POSITION_ESTIMATE_POSITION_WGS_HPP_