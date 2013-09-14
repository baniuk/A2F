/**
 * \file    DOC_MainPage.h
 * \brief   Main page of Doxygen documentation
 * \details This file contains main page for doc and some todos
 * \author  PB
 * \date    2013/09/13
 * \version 0.5
 */
/** \mainpage A2F port
*
* \section Installation
* -# Run build.bat on setup. It downloads and compiles all required tools. GTest is only downloaded but not compiled.
* \section structure Project structure
* -# More information are on trac.
* \section Pantheios
* -# All pantheios settings are in Panheios_header.h file. there is also name and path to the log file.
* \section General
* Po wstawieniu PMC do PME wywo�ywana jest funkcja CUnitOperations::FinalConstruct(). W tej funkcji tworzone jest API Pantheios'a kt�re z kolei jest 
* zamykane w funkcji CUnitOperations::FinalRelease(). Po wstawieniu PMC metody s� wywo�ywane przez PME w kolejno�ci:
* -# CUnitOperations::FinalConstruct()
* -# CUnitOperations::Initialize()
* -# CUnitOperations::get_ports( LPDISPATCH * ports )
* -# CUnitOperations::FinalRelease()\n
* 
* Wynika z tego �e za ka�dym razem jak PME co� chce od PMC to wywo�uje ta procedur� od pocz�tku.
*/
