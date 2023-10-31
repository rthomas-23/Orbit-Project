# CMakeList.txt : CMake project for OrbitPlotting, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OrbitPlotting  "Matrix.cpp" "Matrix.h" "MathTools.cpp" "MathTools.h" "test.cpp" "OEs.cpp" "OEs.h" "OrbitPlotting.cpp" "OrbitPlotting.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OrbitPlotting PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
