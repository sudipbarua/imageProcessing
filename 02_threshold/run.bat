@REM clean and configure
Remove-Item -Recurse -Force build
cmake -S .\src\ -B build 
@REM build
cmake --build .\build\
@REM run
build\Debug\threshold.exe