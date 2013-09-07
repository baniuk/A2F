message(STATUS "downloading...
     src='http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip'
     dst='H:/Projekty/A2F/CMake_trash/src/stlsoft-1.9.117-hdrs.zip'
     timeout='none'")




file(DOWNLOAD
  "http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip"
  "H:/Projekty/A2F/CMake_trash/src/stlsoft-1.9.117-hdrs.zip"
  SHOW_PROGRESS
  # no EXPECTED_HASH
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://sourceforge.net/projects/stlsoft/files/STLSoft%201.9/1.9.117/stlsoft-1.9.117-hdrs.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
