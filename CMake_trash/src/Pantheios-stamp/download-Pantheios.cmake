message(STATUS "downloading...
     src='http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip'
     dst='H:/Projekty/A2F/CMake_trash/src/pantheios-1.0.1-beta214-src.zip'
     timeout='none'")




file(DOWNLOAD
  "http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip"
  "H:/Projekty/A2F/CMake_trash/src/pantheios-1.0.1-beta214-src.zip"
  SHOW_PROGRESS
  # no EXPECTED_HASH
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'http://sourceforge.net/projects/pantheios/files/Pantheios%20%28C%20and%20Cxx%29/1.0.1%20%28beta%20214%29/pantheios-1.0.1-beta214-src.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
