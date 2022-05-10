/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|applicationStart.hpp              |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_APPLICATION_START_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_APPLICATION_START_HPP_

#include "inputData.hpp"
#include "readFile.hpp"
#include "writeToFile.hpp"
#include "draw.hpp"
#include <../libraries/eigen3/Eigen/Dense>
#include "estimatePositionWgs.hpp"
#include "calcProbabilityCharact.hpp"
#include "initialExhibition.hpp"
#include "initParams.hpp"

void	applicationStart();

#endif // INERTIAL_NAVIGATION_SYSTEM_APPLICATION_START_HPP_
