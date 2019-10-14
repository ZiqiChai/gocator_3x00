CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(gocator_3x00)
message(STATUS "Executig CMakeLists of project  ${PROJECT_NAME}.")

#SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# Cmake policy
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0005 NEW) 
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#Set Flags
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -D_REENTRANT")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_REENTRANT")

#Set compiler according C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++11 support.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++0x support.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()



# OpenCV
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
FIND_PACKAGE( OpenCV 2.4.8 REQUIRED )
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenCV_LIBRARY_DIRS})
ADD_DEFINITIONS(${OpenCV_DEFINITIONS})

# PCL
FIND_PACKAGE(PCL REQUIRED COMPONENTS)
INCLUDE_DIRECTORIES(${PCL_INCLUDE_DIRS})
LINK_DIRECTORIES(${PCL_LIBRARY_DIRS})
ADD_DEFINITIONS(${PCL_DEFINITIONS})

# GoSDK and KAPI
# Set GO_SDK header files (That is different names for Sdk5.x )
SET(GO_SDK_4 ~/GO_SDK)
FIND_PATH(
    GOCATOR_INCLUDES
    NAMES GoSdk/GoSdk.h
    PATHS ${GO_SDK_4}/Gocator/GoSdk)
FIND_PATH(
    KAPI_INCLUDES
    NAMES kApi/kApi.h
    PATHS ${GO_SDK_4}/Platform/kApi)
INCLUDE_DIRECTORIES(${GOCATOR_INCLUDES} ${KAPI_INCLUDES})

# Set GO_SDK libs (That is different names for Sdk5.x )
FIND_LIBRARY(
    GOCATOR_LIBRARIES
    NAMES GoSdk
    PATHS ${GO_SDK_4}/lib/linux_x64d/) 
FIND_LIBRARY(
    KAPI_LIBRARIES
    NAMES kApi
    PATHS ${GO_SDK_4}/lib/linux_x64d/)

message(STATUS "Gocator Headers   found at ${GOCATOR_INCLUDES}.")
message(STATUS "Gocator Libraries found at ${GOCATOR_LIBRARIES}.")

# Build library
# Set source files
SET(SRCS src/gocator3100.cpp)
# Set header files 
SET(HDRS src/gocator3100.h)
# Add library
ADD_LIBRARY(${PROJECT_NAME}_LIB SHARED ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_LIB ${GOCATOR_LIBRARIES} ${KAPI_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS})

#Build examples 
ADD_SUBDIRECTORY(src/examples)
