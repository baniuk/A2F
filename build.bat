echo off
setlocal enabledelayedexpansion
rem setting tools to download
set CURRENT_DIR=%CD%
rem set correct names here!!
set STL_NAME=stlsoft-1.9.117& rem -hdrs.zip
set PANTH_NAME=pantheios-1.0.1-beta214& rem -src.zip
set WX_NAME=wxWidgets-2.9.5& rem .zip

set PATH=%CURRENT_DIR%\tools;%PATH%
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
rem ------------- DOWNLOADING -------------------------------
cecho {red}Entering setup...{\n}{default}
IF NOT EXIST External_dep mkdir External_dep
mkdir temp
cd temp
rem download stlsoft
wget -nc http://sourceforge.net/projects/stlsoft/files/latest/download?source=files
unzip -n %STL_NAME%-hdrs.zip -d ..\External_dep
IF %ERRORLEVEL% NEQ 0 goto :ERROR
set STLSOFT=%CURRENT_DIR%\External_dep\%STL_NAME%
rem download Pantheios and patches for vc11
wget -nc -O PANTH.diff http://sourceforge.net/p/pantheios/patches/_discuss/thread/832a5759/5540/attachment/pantheios-1_0_1-beta214-MSVC2012-patch.diff
wget -nc -O PANTH.zip http://sourceforge.net/p/pantheios/patches/_discuss/thread/832a5759/5a65/attachment/vc11.zip
wget -nc http://sourceforge.net/projects/pantheios/files/latest/download?source=files
unzip -n %PANTH_NAME%.zip -d ..\External_dep
IF %ERRORLEVEL% NEQ 0 goto :ERROR
rem patching
cecho {red on white}Applying patches...{default}{\n}
unzip -u -n PANTH.zip -d ..\External_dep\%PANTH_NAME%\build
IF %ERRORLEVEL% NEQ 0 goto :ERROR
patch -p0 -f -d..\External_dep\%PANTH_NAME% -i ..\..\temp\PANTH.diff
rem Gtest
cecho {red on white}Checkingout gtest...{default}{\n}
svn checkout http://googletest.googlecode.com/svn/trunk/ ..\External_dep\gtest
rem WxWidgets
wget -nc http://sourceforge.net/projects/wxwindows/files/2.9.5/wxWidgets-2.9.5.zip/download
unzip -n %WX_NAME%.zip -d ..\External_dep\%WX_NAME%

rem ------------- COMPILING -------------------------------
rem Pantheios 32bit
cecho {red on white}Compiling %PANTH_NAME%...{default}{\n}
cd ..\External_dep\%PANTH_NAME%\build\vc11
nmake
rem WX 32bit
cecho {red on white}Compiling %WX_NAME%...{default}{\n}
cd %CURRENT_DIR%\External_dep\%WX_NAME%\build\msw
rem ustawienia zgodnie z tabelk¹ wiki.wxwidgets.org/Microsoft_Visual_C%2B%2B_Guide
nmake -f makefile.vc BUILD=release UNICODE=0
nmake -f makefile.vc BUILD=debug UNICODE=0 DEBUG_RUNTIME_LIBS=1
rem cleaning
cecho {red on white}Cleaning...{default}{\n}
cd %CURRENT_DIR%
rmdir temp /s /q
goto :EOF
:ERROR
cecho {blue}Error occured{\n}{default}