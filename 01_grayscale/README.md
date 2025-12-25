# 01_grayscale

Simple C++ example demonstrating image grayscale conversion using OpenCV.

## What it does
- Loads an example image from `data/`
- Converts the image to grayscale
$$gray = (r \times 0.299) + (g \times 0.587) + (b \times 0.114)$$
- Displays and optionally saves the result
- Uses a small `Timer.h` utility for timing operations

## Files
- src/main.cpp — entry point showing how to read an image, convert to gray and display/save it
- src/Timer.h — lightweight timing helper
- run.bat — helper to run the built binary on Windows (if present)
- data/ — input images used by the example
- build/ — CMake build output (generated)

## Prerequisites
- CMake (>= 3.10)
- A C++ toolchain (Visual Studio on Windows recommended)
- OpenCV (installed and discoverable by CMake)

## Build (Windows / Visual Studio)
1. Open a PowerShell in the example folder:
   ```powershell
   cd d:\projects\imageProcessing\01_grayscale
   mkdir build
   cd build
   cmake ..
   # or specify generator:
   cmake -G "Visual Studio 17 2022" ..
   cmake --build . --config Release
   ```

2. If present, use `run.bat` or run the produced executable from the build output folder. Ensure OpenCV DLLs are next to the exe or on PATH.

## Notes
- Check `src/main.cpp` for the expected input filenames in `data/`.
- To adapt: modify `main.cpp` to load different images or change output behavior.
