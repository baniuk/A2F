########################################################################
# CMake build script for LOG_test.	                               #
########################################################################
# Possible targets:
# 	gtest_main gtest	- from gtest
#	doc					- doxygen doc

# Linux
# Dla linuxa wymaga 	python-dev
#			libbz2-dev
# 			gcc 4.4.5 - ma znaczenie dla Panth i boosta

cmake_minimum_required (VERSION 2.8.3) 

# Define helper functions and macros
include(CMake/internal_utils.cmake)

find_all_required_packages()  # Defined in internal_utils.cmake.
config_compiler_and_linker()  # Defined in internal_utils.cmake.

########################################################################
# Setup project                                                        #
########################################################################
include(ExternalProject)
# Project name - nazwa jako zmienna bo u¿ywana tez w doxygenie, ma wp³yw na inne podprojekty
# nie zawsze s¹ one zwi¹zane z ta zmienn¹
set(PROJECT_NAME "Test" CACHE STRING "")
project (${PROJECT_NAME}) 

########################################################################
# Setting tools                                                        #
########################################################################
set_project_tools()	# Defined in internal_utils.cmake.

# TMP dirs
file(MAKE_DIRECTORY CMake_trash)
set(TMP ${Test_SOURCE_DIR}/CMake_trash CACHE PATH "")

# Set default ExternalProject root directory http://stackoverflow.com/questions/9689183/cmake-googletest
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${Test_BINARY_DIR}/Third_Party)

########################################################################
# Building external libraries   (targrt gtest, all)                    #
########################################################################
add_subdirectory(Third_Party)	

########################################################################
# Building Doxygen DOC     (targrt doc, all)                           #
########################################################################
#add_subdirectory(Configs)

########################################################################
# Create warper makefile with external env                             #
########################################################################
IF (${WIN32})
	file(WRITE ${TMP}/make_wrapper_script.bat "rem Warper makefile created autmoatically\n" )
	file(APPEND ${TMP}/make_wrapper_script.bat "set STLSOFT=${External_tools_SOURCE_DIR}/${STL_VER}\n")
ELSEIF (${UNIX})
	file(WRITE ${TMP}/make_wrapper_script.sh "# Warper script created automatically\n")
	file(APPEND ${TMP}/make_wrapper_script.sh "STLSOFT=${External_tools_SOURCE_DIR}/${STL_VER}\n")
	file(APPEND ${TMP}/make_wrapper_script.sh "export STLSOFT\n")
	file(APPEND ${TMP}/make_wrapper_script.sh "echo STLSOFT set\n") 
ELSE (${WIN32})
	message(FATAL_ERROR "Wrong System")
ENDIF(${WIN32})	
