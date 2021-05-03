#ifndef AHRS_hpp
#define AHRS_hpp

#include "typesData.hpp"
#include <math.hpp>

double	*getAngleFromAccelerometer(const double dataAccelerometer[3]);
double	*getAngleGyroscope(const double dataGyroscopePast[3], const double dataGyroscopeCurrent[3], const double dt);
double	*getAngleMagnetometer(const double *dataMagnetometer);
double	absRad(const double rad);


#endif