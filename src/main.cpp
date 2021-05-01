#include "inputData.hpp"
#include "iostream"
#include "readFile.hpp"
#include "lowPassFilter.hpp"
#include "calcProbabilityCharact.hpp"
#include "draw.hpp"
// #include <../eigen3/Eigen/Dense>
#include <../libraries/eigen3/Eigen/Dense>

using namespace Eigen;

const double g0 = 9.780327; // ускорение силы тяжести на экваторе

double	gravitationalAccelerationCalc(double phi, double h);

int main()
{
	const std::string	DIR_RESOURCES = "./resource/";
	std::string			switchTesting;
	std::ifstream		file;
	std::string			nameFile;
	vectString_t		str;
	vectDouble2d_t		dataINS; // данные с БИНС
		

	std::cout << std::endl << "calculate trajectory..." << std::endl;
	std::cout << "__________________________________________" << std::endl;
	// nameFile = DIR_RESOURCES + "Car_7Km.h.txt";
	// nameFile = DIR_RESOURCES + "move Y(2 meters).txt";
	// nameFile = DIR_RESOURCES + "scooter.txt";
	nameFile = DIR_RESOURCES + "drift rate.txt";
	file.open(nameFile);

	if (checkOpenFile(file))
	{
		readStrFile(file, str);
		inputData(str, dataINS, 3);
		file.close();
		str.clear();
	}

	Vec xGravitAccel(dataINS.size()); 		// вектор значений ускорения свободного падения по оси X
	Vec yGravitAccel(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Y
	Vec zGravitAccel(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Z
	Vec xVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси X
	Vec yVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Y
	Vec zVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Z
	Vec xCoordinate;//(dataINS.size()); 		// вектор значений координат по оси X
	Vec yCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Y
	Vec zCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Z
	Vec time(dataINS.size());				// время в течение которого осуществляется замер

	double	mean_xGravitAccel; // математическое ожидание
	double	dispersion_xGravitAccel; // дисперсия
	double	mean_yGravitAccel; // математическое ожидание 
	double	dispersion_yGravitAccel; // дисперсия
	double	mean_zGravitAccel; // математическое ожидание 
	double	dispersion_zGravitAccel; // дисперсия
	double	g; // ускорение силы тяжести

	g = gravitationalAccelerationCalc(0.959931, 130);
	for (size_t i = 0; i < dataINS.size(); i++)
	{
			xGravitAccel[i] = dataINS[i][1];
			yGravitAccel[i] = dataINS[i][2];
			zGravitAccel[i] = -dataINS[i][3] + g;
			time[i] = dataINS[i][0];

	}
	Vec xAccelerationFilter;
	Vec yAccelerationFilter;
	Vec zAccelerationFilter;
	xAccelerationFilter = lowPassFilter(xGravitAccel, time, 0.02);
	yAccelerationFilter = lowPassFilter(yGravitAccel, time, 0.02);
	zAccelerationFilter = lowPassFilter(zGravitAccel, time, 0.02);

	mean_xGravitAccel = 0.0340018;//meanCalculate(xGravitAccel);
	dispersion_xGravitAccel = 8.08182e-05;//dispersionCalculate(xGravitAccel, mean_xGravitAccel);

	mean_yGravitAccel = 0.0588195;meanCalculate(yGravitAccel);
	dispersion_yGravitAccel = 7.39393e-05;//dispersionCalculate(yGravitAccel, mean_yGravitAccel);

	mean_zGravitAccel = -0.0674869 ;//meanCalculate(zGravitAccel);
	dispersion_zGravitAccel = 0.000118275;dispersionCalculate(zGravitAccel, mean_zGravitAccel);
	// xAccelerationFilter = lowPassFilter(xAccelerationFilter, time, 1);
	// yAccelerationFilter = lowPassFilter(yAccelerationFilter, time, 1);
	// zAccelerationFilter = lowPassFilter(zAccelerationFilter + g, time, 1);
	Plot plotX;
	Plot plotY;
	Plot plotZ;

	drawGraph(time, xGravitAccel, &plotX, "acceleration X", 0);
	drawLine(time, 3*sqrt(dispersion_xGravitAccel) + mean_xGravitAccel, &plotX, "SD", 0);
	drawLine(time, mean_xGravitAccel, &plotX, "mean", 0);
	drawLine(time, -3*sqrt(dispersion_xGravitAccel) + mean_xGravitAccel, &plotX, "SD", 1);

	drawGraph(time, yGravitAccel, &plotY,"acceleration Y", 0);
	drawLine(time, 3*sqrt(dispersion_yGravitAccel) + mean_yGravitAccel, &plotY, "SD", 0);
	drawLine(time, mean_yGravitAccel, &plotY, "mean", 0);
	drawLine(time, -3*sqrt(dispersion_yGravitAccel) + mean_yGravitAccel, &plotY, "SD", 1);

	drawGraph(time, yGravitAccel, &plotZ,"acceleration Z", 0);
	drawLine(time, 3*sqrt(dispersion_zGravitAccel) - mean_zGravitAccel, &plotZ, "SD", 0);
	drawLine(time, -mean_zGravitAccel, &plotZ, "mean", 0);
	drawLine(time, -3*sqrt(dispersion_zGravitAccel) - mean_zGravitAccel, &plotZ, "SD", 1);

	xGravitAccel = xAccelerationFilter;
	yGravitAccel = yAccelerationFilter;
	zGravitAccel = zAccelerationFilter;

	// drawLine(time, 3*sqrt(dispersion_xGravitAccel), plot1,"line");
	// drawLine(time, -3*sqrt(dispersion_xGravitAccel), "line");

	std::cout << "mean x = " << mean_xGravitAccel << " "
			  << "dispersion x = "<< dispersion_xGravitAccel << " "
			  << "3*sigma x = " << 3*sqrt(dispersion_xGravitAccel) << std::endl;
	std::cout << "mean y = " << mean_yGravitAccel << " "
			  << "dispersion y = " << dispersion_yGravitAccel << " "
			  << "3*sigma x = " << 3*sqrt(dispersion_yGravitAccel) << std::endl;
	std::cout << "mean z = " << mean_zGravitAccel << " "
			  << "dispersion z = " << dispersion_zGravitAccel << " "
			  << "3*sigma x = " << 3*sqrt(dispersion_zGravitAccel) << std::endl;

	std::cout << "g = " << g << std::endl;

	// std::cout << "mean X" << mean_xGravitAccel << std::endl;
	// std::cout << "dispersion X" << dispersion_xGravitAccel << std::endl;

	// std::cout << "mean Y" << mean_yGravitAccel << std::endl;
	// std::cout << "dispersion Y" << dispersion_yGravitAccel << std::endl;


	// std::cout << "mean Z" << mean_zGravitAccel << std::endl;
	// std::cout << "dispersion Z" << dispersion_zGravitAccel << std::endl;
	// for (size_t i = 0; i < dataINS.size(); i++)
	// {
			
	// }
	//dispersion_xGravitAccel = 3 * std::sqrt(dispersion_xGravitAccel);

	g = gravitationalAccelerationCalc(0.959931, 130);
	// double startValue = 000;
	double startValue = 0.000;
	Vec time1(xGravitAccel.size() - startValue);
	Vec xGravitAccel1(xGravitAccel.size() - startValue);
	Vec yGravitAccel1(xGravitAccel.size() - startValue);
	Vec zGravitAccel1(xGravitAccel.size() - startValue);
	for	(int i = startValue; i < xGravitAccel.size() - startValue; i++)
	{
		time1[i - startValue] = time[i];
		xGravitAccel1[i - startValue] = xGravitAccel[i];
		yGravitAccel1[i - startValue] = yGravitAccel[i];
		zGravitAccel1[i - startValue] = zGravitAccel[i];
	}

	// Plot plotX_filter;
	// Plot plotY_filter;
	// drawLine(time, 0.014, &plotX_filter, "SD", 0);
	drawGraph(time1, xGravitAccel1 - mean_xGravitAccel, "acceleration filter X");	
	drawGraph(time1, yGravitAccel1 - mean_yGravitAccel, "acceleration filter Y");
	drawGraph(time1, zGravitAccel1 - mean_zGravitAccel, "acceleration filter Z");


	xVeloucity = integralEuler(time1, xGravitAccel1 - mean_xGravitAccel);
	yVeloucity = integralEuler(time1, yGravitAccel1 - mean_yGravitAccel);
	zVeloucity = integralEuler(time1, zGravitAccel1 - mean_zGravitAccel);

	drawGraph(time1, xVeloucity, "veloucity X");
	drawGraph(time1, yVeloucity, "veloucity Y");
	drawGraph(time1, zVeloucity, "veloucity Z");

	std::cout << "value veloucityY = " << yVeloucity[yVeloucity.size() - 2] << std::endl;

	xCoordinate = integralEuler(time, xVeloucity);
	yCoordinate = integralEuler(time, yVeloucity);
	zCoordinate = integralEuler(time, zVeloucity);

	drawGraph(time1, xCoordinate, "coordinate X");
	drawGraph(time1, yCoordinate, "coordinate Y");
	drawGraph(time1, zCoordinate, "coordinate Z");
	

	// расчитать мат ожидание и дисперсию

}

/*
	расчёт ускорения силы тяжести

	phi - широта
	h 	- долгота
*/
double	gravitationalAccelerationCalc(double phi, double h)
{
	double g;

	g = g0 * (1 + 0.0053024 * squaring(std::sin(phi)) - 0.0000058 * squaring(std::sin(squaring(phi)))) - (3.686 / 1000000) * h;

	return (g);
}

