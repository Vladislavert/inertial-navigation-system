#include "yaml-cpp/yaml.h"

int main()
{
	// инициализация переменных в yaml файле
	// const char *filename = "/home/vladislav/Documents/learning/4 course/2 semester/Синтез систем бортовых алгоритмов/courseWorking/inertial navigation system/config/indexDataConfig.yaml";
	// YAML::Node fs = YAML::LoadFile(filename);

	// const unsigned int indxGyro = fs["indxGyro"].as<unsigned int>();

	YAML::Node fs = YAML::LoadFile("/home/vladislav/projects/control_systems_tools/config/mission_1.yaml");

	int indxGyro = fs["point_count"].as<int>();

	// const unsigned int indxMagnet = fs["indxMagnet"].as<unsigned int>();
	// const unsigned int indxAcc = fs["indxAcc"].as<unsigned int>();
	return (0);
}

// #include "yaml-cpp/yaml.h"
// #include "iostream"

// int main()
// {
//    YAML::Emitter out;
//    out << "Hello, World!";
   
//    std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
//    return 0;
// }