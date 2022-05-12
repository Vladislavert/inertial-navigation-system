/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|estimatePositionWgs.cpp           |*/
/*	|__________________________________|*/
/* ************************************ */


#include "estimatePositionWgs.hpp"

// #define DEBUG
#define DEBUG1

#ifdef DEBUG
	#include "iostream"
	#include "draw.hpp"
#endif

#ifdef DEBUG1
	#include "iostream"
#endif

/**
 * @brief оценка позиции в геоцентрической СК(WGS-84)
 * 
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнитометр(X, Y)). Фильтруются внутри функции
 * @param dataGNSS данные с ГНСС приёмника в WGS-84(широта, долгота, высота)
 * @param meanInitGNSS координаты точки старта в геоцентрической эллипсоидальной СК
 * @param dataTime время с начала замера данных с датчиков
 * @return координаты в геоцентрической СК(WGS-84)(X, Y, Z)
 */
vectDouble2d_t	estimatePositionWgs(vectDouble2d_t& dataIMU, const vectDouble2d_t& dataGNSS, const double* meanInitGNSS, const vectDouble_t& dataTime)
{
	vectDouble2d_t			resCoordinateWGS; // результат оценки положения в ГСК
	vectDouble2d_t 			dataIMUTranspose(dataIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble_t			startCoordinateGeoNormal; // координаты начала стартовой СК в геоцентрической нормальной СК
	vectDouble_t			initialData;
	vectDouble2d_t			coordGeoNormalGNSS(dataGNSS[0].size());
	Eigen::Vector3d			acceleration; // ускорение
	vector3d<vectDouble_t>	accelerationVec;
	vector3d<vectDouble_t>	velocityVec;
	vector3d<vectDouble_t>	positionVec;
	Eigen::Vector3d			apparentAcceleration; // кажущееся ускорение
	vectDouble2d_t			orientation;
	vectDouble_t			temp;
	Eigen::Vector3d			gravityAcceleration;
	Eigen::Matrix3d			matrixRotation; 
	double					g;
	double					*error;
	double					time; // прошедшее время
	double					isSecond; // прошла ли секунда
	double					dt;

	for	(unsigned int i = 0; i < dataIMU[0].size(); i++)
		for (auto & j : dataIMU)
			dataIMUTranspose[i].push_back(j[i]);
	g = gravitationalAccelerationCalc(meanInitGNSS[0], meanInitGNSS[2]);
	gravityAcceleration << 0, 0, g;
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0.12);
	// фильтрация данных с БИНС
	 lowPassFilter(dataIMUTranspose[0], dataTime, 1);
	 lowPassFilter(dataIMUTranspose[1], dataTime, 1);
	 lowPassFilter(dataIMUTranspose[2], dataTime, 1);
	// for	(unsigned int i = 0; i < (*dataIMU).size(); i++)
	// 	for (unsigned int j = 0; j < (*dataIMU)[i].size(); j++)
	// 		(*dataIMU)[i][j] = dataIMUTranspose[j][i];
	// определение ориентации с помощью Attitude and Heading Reference System(AHRS)
	orientation.push_back(temp);
	matrixRotation = rotationMatrix(orientation[0]);
	orientation = getOrientation(orientation[0], dataIMU, dataTime);
	for	(unsigned int i = 0; i < orientation.size(); i++)
	{
		apparentAcceleration << dataIMU[i][0], dataIMU[i][1], dataIMU[i][2];
		matrixRotation = rotationMatrix(orientation[i]);
		acceleration = (matrixRotation.inverse() * apparentAcceleration) - gravityAcceleration;
		accelerationVec.x.push_back(acceleration[0]);
		accelerationVec.y.push_back(acceleration[1]);
		accelerationVec.z.push_back(acceleration[2]);
	}
	velocityVec.x = integralEuler(dataTime, accelerationVec.x, 0);
	velocityVec.y = integralEuler(dataTime, accelerationVec.y, 0);
	velocityVec.z = integralEuler(dataTime, accelerationVec.z, 0);
	time = 0;
	isSecond = 1;
	dt = dataTime[1] - dataTime[0];
	initialData = convertGeoEllipseToGeoNormal(meanInitGNSS);
	positionVec.x.push_back(integralEuler(initialData[0], velocityVec.x[0], dt));
	positionVec.y.push_back(integralEuler(initialData[1], velocityVec.y[0], dt));
	positionVec.z.push_back(integralEuler(initialData[2], velocityVec.z[0], dt));
	for (size_t i = 1; i < velocityVec.x.size() - 1; i++)
	{
		if (time >= isSecond)
		{
			initialData.clear();
			initialData = convertGeoEllipseToGeoNormal(dataGNSS[i]);
			positionVec.x.push_back(integralEuler(initialData[0], velocityVec.x[i], dt));
			positionVec.y.push_back(integralEuler(initialData[1], velocityVec.y[i], dt));
			positionVec.z.push_back(integralEuler(initialData[2], velocityVec.z[i], dt));
			// positionVec.x.push_back(integralEuler(positionVec.x[i - 1], velocityVec.x[i], dt));
			// positionVec.y.push_back(integralEuler(positionVec.y[i - 1], velocityVec.y[i], dt));
			// positionVec.z.push_back(integralEuler(positionVec.z[i - 1], velocityVec.z[i], dt));
			#ifdef DEBUG1
				std::cout << "initialData[0] = " << initialData[0] << std::endl;
				std::cout << "initialData[1] = " << initialData[1] << std::endl;
				std::cout << "initialData[2] = " << initialData[2] << std::endl;
				std::cout << "time = " << time << std::endl;
				std::cout << "second = " << isSecond<< std::endl;
				std::cout << i << std::endl;
			#endif
			isSecond += 1;
		}
		else
		{
			positionVec.x.push_back(integralEuler(positionVec.x[i - 1], velocityVec.x[i], dt));
			positionVec.y.push_back(integralEuler(positionVec.y[i - 1], velocityVec.y[i], dt));
			positionVec.z.push_back(integralEuler(positionVec.z[i - 1], velocityVec.z[i], dt));
		}
		time += dt;
		dt = dataTime[i + 1] - dataTime[i];
	}

	// перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
	// начальная выставка, для получения координат стартовой СК в геоцентрической СК(WGS-84)
	for	(unsigned int i = 0; i < dataGNSS[0].size(); i ++)
	{
		coordGeoNormalGNSS[i] = convertGeoEllipseToGeoNormal(dataGNSS[i]);
		#ifdef DEBUG
			std::cout << "GNSS = " << (*dataGNSS)[i][0] << std::endl;
		#endif
	}
	startCoordinateGeoNormal = convertGeoEllipseToGeoNormal(meanInitGNSS); // передавать значения полученные в результате начальной выставки(средние значения)
	#ifdef DEBUG
		std::cout << "X c ГНСС = " << startCoordinateGeoNormal[0] << std::endl;
		std::cout << "Y c ГНСС = " << startCoordinateGeoNormal[1] << std::endl;
		std::cout << "Z c ГНСС = " << startCoordinateGeoNormal[2] << std::endl;
	#endif
	// определение позиции путём интегрирования данных с акселерометра, а также коррекция позиции с помощью ГНСС
	error = new double[3];
	for (unsigned int i = 0; i < positionVec.x.size(); i++)
	{		
		temp.clear();
		error[0] = 0;//positionVec.x[i] + startCoordinateGeoNormal[0] - coordGeoNormalGNSS[i][0];
		error[1] = 0;//positionVec.y[i] + startCoordinateGeoNormal[1] - coordGeoNormalGNSS[i][1];
		error[2] = 0;//positionVec.z[i] + startCoordinateGeoNormal[2] - coordGeoNormalGNSS[i][2];
		temp.push_back(positionVec.x[i]);// + startCoordinateGeoNormal[0] - error[0]);
		temp.push_back(positionVec.y[i]);// + startCoordinateGeoNormal[1] - error[1]);
		temp.push_back(positionVec.z[i]);// + startCoordinateGeoNormal[2] - error[2]);
		resCoordinateWGS.push_back(temp);
	}
	delete[] error;
	for	(unsigned int i = 0; i < resCoordinateWGS.size(); i++)
		resCoordinateWGS[i] = convertGeoNormalToGeoEllipse(resCoordinateWGS[i]);
	#ifdef DEBUG
		std::cout << "широта = " << resCoordinateWGS[0][0] << std::endl;
		std::cout << "долгота = " << resCoordinateWGS[0][1] << std::endl;
		std::cout << "высота = " << resCoordinateWGS[0][2] << std::endl;
	#endif
	return (resCoordinateWGS);
}