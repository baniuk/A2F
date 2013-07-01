########################################################################
# CMake build script for Documentation.								   #
########################################################################
# find_doxygen znajduje tak¿e pakiet dot. Dorobiæ wrucanie scierzki do pliku doxygena
# katalog z wynikowa dokumentacj¹
set(DOC_DIR "${${PROJECT_NAME}_SOURCE_DIR}/doc")
IF ( ${WIN32} )
	#script for windows
	# Kopiuje plik zmieniaj¹c jego nazwê oraz kodowanie oraz wpisuje nazwê projektu
	# Plik Doxygena musi zawierac odwo³anie do makr cmake
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake NEWLINE_STYLE WIN32)
ELSEIF ( ${UNIX})
	# Script for linux
	# Kopiuje plik zmieniaj¹c jego nazwê oraz kodowanie
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake NEWLINE_STYLE UNIX)
ELSE ( ${WIN32} )
	message(FATAL_ERROR "Unknown system")	
ENDIF ( ${WIN32} )	

# automatyczne szukanie pakietu, automatycznie definiownych jest szereg zmienncch zaczynaj¹cych siê od DOXYGEN
IF ( ${DOXYGEN_FOUND} )
	message(STATUS "Doxygen found at " ${DOXYGEN_EXECUTABLE})
	add_custom_target(	doc
						ALL
						${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
						COMMENT "Generating API documentation with Doxygen" VERBATIM
					)	
ELSE ( ${DOXYGEN_FOUND} )
	message(WARNING "Doxygen not found")
ENDIF ( ${DOXYGEN_FOUND} )	


		