#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP

#include "typesData.hpp"

Vec		lowPassFilter(Vec input, Vec time, double T);
Vec		HighPassFilter(Vec input, Vec time, double T);
double	*complementaryFilter(double angleAccelerometer[2], double angleGyroscope[3], double angleMagnetometer[1]);

#endif