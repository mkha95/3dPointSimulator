cmake_minimum_required(VERSION 3.10)
project(3DPointSimulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find VTK package
find_package(VTK REQUIRED)

set(SOURCES
    main.cpp
    Point.cpp
    Force.cpp
    Simulator.cpp
    VTKWriter.cpp
    ConfigParser.cpp
)

set(HEADERS
    Vector3D.h
    Point.h
    Force.h
    Simulator.h
    VTKWriter.h
    ConfigParser.h
)

add_executable(3DPointSimulator ${SOURCES} ${HEADERS})

# Set output directory to run/
set_target_properties(3DPointSimulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/run"
)

target_compile_features(3DPointSimulator PRIVATE cxx_std_17)

# Link VTK libraries
target_link_libraries(3DPointSimulator ${VTK_LIBRARIES})
vtk_module_autoinit(
  TARGETS 3DPointSimulator
  MODULES ${VTK_LIBRARIES}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(3DPointSimulator m)
endif()

install(TARGETS 3DPointSimulator DESTINATION bin)