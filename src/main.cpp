#include "inputData.hpp"
#include "iostream"
#include "readFile.hpp"
#include "filters.hpp"
#include "calcProbabilityCharact.hpp"
#include "draw.hpp"
// #include <../eigen3/Eigen/Dense>
#include <../libraries/eigen3/Eigen/Dense>
#include "ahrs.hpp"

#define DEBUG

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
	nameFile = DIR_RESOURCES + "musicGlobalCoordinate.csv";
	file.open(nameFile);

	if (checkOpenFile(file))
	{
		readStrFile(file, str);
		inputData(str, dataINS, 1);
		file.close();
		str.clear();
	}

	Vec xAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси X
	Vec yAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Y
	Vec zAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Z
	Vec xVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси X
	Vec yVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Y
	Vec zVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Z
	Vec xCoordinate;//(dataINS.size()); 		// вектор значений координат по оси X
	Vec yCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Y
	Vec zCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Z
	Vec time(dataINS.size());				// время в течение которого осуществляется замер

	double	mean_xAcceleration; // математическое ожидание
	double	dispersion_xAcceleration; // дисперсия
	double	mean_yAcceleration; // математическое ожидание 
	double	dispersion_yAcceleration; // дисперсия
	double	mean_zAcceleration; // математическое ожидание 
	double	dispersion_zAcceleration; // дисперсия
	double	g; // ускорение силы тяжести

	g = gravitationalAccelerationCalc(0.959931, 190);
	double *dataAccelerometer;

	dataAccelerometer = new double[3];
	for (size_t i = 0; i < dataINS.size(); i++)
	{
			xAcceleration[i] = dataINS[i][0];
			yAcceleration[i] = dataINS[i][1];
			zAcceleration[i] = -dataINS[i][2] + g;
			dataAccelerometer[0] = xAcceleration[i];
			dataAccelerometer[1] = yAcceleration[i];
			dataAccelerometer[2] = zAcceleration[i];
			getAngleFromAccelerometer(dataAccelerometer);
			time[i] = dataINS[i][24] / 1000;
	}
	

	getAngleFromAccelerometer(dataAccelerometer);

	Vec xAccelerationFilter;
	Vec yAccelerationFilter;
	Vec zAccelerationFilter;
	xAccelerationFilter = lowPassFilter(xAcceleration, time, 0.02);
	yAccelerationFilter = lowPassFilter(yAcceleration, time, 0.02);
	zAccelerationFilter = lowPassFilter(zAcceleration, time, 0.02);

	mean_xAcceleration = meanCalculate(xAcceleration);
	dispersion_xAcceleration = dispersionCalculate(xAcceleration, mean_xAcceleration);

	mean_yAcceleration = meanCalculate(yAcceleration);
	dispersion_yAcceleration = dispersionCalculate(yAcceleration, mean_yAcceleration);

	mean_zAcceleration = meanCalculate(zAcceleration);
	dispersion_zAcceleration = dispersionCalculate(zAcceleration, mean_zAcceleration);
	// xAccelerationFilter = lowPassFilter(xAccelerationFilter, time, 1);
	// yAccelerationFilter = lowPassFilter(yAccelerationFilter, time, 1);
	// zAccelerationFilter = lowPassFilter(zAccelerationFilter + g, time, 1);
	Plot plotX;
	Plot plotY;
	Plot plotZ;

	drawGraph(&time, &xAcceleration, &plotX, "acceleration X", 0);
	// drawLine(&time, &(3*sqrt(dispersion_xAcceleration) + mean_xAcceleration), &plotX, "SD", 0);
	drawLine(&time, &(mean_xAcceleration), &plotX, "mean", 1);
	// drawLine(&time, -3*sqrt(dispersion_xAcceleration) + mean_xAcceleration, &plotX, "SD", 1);

	drawGraph(&time, &yAcceleration, &plotY,"acceleration Y", 0);
	// drawLine(&time, 3*sqrt(dispersion_yAcceleration) + mean_yAcceleration, &plotY, "SD", 0);
	drawLine(&time, &mean_yAcceleration, &plotY, "mean", 0);
	// drawLine(&time, -3*sqrt(dispersion_yAcceleration) + mean_yAcceleration, &plotY, "SD", 1);

	drawGraph(&time, &zAcceleration, &plotZ,"acceleration Z", 0);
	// drawLine(time, 3*sqrt(dispersion_zAcceleration) + mean_zAcceleration, &plotZ, "SD", 0);
	drawLine(&time, &mean_zAcceleration, &plotZ, "mean", 0);
	// drawLine(time, -3*sqrt(dispersion_zAcceleration) + mean_zAcceleration, &plotZ, "SD", 1);

	xAcceleration = xAccelerationFilter;
	yAcceleration = yAccelerationFilter;
	zAcceleration = zAccelerationFilter;

	// drawLine(time, 3*sqrt(dispersion_xAcceleration), plot1,"line");
	// drawLine(time, -3*sqrt(dispersion_xAcceleration), "line");

	#ifdef DEBUG
		std::cout << "mean x = " << mean_xAcceleration << " "
				<< "dispersion x = "<< dispersion_xAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_xAcceleration) << std::endl;
		std::cout << "mean y = " << mean_yAcceleration << " "
				<< "dispersion y = " << dispersion_yAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_yAcceleration) << std::endl;
		std::cout << "mean z = " << mean_zAcceleration << " "
				<< "dispersion z = " << dispersion_zAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_zAcceleration) << std::endl;

		std::cout << "g = " << g << std::endl;
	#endif

	// std::cout << "mean X" << mean_xAcceleration << std::endl;
	// std::cout << "dispersion X" << dispersion_xAcceleration << std::endl;

	// std::cout << "mean Y" << mean_yAcceleration << std::endl;
	// std::cout << "dispersion Y" << dispersion_yAcceleration << std::endl;


	// std::cout << "mean Z" << mean_zAcceleration << std::endl;
	// std::cout << "dispersion Z" << dispersion_zAcceleration << std::endl;
	// for (size_t i = 0; i < dataINS.size(); i++)
	// {
			
	// }
	//dispersion_xAcceleration = 3 * std::sqrt(dispersion_xAcceleration);

	g = gravitationalAccelerationCalc(0.959931, 130);
	// double startValue = 000;
	double startValue = 0.000;
	Vec time1(xAcceleration.size() - startValue);
	Vec xAcceleration1(xAcceleration.size() - startValue);
	Vec yAcceleration1(xAcceleration.size() - startValue);
	Vec zAcceleration1(xAcceleration.size() - startValue);
	for	(int i = startValue; i < xAcceleration.size() - startValue; i++)
	{
		time1[i - startValue] = time[i];
		xAcceleration1[i - startValue] = xAcceleration[i];
		yAcceleration1[i - startValue] = yAcceleration[i];
		zAcceleration1[i - startValue] = zAcceleration[i];
	}

	// Plot plotX_filter;
	// Plot plotY_filter;
	// drawLine(time, 0.014, &plotX_filter, "SD", 0);
	Vec dataX = xAcceleration1 - mean_xAcceleration;
	Vec dataY = yAcceleration1 - mean_yAcceleration;
	Vec dataZ = zAcceleration1 - mean_zAcceleration;
	drawGraph(&time1, &(dataX), "acceleration filter X");	
	drawGraph(&time1, &(dataY), "acceleration filter Y");
	drawGraph(&time1, &(dataZ), "acceleration filter Z");


	xVeloucity = integralEuler(time1, xAcceleration1 - mean_xAcceleration);
	yVeloucity = integralEuler(time1, yAcceleration1 - mean_yAcceleration);
	zVeloucity = integralEuler(time1, zAcceleration1 - mean_zAcceleration);

	drawGraph(&time1, &xVeloucity, "veloucity X");
	drawGraph(&time1, &yVeloucity, "veloucity Y");
	drawGraph(&time1, &zVeloucity, "veloucity Z");

	#ifdef DEBUG
		std::cout << "value veloucityY = " << yVeloucity[yVeloucity.size() - 2] << std::endl;
	#endif

	// xCoordinate = integralEuler(time1, xVeloucity);
	// yCoordinate = integralEuler(time1, yVeloucity);
	// zCoordinate = integralEuler(time1, zVeloucity);

	// drawGraph(&time1, &xCoordinate, "coordinate X");
	// drawGraph(&time1, &yCoordinate, "coordinate Y");
	// drawGraph(&time1, &zCoordinate, "coordinate Z");
	

	// расчитать мат ожидание и дисперсию

}

/**
 * @brief расчёт ускорения свободного падения
 * 
 * @param phi - широта
 * @param h - высота
 * @return ускорение свободного падения
 */
double	gravitationalAccelerationCalc(double phi, double h)
{
	double g;

	g = g0 * (1 + 0.0053024 * squaring(std::sin(phi)) - 0.0000058 * squaring(std::sin(squaring(phi)))) - (3.686 / 1000000) * h;

	return (g);
}

