message(STATUS "downloading...
     src='http://downloads.sourceforge.net/project/boost/boost/1.53.0/boost_1_53_0.zip'
     dst='H:/Projekty/A2F/CMake_trash/src/boost_1_53_0.zip'
     timeout='none'")




file(DOWNLOAD
  "http://downloads.sourceforge.net/project/boost/boost/1.53.0/boost_1_53_0.zip"
  "H:/Projekty/A2F/CMake_trash/src/boost_1_53_0.zip"
  SHOW_PROGRESS
  # no EXPECTED_HASH
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://downloads.sourceforge.net/project/boost/boost/1.53.0/boost_1_53_0.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
