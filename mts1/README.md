Mitsuba Fork for CMake
===================================

Download and unzip dependencies.zip if you need.



===================================

This fork is modified for CMake/Scons compilation, dependencies are updated to lastest(?) version.(Only Windows platform supported)

## Usage

### Environment
Following environment/dependencies are required:
 - Visual Studio
 - [CMake](https://cmake.org/download/)
 - [Qt 5.15](https://www.qt.io/download-qt-installer)
 - [Python 3.9](https://www.python.org/)

Optional:
 - [Scons 4.3.1](https://pypi.org/project/SCons/)(If you are using SCons).

### Dependencies Compilation
Before you start, please notice that:
 - **All commands below are required to execute under VS Command Prompt(x64).**
 - **Please make sure you can download files in cmake.** If you can't, or you don't want to, please refer to the "Dependencies List" section, and download them manually.

1. Modify `dependencies/CMakeLists.txt`
	- Check Line 7. Choose a number <= your CPU cores.
	- Check Line 8 and Line 9 for proxies. If you don't know what it is, or you don't need it, just comment these 2 lines.
2. Dependencies compilation: Go to `dependencies/`, and execute `cmake ./`. (**Too many files, it will take a long time to compile.**)

### Mitsuba Compilation

You can choose compile with CMake or SCons. (CMake is recommended)

#### CMake Compilation
You can compile with CMake GUI or command line.

1. Specify `QT_DIR` and `Python_ROOT_DIR`.
2. Create folder `cbuild`. (Compiling in folder `build` is not recommended, because some scripts are in that folder and you may not want to mess them up.)
3. Config and generate project in GUI. (or go to `cbuild` folder and execute `cmake ..` in command line)
4. Open Visual Studio Solution `Mitsuba.sln`, compile entire solution.
5. You can run/debug mitsuba as normal VS project now.

## Dependencies list

 - If you can't download dependencies in cmake, you can download them manually to `dependencies/Downloads`. After downloading, you can start from Step 1 in "Compilation" section.
 - **All downloaded content are stored in `dependencies/Downloads`**
 - In this table, if "Filename" ends with '/', means this is a folder; otherwise this is a file.

| Library | Filename | Link |
| ------- | -------  | ---- |
| zlib | `zlib/` | `git clone --recurse-submodules https://github.com/madler/zlib.git` |
| OpenEXR | `openexr/` | `git clone --recurse-submodules https://github.com/AcademySoftwareFoundation/openexr.git` |
| libjpeg-turbo | `libjpeg/` | `git clone --recurse-submodules https://github.com/libjpeg-turbo/libjpeg-turbo.git` |
| libpng | `libpng/` | `git clone --recurse-submodules https://github.com/glennrp/libpng.git` |
| boost | `boost/` | `git clone --recurse-submodules --depth=1 --branch=boost-1.77.0 https://github.com/boostorg/boost.git`
| xerces-c | `xerces-c/` | `git clone --recurse-submodules https://github.com/apache/xerces-c.git` |
| glew | `glew-2.2.0-win32.zip` | https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip |
| half | `half-2.2.0.zip` | https://iweb.dl.sourceforge.net/project/half/half/2.2.0/half-2.2.0.zip |
| glext | `glext.h` | https://www.khronos.org/registry/OpenGL/api/GL/glext.h |
| khr | `khrplatform.h` | https://www.khronos.org/registry/EGL/api/KHR/khrplatform.h |
| FFTW | `fftw-3.3.5-dll64.zip` | https://fftw.org/pub/fftw/fftw-3.3.5-dll64.zip |

## Konwn Issues
 - Fail to export hdr images under debug mode. (Works fine in release mode)

---

Feel free to open an issue, I will try to reply asap. (If this fork helps you, please give me a star :smile:)
