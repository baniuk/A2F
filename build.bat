rem ***********************************
rem *         A2F build tool          *
rem * Set correct names before use    *
rem * if you need other versions      *
rem * of tools                        *
rem * Prerequirements:                *
rem * 	cmake                         *
rem *	svn                           *
rem * /// \todo Use fork of config4cpp*
rem ***********************************

echo off
setlocal enabledelayedexpansion
rem setting tools to download
set CURRENT_DIR=%CD%
rem set correct names here!!
set PANTH_NAME=pantheios-1.0.1-beta214& rem -src.zip

rem For tools
set PATH=%CURRENT_DIR%\tools;%PATH%
rem For svn and cmake
set PATH=%CURRENT_DIR%\tools\svn-win32-1.8.10\bin;%CURRENT_DIR%\tools\cmake-3.0.2-win32-x86\bin;%PATH%
cecho {red}Configure tool for A2F project{\n}{default}
cecho {green}{\t}USAGE: build - download and compiles all required tools.{\n}{default}
cecho {green}{\t\t}Updates existing instalation{\n}{default}
cecho {green}{\t}USAGE: build ALL cleans everything before download{\n}{default}
cecho {yellow}Downloaded tools:{\n}{default}
cecho {yellow}{\t}%STL_NAME%{\n}{default}
cecho {yellow}{\t}%PANTH_NAME% with patches 32bit{\n}{default}
echo
cecho {red on white}Warning - script downloads latests versions of files{\n}{default}
cecho {red on white}Names of final files must agree in script{\n}{default}
pause
echo off
IF "%1"=="ALL" (goto :CLEAR_ALL) ELSE (goto :SETUP)
:CLEAR_ALL
cecho {red}Cleaning everything...{\n}{default}
rmdir External_dep /s /q
rmdir temp /s /q
:SETUP
cecho {red}Entering setup...{\n}{default}
IF NOT EXIST External_dep mkdir External_dep
IF NOT EXIST temp mkdir temp
rem download stlsoft - always latest version
cd temp
wget -nc http://sourceforge.net/projects/stlsoft/files/latest/download?source=files
IF %ERRORLEVEL% NEQ 0 goto :WGET_ERROR
rem we assume naming pattern: stlsoft* and try to obtain full name of file
rem setting variable as result of operation
dir /B | grep stlsoft > temp.file
set /p STL_NAME_ZIP= < temp.file
unzip -n %STL_NAME_ZIP% -d ..\External_dep
IF %ERRORLEVEL% NEQ 0 goto :ERROR
rem extraction name of directory with stlsoft
dir /AD /B ..\External_dep\ | grep "^stlsoft" > temp.file
set /p STL_NAME= < temp.file
set STLSOFT=%CURRENT_DIR%\External_dep\%STL_NAME%
rem download Pantheios and patches for vc11
wget -nc -O PANTH.diff http://sourceforge.net/p/pantheios/patches/_discuss/thread/832a5759/5540/attachment/pantheios-1_0_1-beta214-MSVC2012-patch.diff
IF %ERRORLEVEL% NEQ 0 goto :WGET_ERROR
wget -nc -O PANTH.zip http://sourceforge.net/p/pantheios/patches/_discuss/thread/832a5759/5a65/attachment/vc11.zip
IF %ERRORLEVEL% NEQ 0 goto :WGET_ERROR
wget -nc http://sourceforge.net/projects/pantheios/files/latest/download?source=files
IF %ERRORLEVEL% NEQ 0 goto :WGET_ERROR
unzip -n %PANTH_NAME%.zip -d ..\External_dep
IF %ERRORLEVEL% NEQ 0 goto :ERROR
rem download config4cpp
wget -nc http://www.config4star.org/download/config4cpp.zip
IF %ERRORLEVEL% NEQ 0 goto :WGET_ERROR
unzip -n config4cpp.zip -d ..\External_dep
IF %ERRORLEVEL% NEQ 0 goto :ERROR
rem patching
cecho {red on white}Applying patches...{default}{\n}
unzip -u -n PANTH.zip -d ..\External_dep\%PANTH_NAME%\build
IF %ERRORLEVEL% NEQ 0 goto :ERROR
patch -p0 -f -d ..\External_dep\%PANTH_NAME% -i ..\..\temp\PANTH.diff
patch -p0 -f -d ..\External_dep\config4cpp\src -i ..\..\..\tools\org.dif
rem Gtest
cecho {red on white}Checkingout gtest...{default}{\n}
svn checkout http://googletest.googlecode.com/svn/trunk/ ..\External_dep\gtest
rem kompilacja
rem Pantheios 32bit
cecho {red on white}Compiling %PANTH_NAME%...{default}{\n}
cd %CURRENT_DIR%\External_dep\%PANTH_NAME%\build\vc11
nmake
rem config4cpp
cecho {red on white}Compiling Config4cpp...{default}{\n}
cd %CURRENT_DIR%\External_dep\config4cpp
nmake -f Makefile.win
rem gtest
cd %CURRENT_DIR%\External_dep\gtest
IF EXIST lib rmdir lib /s /q
mkdir lib
mkdir lib\Release
mkdir lib\Debug
cd lib\Release
rem build /MDd version of libs
cmake -G "NMake Makefiles" -DCMAKE_CXX_FLAGS="-D_VARIADIC_MAX=10" -Dgtest_force_shared_crt=ON -DCMAKE_BUILD_TYPE=Release ..\..\
nmake
cd ..\Debug
cmake -G "NMake Makefiles" -DCMAKE_CXX_FLAGS="-D_VARIADIC_MAX=10" -Dgtest_force_shared_crt=ON -DCMAKE_BUILD_TYPE=Debug ..\..\
nmake
rem cleaning
cecho {red on white}Cleaning...{default}{\n}
cd %CURRENT_DIR%
rmdir temp /s /q
goto :EOF
:ERROR
cecho {red}Error occured{\n}{default}
goto :EOF
:WGET_ERROR
cecho {red}Wget cannot download file{\n}{default}
goto :EOF
:TOOL_ERROR
cecho {red}Cannot find tool{\n}{default}
goto :EOF
