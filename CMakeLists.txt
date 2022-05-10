cmake_minimum_required(VERSION 3.0.2)
project(inertial_navigation_system)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_FLAGS "-Wall -Werror -Wextra")
# set(COMMON_FLAGS "-g")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")

find_package (Eigen3  REQUIRED)
find_package (Threads)
find_package(yaml-cpp REQUIRED)

include_directories(
	  src/
    inc/
	  ${EIGEN3_INCLUDE_DIR}
	  ${YAML_CPP_INCLUDE_DIR}
	  src/draw
	  src/estimate_position
    src/math
	  src/parser
    libraries/sciplot/sciplot
)

set(DRAW_CPP_FILES
    src/draw/draw.cpp
)

set(ESTIMATE_POSITION_CPP_FILES
    src/estimate_position/ahrs.cpp
    src/estimate_position/estimatePositionWgs.cpp
)

set(MATH_CPP_FILES
    src/math/calcProbabilityCharact.cpp
    src/math/coordinateTransform.cpp
    src/math/math.cpp
    src/math/rotationMatrix.cpp
)

set(PARSER_CPP_FILES
    src/parser/convert.cpp
    src/parser/inputData.cpp
    src/parser/readFile.cpp
    src/parser/writeToFile.cpp
)

set(CPP_FILES
    src/applicationStart.cpp
    src/filters.cpp
    src/gravitationalAccelerationCalc.cpp
    src/initialExhibition.cpp
)

add_library(inertial_navigation_system STATIC 
${DRAW_CPP_FILES}
${ESTIMATE_POSITION_CPP_FILES}
${MATH_CPP_FILES}
${PARSER_CPP_FILES}
${CPP_FILES}
)

add_executable(main ../src/main.cpp)

target_link_libraries(inertial_navigation_system yaml-cpp)
target_link_libraries(main inertial_navigation_system)
