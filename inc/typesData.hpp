/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|typesData.hpp                     |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_TYPES_DATA_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_TYPES_DATA_HPP_

#include <vector>
#include <string>
#include "sciplot.hpp"

using namespace sciplot;

typedef std::vector<double>								vectDouble_t;
typedef std::vector<std::vector<double>>				vectDouble2d_t;
typedef std::vector<std::vector<std::vector<double>>>	vectDouble3d_t;
typedef std::vector<std::string> 						vectString_t;
typedef std::vector<sciplot::Plot>						vectPlot_t;
typedef std::vector<std::vector<sciplot::PlotXD>>		vectPlot2d_t;

template <class T>
struct vector3d
{
	vector3d(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector3d(){}
	T x;
	T y;
	T z;
};
#endif // INERTIAL_NAVIGATION_SYSTEM_TYPES_DATA_HPP_
