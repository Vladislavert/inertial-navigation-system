#ifndef TYPESDATA_HPP
#define TYPESDATA_HPP

#include <vector>
#include <string>
#include "sciplot.hpp"

using namespace sciplot;

typedef std::vector<double>								vectDouble_t;
typedef std::vector<std::vector<double>>				vectDouble2d_t;
typedef std::vector<std::vector<std::vector<double>>>	vectDouble3d_t;
typedef std::vector<std::string> 						vectString_t;
typedef std::vector<sciplot::PlotXD>					vectPlot_t;
typedef std::vector<std::vector<sciplot::PlotXD>>		vectPlot2d_t;


#endif