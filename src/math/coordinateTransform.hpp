/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|coordinateTransform.hpp           |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_MATH_COORDINATE_TRANSFORM_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_MATH_COORDINATE_TRANSFORM_HPP_

#include "typesData.hpp"
#include "math.hpp"

// параметры Земли
const double e =  0.081819190842613; // эксцентриситет
const double f = 1/298.257223563; // геометрическое сжатие
const double a = 6378137; // большая полуось эллипсоида
// const double b = 6356752.314245; // малая полуось эллипсоида
const double b = a * (1 - f); // малая полуось эллипсоида



vectDouble_t	convertGeoEllipseToGeoNormal(const vectDouble_t *coordinateGeoEllipse);
vectDouble_t	convertGeoEllipseToGeoNormal(const double *coordinateGeoEllipse);
vectDouble_t	convertGeoNormalToGeoEllipse(const vectDouble_t *coordinateGeoNormal);
vectDouble_t	convertGeoNormalToGeoEllipse(const double *coordinateGeoNormal);

#endif // INERTIAL_NAVIGATION_SYSTEM_MATH_COORDINATE_TRANSFORM_HPP_