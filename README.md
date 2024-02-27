# LearningOpenGL
Repository of code I've written while learning **OpenGL** using [this](https://learnopengl.com/) awesome website.


## Prerequisites

* CMake
* OpenGL development libraries
* [vcpkg](https://vcpkg.io/en/getting-started) (for Windows)
* fmt, GLEW, GLFW, GLM (installed on Linux)
* C++ 17+

## Structure
Each project covers different aspect(s) of **OpenGL :**
* Basics
* Lighting
## Build and run
```powershell
cd [project_name]
```
### Windows
```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
```
```powershell
cmake --build build
```

```powershell
.\build\Debug\[project_name].exe
```
---


### Linux

```powershell
cmake -S . -B build
```
```powershell
cmake  --build build
```

```powershell
./build/[project_name]
```


