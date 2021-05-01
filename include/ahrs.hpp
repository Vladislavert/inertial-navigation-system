#ifndef AHRS_hpp
#define AHRS_hpp

#include "typesData.hpp"
#include <math.hpp>

double	*getAngleFromAccelerometer(double *dataAccelerometer);
double	*getAngleGyroscope(const double *dataGyroscope);
double	*getMagnetometer(const double *dataMagnetometer);


#endif