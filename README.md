# 2D TopDown Shooter
It is a 2d shooting game made with C++ and [SDL2](https://www.libsdl.org/)

## Compiling

Project depends on `SDL2` libs.

### On Windows

Download and unpack devel packages for [SDL2](https://www.libsdl.org/download-2.0.php) and [SDL2_image](https://www.libsdl.org/projects/SDL_image/).\
Set paths to them in `CMakeLists.txt`, see suggested placement in `/external`.\
If you are using MSVC then use the following commands in project directory to compile the code with CMake..
```
mkdir build

cd build

cmake ..

cmake --build .
```
The compiled `.exe` is located in `./build/Debug/`

### On Linux

Install devel packages for `SDL2`, `SDL2_image`.\
Compile with CMake