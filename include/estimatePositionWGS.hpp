#ifndef ESTIMATEPOSITIONWGS_HPP
#define ESTIMATEPOSITIONWGS_HPP

#include "ahrs.hpp"
#include "filters.hpp"
#include "calcProbabilityCharact.hpp"
#include "gravitationalAccelerationCalc.hpp"

vectDouble2d_t	estimatePositionWGS(const vectDouble2d_t *dataIMU, const vectDouble2d_t *dataGNSS, const vectDouble_t *dataTime);	

#endif