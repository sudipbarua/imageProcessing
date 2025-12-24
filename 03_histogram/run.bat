@REM clean and configure
Remove-Item -Recurse -Force build

rmdir /s /q build

cmake -S .\src\ -B build 
@REM build
cmake --build .\build\
@REM run
build\Debug\histogram.exe