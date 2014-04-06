rem Static test based on config4cpp
rem Example: Test_Interpreter>StaticTest.cmd ..\..\External_dep\config4cpp\bin ..\..\tools

echo off
setlocal enabledelayedexpansion
rem Expect directory for config4cpp
set C4C_DIR=%1%
set TOOL_DIR=%2%
echo Check for general errors
%C4C_DIR%\config4cpp -cfg A2F.cfg parse 
IF %ERRORLEVEL% NEQ 0 (goto :ERROR) ELSE %TOOL_DIR%\cecho {green} NONE{\n}{default}
echo Print informations
%C4C_DIR%\config4cpp -cfg A2F.cfg print -scope FLUENT -name NUMOFITER 
IF %ERRORLEVEL% NEQ 0 goto :ERROR
echo Scheme Validator
%C4C_DIR%\config4cpp -cfg A2F.cfg validate -scope FLUENT -schemaCfg Schema.cfg -schema A2F.FluentSchema -recursive -types scope_and_vars 
IF %ERRORLEVEL% NEQ 0 (goto :ERROR) ELSE %TOOL_DIR%\cecho {green} NONE{\n}{default}

goto :EOF
:ERROR
%TOOL_DIR%\cecho {red}Error occured{\n}{default}