########################################################################
# CMake build script for external tools								   #	
########################################################################
project (External_tools) 

########################################################################
# Pobieranie narzêdzi       										   #	
#	S¹ zapisywane w katalogu TMP projektu                              #
########################################################################
# Wersje narzêdzi i katalogi do jakich siê rozpakuj¹, trzeba URL tez zmieniaæ jak by co
set(PANTHEIOS_VER pantheios-1.0.1-beta214 CACHE STRING "")
set(STL_VER stlsoft-1.9.117 CACHE STRING "")
set(BOOST_VER 1.53.0 )

########################################################################
# Patche dla VS12            										   #	
######################################################################## 
IF (${WIN32})
    MESSAGE(STATUS "Patching sources")
    # nazwy musza byæ nadane tu bo dla takich linków by³y nieprawid³owe
    execute_process(COMMAND ${WGET_EXECUTABLE} -O PANTH.diff http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456644&aid=3587889 WORKING_DIRECTORY ${TMP})
    execute_process(COMMAND ${WGET_EXECUTABLE} -O PANT.zip http://sourceforge.net/tracker/download.php?group_id=141831&atid=750759&file_id=456645&aid=3587889 WORKING_DIRECTORY ${TMP})
ENDIF (${WIN32})    

###############d#########################################################
# Download STL Pantheios       										   #
#  																	   #	
######################################################################## 	
# jak jest ustawiony projekt na œci¹ganie to œci¹g do source dir
ExternalProject_Add(	STLSoft
						PREFIX ${TMP}
						URL http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip
						SOURCE_DIR ${External_tools_SOURCE_DIR}/${STL_VER}
						UPDATE_COMMAND ""
						PATCH_COMMAND ""
						CONFIGURE_COMMAND ""
						BUILD_COMMAND ""
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""						
					)	
					
########################################################################
# Kompilacja Pantheios       										   #
# JEst to pe³en projekt, generuje wszystkie wersje libów			   #	
######################################################################## 	
# W zalezonosci od wersji ró¿ne makefile w projekcie
IF (${WIN32})
	set(SYSTEM_PATH_COMMAND ${PATCH_EXECUTABLE} -p0 -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER} -i ${TMP}/PANTH.diff)
	set(SYSTEM_UPDATE_COMMAND ${ZIP_EXECUTABLE} -u ${TMP}/PANT.zip -d ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}/build)
	IF (${MSVC_VERSION} EQUAL 1600)	# MSVC10
		set(PANTH_MAKEFILE_PATH build/vc10.x64)
	ELSEIF (${MSVC_VERSION} GREATER 1600)	#MSVC11
		set(PANTH_MAKEFILE_PATH build/vc11.x64)
	ELSE (${MSVC_VERSION} EQUAL 1600)
		MESSAGE(FATAL_ERROR "Setup correct makefile for Pantheios for WiN32")
	ENDIF (${MSVC_VERSION} EQUAL 1600)
ELSEIF (${UNIX})
	set(SYSTEM_PATH_COMMAND "")
	set(SYSTEM_UPDATE_COMMAND "")
	IF (${CMAKE_COMPILER_IS_GNUCXX})
		set(PANTH_MAKEFILE_PATH build/gcc44.unix.file64bit)
	ELSE (${CMAKE_COMPILER_IS_GNUCXX})
		MESSAGE(FATAL_ERROR "Setup correct makefile for Pantheios for UNIX")
	ENDIF (${CMAKE_COMPILER_IS_GNUCXX})	
ELSE (${WIN32})
	MESSAGE(FATAL_ERROR "Unknown system")
ENDIF(${WIN32})

# jak jest ustawiony projekt na œci¹ganie to œci¹g do source dir
ExternalProject_Add(	Pantheios
						DEPENDS STLSoft
						PREFIX ${TMP}
						URL http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip
						SOURCE_DIR ${External_tools_SOURCE_DIR}/${PANTHEIOS_VER}
						UPDATE_COMMAND ${SYSTEM_UPDATE_COMMAND}
						PATCH_COMMAND ${SYSTEM_PATH_COMMAND}
						CONFIGURE_COMMAND ""
						BUILD_COMMAND cd ${PANTH_MAKEFILE_PATH} &&  ${CMAKE_BUILD_TOOL}
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""						
					)	
