@REM clean and configure
Remove-Item -Recurse -Force build
cmake -S . -B build 
@REM build
cmake --build .\build\
@REM run
D:\projects\imageProcessing\01_grayscale\build\src\Debug\grayscale.exe