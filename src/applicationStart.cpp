/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|applicationStart.cpp              |*/
/*	|__________________________________|*/
/* ************************************ */

#include "applicationStart.hpp"

void	applicationStart()
{
	const std::string	DIR_RESOURCES = "../resource/";
	std::ifstream		file;
	std::ifstream		fileInit;
	std::ifstream		fileInitGNSS;
	std::string			nameFile; // название файла с основными данными
	std::string			nameFileInitExhibition; // название файла, где проводится определения ошибок датчиков(переименовать??)
	std::string			nameFileInitGNSS; // название файла с ГНСС, для накопления начальной позиции
	vectString_t		strTemp;
	vectDouble2d_t		dataSensors; // данные с датчиков
	vectDouble2d_t		dataFileInitGNSS; // данные для определения позиции
	vectDouble2d_t		dataSensorsInit; // данные с датчиков во время начальной инициализации
	vectDouble2d_t		positionWGS; // оценка позиции в WGS84(X, Y, Z)
	vectDouble_t		xPositionWGS;
	vectDouble_t		yPositionWGS;
	vectDouble_t		zPositionWGS;
	vectPlot2d_t		plotPositionXYZ(quantityAxes);
	Plot				plotPositionX;
	Plot				plotPositionY;
	Plot				plotPositionZ;
	double				g;
	double				*meanGNSS;

	nameFile = DIR_RESOURCES + "GNSSup_0.csv";
	nameFileInitGNSS = DIR_RESOURCES + "initGNSSup_0.csv";
	nameFileInitExhibition = DIR_RESOURCES + "initCondition2.csv";
	file.open(nameFile);
	fileInit.open(nameFileInitExhibition);
	fileInitGNSS.open(nameFileInitGNSS);
	if (checkOpenFile(file) && checkOpenFile(fileInit))
	{
		readStrFile(file, strTemp);
		inputData(strTemp, dataSensors, 1);
		strTemp.clear();
		file.close();
		readStrFile(fileInit, strTemp);
		inputData(strTemp, dataSensorsInit, 1);
		strTemp.clear();
		fileInit.close();
		readStrFile(fileInitGNSS, strTemp);
		inputData(strTemp, dataFileInitGNSS, 1);
		strTemp.clear();
		fileInit.close();
	}
	else
	{
		std::cout << "error open file" << std::endl;
		std::exit(0);
	}
	// запись данных с сенсоров из общего вектора в вектор соответствующие типу датчик
	vectDouble2d_t 		dataIMU; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble2d_t 		dataIMUInit; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
	vectDouble2d_t		dataGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble2d_t		dataInitGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble_t		dataTime; // время с начала замера данных с датчиков
	vectDouble_t		dataTimeInit; // время с начала замера данных с датчиков
	vectDouble_t		temp; // временный вектор, для заполнения
	vectDouble_t		tempInit; // временный вектор, для заполнения данных начальной выставки

	for	(auto & dataSensor : dataSensors)
	{
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensor[indxAcc + j]);
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensor[indxGyro + j]);
		for (unsigned int j = 0; j < quantityAxes - 1; j++)
			temp.push_back(dataSensor[indxMagnet + j]);
		dataIMU.push_back(temp);
		temp.clear();
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensor[indxGNSS + j]);
		dataGNSS.push_back(temp);
		dataTime.push_back(dataSensor[indxTime] / 1000);
		temp.clear();		
	}
	for	(auto & i : dataFileInitGNSS)
	{	
		temp.clear();
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(i[indxInitGNSS + j]);
		dataInitGNSS.push_back(temp);
	}
	for	(auto & dataSensorInit : dataSensorsInit)
	{
		for (unsigned int j = 0; j < quantityAxes; j++)
			tempInit.push_back(dataSensorInit[indxAcc + j]);
		for (unsigned int j = 0; j < quantityAxes; j++)
			tempInit.push_back(dataSensorInit[indxGyro + j]);
		for (unsigned int j = 0; j < quantityAxes - 1; j++)
			tempInit.push_back(dataSensorInit[indxMagnet + j]);
		dataIMUInit.push_back(tempInit);
		tempInit.clear();
		dataTimeInit.push_back(dataSensorInit[indxTime] / 1000);
		tempInit.clear();
	}
	meanGNSS = new double[quantityAxes];
	meanGNSS = accumulationPositionGNSS(dataInitGNSS);
	g = gravitationalAccelerationCalc(meanGNSS[0], meanGNSS[2]);
	getCorrectData(dataIMU, dataIMUInit, g);
	positionWGS = estimatePositionWgs(dataIMU, dataGNSS, meanGNSS, dataTime);
	delete[] meanGNSS;
	std::cout << "Широта в начальный момент времени\t= " << positionWGS[0][0] << std::endl;
	std::cout << "Долгота в начальный момент времени\t= " << positionWGS[0][1] << std::endl;
	std::cout << "Высота в начальный момент времени\t= " << positionWGS[0][2] << std::endl;
	std::cout << std::endl;
	std::cout << "Широта в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][0] << std::endl;
	std::cout << "Долгота в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][1] << std::endl;
	std::cout << "Высота в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][2] << std::endl;
	for	(auto & position : positionWGS)
	{
		xPositionWGS.push_back(position[0]);
		yPositionWGS.push_back(position[1]);
		zPositionWGS.push_back(position[2]);
	}
	writeToFile(positionWGS);

	drawGraph(&dataTime, &xPositionWGS, &plotPositionX, "xPosition", 0);
	drawGraph(&dataTime, &yPositionWGS, &plotPositionY, "yPosition", 0);
	drawGraph(&dataTime, &zPositionWGS, &plotPositionZ, "zPosition", 0);
	plotPositionX.grid().show();
	plotPositionY.grid().show();
	plotPositionZ.grid().show();
	plotPositionXYZ[0].push_back(plotPositionX);
	plotPositionXYZ[1].push_back(plotPositionY);
	plotPositionXYZ[2].push_back(plotPositionZ);
	Figure				figPosition = plotPositionXYZ;
	figPosition.size(600, 600);
	figPosition.show();
}