########################################################################
# Kompilacja Gtest          										   #	
######################################################################## 
# Add gtest http://stackoverflow.com/questions/9689183/cmake-googletest
# \todo dodaæ set katalogów jak w przyk³adzie http://www.cmake.org/pipermail/cmake/2012-June/050781.html
# \warning Czy biblioteki te bêda do znalezienia automatycznie??
ExternalProject_Add(	googletest
						# wszystko l¹duje w Third_party/Gtest
						PREFIX ${CMAKE_CURRENT_BINARY_DIR}/GTest
						TMP_DIR ${TMP}
						SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
						TIMEOUT 10
						# SOURCE_DIR ${External_tools_SOURCE_DIR}/GTest-src
						# Force separate output paths for debug and release builds to allow easy
						# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
						CMAKE_ARGS -DCMAKE_CXX_FLAGS='-D_VARIADIC_MAX=10'
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
							-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
							-Dgtest_force_shared_crt=ON
						# BINARY_DIR ${External_tools_SOURCE_DIR}/GTest-bin # bez tej linijki trafia do bin do domyslengo katalogu
						# Disable install step
						INSTALL_COMMAND ""
						# Wrap download, configure and build steps in a script to log output
						# LOG_DOWNLOAD ON
					)

########################################################################
# Kompilacja BOOST          										   #	
######################################################################## 	
# http://www.boost.org/doc/libs/1_53_0/more/getting_started/windows.html#test-your-program
# linkowanie dynamiczne tylko w windows

# ustawiæ scie¿ki do bibliotek bo ró¿ni¹ siê w zaleznoœci od systemu
IF (${WIN32})
	set(BOOST_BOOTSTRAP bootstrap.bat)
	set(BOOST_BUILD_CMD b2)
	IF (${MSVC_VERSION} EQUAL 1600)	# MSVC10
		set(BOOST_TOOLSET msvc-10.0)
	ELSEIF (${MSVC_VERSION} GREATER 1600)	#MSVC11
		set(BOOST_TOOLSET msvc-11.0)
	ELSE (${MSVC_VERSION} EQUAL 1600)
		MESSAGE(FATAL_ERROR "Setup correct makefile for BOOST for WiN32")
	ENDIF (${MSVC_VERSION} EQUAL 1600)
ELSEIF (${UNIX})	
	set(BOOST_BUILD_CMD ./b2)
	set(BOOST_BOOTSTRAP ./bootstrap.sh)
	IF (${CMAKE_COMPILER_IS_GNUCXX})
		set(BOOST_TOOLSET gcc-4.4.5)
	ELSE (${CMAKE_COMPILER_IS_GNUCXX})
		MESSAGE(FATAL_ERROR "Setup correct makefile for BOOST for UNIX")
	ENDIF (${CMAKE_COMPILER_IS_GNUCXX})	
ELSE (${WIN32})
	MESSAGE(FATAL_ERROR "Wrong system")
ENDIF(${WIN32})
			
string( REPLACE "." "_" Boost_Version_Underscore ${BOOST_VER} )
message( STATUS "Boost_Version: " ${BOOST_VER} )
ExternalProject_Add( 	Boost
						PREFIX ${TMP}
						SOURCE_DIR ${External_tools_SOURCE_DIR}/boost
						URL http://downloads.sourceforge.net/project/boost/boost/${BOOST_VER}/boost_${Boost_Version_Underscore}.zip
						UPDATE_COMMAND ${BOOST_BOOTSTRAP}
						CONFIGURE_COMMAND ""
						# te parametr ymaj¹ wp³yw na poni¿sze œcie¿ki i nazwy bibliotek
						BUILD_COMMAND ${BOOST_BUILD_CMD} -j4 address-model=64 toolset=${BOOST_TOOLSET} link=static stage
						BUILD_IN_SOURCE 1
						INSTALL_COMMAND ""
					)
#set_property( TARGET Boost PROPERTY FOLDER "Externals")
# Ustawia¿ w funkcjach buduj¿cych
#ExternalProject_Get_Property( Boost source_dir )
#ExternalProject_Get_Property( Boost binary_dir )
#set( Boost_INCLUDE_DIRS ${source_dir} )
#set( Boost_LIBRARIES ${binary_dir}/stage)		
#MESSAGE(STATUS "^^^^^BOOST_INCLUDE_DIRS set to ${Boost_INCLUDE_DIRS}")	
#MESSAGE(STATUS "^^^^^BOOST_LIBS_DIRS set to ${Boost_LIBRARIES}")			
