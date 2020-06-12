# Silfur Engine

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Build Status](https://travis-ci.com/Duality-Workshop/Silfur-Engine.svg?branch=develop)](https://travis-ci.com/Duality-Workshop/Silfur-Engine) ![Platform](https://img.shields.io/badge/platform-Win64-lightgrey) ![Organizing with Zenhub](https://img.shields.io/badge/Organizing%20with-ZenHub-5e60ba.svg)

## Description

This game engine will permit to create 3D/2D applications which need rendering or 2D/3D games on Windows 64-bits.

Upon completion, this will be a free, open-source game engine. The source code is under `Apache v2` license.

The game engine is under active development. You can follow the progress of the development with the devlogs on [itch.io.](https://duality-workshop.itch.io/silfur-engine)

## Building Silfur

### On Windows
#### Prerequisites

* Vulkan SDK v1.2.135.0
* CMake 3.17 and up
* GCC 9 and up or Visual Studio 2017 and up

#### Available configurations

* `Debug`
* `Release`
* `RelWithDebInfo`

By default, it's `Debug` configuration. For another configuration, add `-DCMAKE_BUILD_TYPE=<Config>` 
where `<Config>` is equal to `Release` or `RelWithDebInfo`.

#### Building

To build with MSVC:
```bash
git clone --recursive https://github.com/Zethzer/Silfur-Engine.git &&
cd Silfur-Engine && mkdir build && cd build &&
cmake -G "Visual Studio 16 2019" -A x64 .. &&
cmake --build . -j 4
```
To build with GCC:
```bash
git clone --recursive https://github.com/Zethzer/Silfur-Engine.git &&
cd Silfur-Engine && mkdir build && cd build &&
cmake -G "MinGW Makefiles" .. &&
cmake --build . -j 4
```
    
## F.A.Q

* Where can I find the necessary tools and SDK(s)?
  * On Windows:
    * Vulkan SDK v1.2.135.0: [Download](https://vulkan.lunarg.com/sdk/download/1.2.135.0/windows/VulkanSDK-1.2.135.0-Installer.exe?Human=true)
    * CMake 3.17.3: [Download](https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3-win64-x64.msi)
    * MSYS2: [Download](https://github.com/msys2/msys2-installer/releases/download/2020-06-02/msys2-x86_64-20200602.exe)

* CMake can't generate the MinGW Makefiles
  * On Windows:
    * Add the path of the `bin` folder for `mingw64` from `MSYS2` install to your `PATH`:
    ```bash
    <Path-to-MSYS2-Install>\mingw64\bin
    ```

* CMake can't find Vulkan or can't find glslc executable
  * On Windows:
    * The executable of Vulkan SDK add automatically an environment variable named `VULKAN_SDK` that points to the installation path of VulkanSDK. Verify it exist, add it if does not.

* CMake can't generate the MSVC project *(Windows only)*
  * Make sure that Windows 10 SDK (xxx) for Desktop C++ [x86 and x64] component is installed