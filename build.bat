rem temporary script for testing cmake
rem option ALL cleans everything
call tools\clean.bat %1
rem out-of-source build
mkdir bin
cd bin
cmake -G "NMake Makefiles" --graphviz=..\CMake_trash\ARCH.dot ..\
rem calls warper script - correct env must be set http://www.mail-archive.com/cmake@cmake.org/msg38597.html
call ..\CMake_trash\make_wrapper_script.bat
nmake
ctest --verbose
cd ..
