cmake_minimum_required(VERSION 3.10)

project("TrajectoryViewer")

find_package(Qt5Core)
find_package(Qt5PrintSupport)
find_package(Qt5Widgets)
find_package(Qt5Charts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")
set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od")

if (MSVC_VERSION GREATER_EQUAL "1900")
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
	if (_cpp_latest_flag_supported)
		add_compile_options("/std:c++latest")
	endif()
endif()

include_directories(${CMAKE_SOURCE_DIR})

include(addTaget.cmake)

include(QPlot3D/QPlot3D.cmake)

include(GraphicsViewers/GraphicsViewers.cmake)
include(Geometry/Geometry.cmake)
include(FileWatcher/FileWatcher.cmake)
include(XmlTools/XmlTools.cmake)
include(Data/Data.cmake)
include(TrajectoryViewer/TrajectoryViewer.cmake)
