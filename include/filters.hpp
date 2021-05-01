#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP

#include "typesData.hpp"

Vec		lowPassFilter(Vec out, Vec dt, double T);
double	*complementaryFilter(double *angleAccelerometer, double *angleGyroscope, double *angleMagnetometer);

#endif