cmake_minimum_required (VERSION 2.8)
set(PROJECT_NAME "GeLiSo")
project(${PROJECT_NAME})

###################################################################################################
#											general settings									  #
###################################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-support")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#TODO : a changer !!!
set(CMAKE_CXX_COMPILER "/Users/saschavancauwelaert/gcc_461/bin/g++")
set(CMAKE_C_COMPILER "/Users/saschavancauwelaert/gcc_461/bin/gcc")

if(CMAKE_COMPILER_IS_GNUCXX)
	 message(STATUS "The compiler is GCC")
	else()
	message(FATAL_ERROR "The compiler must be GCC")	
endif()

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)
message(${CMAKE_CXX_COMPILER})
message(${GCC_VERSION})
	
if (GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
        message(STATUS "GCC version >= 4.6")
else()
	message(FATAL_ERROR "GCC version must at least 4.6")	
endif()
	

##########################################################################
# Additional compiler flags
##########################################################################
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++0x" C0X_SUPPORT)
if(C0X_SUPPORT)
  message(STATUS "CXX has c++0x support")
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
else()
	message(${CMAKE_CXX_COMPILER})
	message(${GCC_VERSION})
  message(FATAL_ERROR "c++0x capable compiler is needed to build this project at this time")
endif()


#FindGecode.cmake and FindCPRel.cmake files come from Gustavo Gutierrez
##########################################################################
# Gecode
##########################################################################
find_package(Gecode REQUIRED COMPONENTS kernel support int set driver flatzinc gist minimodel search)
include_directories(GECODE_INCLUDE_DIR)
#get the list of libraries from the global variable initialized in FindGecode.cmake
set(GECODE_LIBS ${GECODE_LIBRARIES})
list(APPEND GECODE_LIBS pthread)
##########################################################################
# CPRel
##########################################################################
find_package(CPRel REQUIRED)
include_directories(CPREL_INCLUDE_DIR)
#get the list of libraries from the global variables initialized in FindCPRel.cmake
set(CPREL_LIBS ${CPREL_LIBRARIES})
list(APPEND CPREL_LIBS ${NEEDED_CPREL_LIBS})
##########################################################################
## Find Boost
##########################################################################
## Find Boost
#include(FindBoost)
#set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.44 REQUIRED System Regex date_time)
message(STATUS "Boost path: ${Boost_INCLUDE_DIRS}")
message(
	STATUS
	"${Boost_LIBRARIES}"
)

link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories(${Boost_INCLUDE_DIRS})


###################################################################################################
#											GeLiSo									 			  #
###################################################################################################

#source files are in the src/ directory (recursively)
file(
	GLOB_RECURSE
	source_files
	src/*
)

#needed libraries to be linked
set (requiredLibs ${GECODE_LIBS})
list(APPEND requiredLibs ${CPREL_LIBS})
list(APPEND requiredLibs ${Boost_LIBRARIES})

message(${requiredLibs})

add_executable(gelisoexec ${source_files})
target_link_libraries(gelisoexec ${requiredLibs})



##########################################################################
