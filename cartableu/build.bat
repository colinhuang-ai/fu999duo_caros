@echo off
REM Builds build\car_sim.exe. Prefers g++ if it is on PATH, otherwise uses
REM MSVC (needs the Windows SDK installed alongside Visual Studio).
setlocal
cd /d "%~dp0"
if not exist build mkdir build

where g++ >nul 2>nul
if %ERRORLEVEL%==0 (
  g++ -std=c++17 -Wall -Wextra -static -o build\car_sim.exe ^
      src\main.cpp src\core\*.cpp src\services\*.cpp src\screens\*.cpp
  goto :eof
)

set "VCVARS=%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if not "%VSCMD_ARG_TGT_ARCH%"=="" goto :msvc
if not exist "%VCVARS%" (
  echo No g++ on PATH and no vcvars64.bat found.
  exit /b 1
)
call "%VCVARS%" >nul

:msvc
cl /nologo /EHsc /std:c++17 /W4 /Fe:build\car_sim.exe /Fo:build\ ^
   src\main.cpp src\core\*.cpp src\services\*.cpp src\screens\*.cpp
