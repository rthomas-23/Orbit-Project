# CMakeList.txt : CMake project for OrbitPlotting, include source and define
# project specific logic here.
#

# Add source to this project's executable.

set(CMAKE_BUILD_TYPE Debug)

add_executable (OrbitPlotting "main.cpp" "main.h" "gnuplot-iostream.h" "MathTools.cpp" "MathTools.h" "OEs.cpp" "OEs.h" "OrbitCall.h" "OrbitCall.cpp" "F_and_G.cpp" "F_and_G.h" "GUI.cpp" "GUI.h" "WriteTextFile.cpp" "WriteTextFile.h")

find_package(Pangolin CONFIG REQUIRED)
find_package(zlib REQUIRED)
target_link_libraries(OrbitPlotting PRIVATE ${Pangolin_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OrbitPlotting PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.