# Silfur Engine

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Build status](https://ci.appveyor.com/api/projects/status/myw2msr47c1vs109?svg=true)](https://ci.appveyor.com/project/Zethzer/silfur-engine) ![Platform](https://img.shields.io/badge/platform-Win64-lightgrey) ![Organizing with Zenhub](https://img.shields.io/badge/Organizing%20with-ZenHub-5e60ba.svg)

## Description

This game engine will permit to create 3D/2D applications which need rendering or 2D/3D games on Windows 64-bits.

Upon completion, this will be a free, open-source game engine. The source code is available on Github.

The game engine is under active development. You can follow the progress of the development with the devlogs on [itch.io.](https://duality-workshop.itch.io/silfur-engine)

## Prerequisites

* Install Vulkan SDK (v1.2.131.2) before compiling the project : [Download](https://vulkan.lunarg.com/sdk/download/1.2.131.2/windows/VulkanSDK-1.2.131.2-Installer.exe?Human=true)
  * Tested only on Windows.

## Compile the project

* On Windows:
  * `git clone --recursive https://github.com/Zethzer/Silfur-Engine.git`
  * Launch `scripts\Win-GenProjects.bat` for generate the `.sln` file