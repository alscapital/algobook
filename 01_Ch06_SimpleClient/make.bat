set PROJ=SimpleClient

set CC=g++

set CFLAGS=--std=c++11 -Wno-return-type

:: -std=c++11 -Wno-return-type
:: -D _WIN64 -march=x86-64 -O0 -static -s -std=gnu++20

::users links
set TWS_DIR="C:\TWS API\source\CppClient\client"
set LIB_DIR="C:\TWS API\source\CppClient\client\lib"

:: Directory containing source files
set SRC_DIR=%TWS_DIR%

:: Directory containing header files
set INC_DIR=%TWS_DIR%

%CC% Main.cpp %PROJ%.cpp %SRC_DIR%\*.cpp %LIB_DIR%\libbid.lib %CFLAGS% -o%PROJ%.exe -I%INC_DIR% -lpthread -L%LIB_DIR%