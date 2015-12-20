# This file create a dynamic library libDynamicAlgorithms.so of all the dynamic algorithms of Featherstone in C++.

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(KEYWORD DynamicAlgorithms)

# Start a project
PROJECT(${KEYWORD})

# Find YARP.  Point the YARP_DIR environment variable at your build.
#FIND_PACKAGE(YARP)

# Define system type
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        #ADD_DEFINITIONS(-DSYSTEMTYPE_LINUX)
	# Set system folder name
	set(SYSTEM_FOLDER_NAME linux-x86)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	#ADD_DEFINITIONS(-DSYSTEMTYPE_WINDOWS)
	# Set system folder name
	set(SYSTEM_FOLDER_NAME win32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Define standard paths.
set(MY_OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out/${SYSTEM_FOLDER_NAME})
set(MY_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Search for source code.
FILE(GLOB folder_source ${MY_SRC_PATH}/*.cpp)
FILE(GLOB folder_header ${MY_SRC_PATH}/*.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

# Automatically add include directories if needed.
FOREACH(header_file ${folder_header})
  GET_FILENAME_COMPONENT(p ${header_file} PATH)
  INCLUDE_DIRECTORIES(${p})
ENDFOREACH(header_file ${folder_header})

# Set location for binary output
set(LIBRARY_OUTPUT_PATH ${MY_OUT_PATH})

# Set up our main executable.
IF (folder_source)
  ADD_LIBRARY(${KEYWORD} SHARED ${folder_source} ${folder_header})
ELSE (folder_source)
  MESSAGE(FATAL_ERROR "No source code files found. Please add something")
ENDIF (folder_source)

# Link executable to external libraries
#target_link_libraries (${KEYWORD} YARP_OS) # YARP_OSd for debug on win32
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
 #ADD_DEFINITIONS(-DSYSTEMTYPE_LINUX)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
 #target_link_libraries (${KEYWORD} ACE) # ACEd for debug on win32
 #target_link_libraries (${KEYWORD} winmm)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

