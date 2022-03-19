# Graphics skeleton

![Release](https://img.shields.io/badge/Release-v1.0-blueviolet)
![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)
![Size](https://img.shields.io/badge/Size-218Mo-f12222)
![Open Source](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)

<br>

This repository is a **skeleton C++ project** containing several graphics libraries : **[GLM](http://glm.g-truc.net/0.9.6/api/index.html)**, **[GLEW](http://glew.sourceforge.net/)**, **[SFML](https://www.sfml-dev.org/)**, **[ImGui](https://github.com/ocornut/imgui)**, **[ImGui-SFML](https://github.com/eliasdaler/imgui-sfml)** and **[Dimension3D](https://github.com/angeluriot/Dimension3D)**. It is perfect for 2D and 3D graphics applications with windows and menus.

<br/>

⚠️ This repository contains **submodules**, add `--recurse-submodules` when cloning ⚠️

<br>

<p align="center">
	<img src="https://i.imgur.com/qzPqvit.png" width="700">
</p>

<br>

# Summary

* **[Summary](#summary)**
* **[Install](#install)**
	* [Windows](#windows)
		* [What you need](#what-you-need)
		* [How to compile it?](#how-to-compile-it)
	* [Unix](#unix)
		* [What you need](#what-you-need-1)
		* [How to compile it?](#how-to-compile-it-1)
	* [Using VS Code](#using-vs-code-recommended) *(recommended)*
		* [What you need](#what-you-need-2)
		* [How to compile it?](#how-to-compile-it-2)
* **[Releases](#releases)**
* **[Credits](#credits)**

<br>

# Install

## Windows

### What you need

* **[CMake](https://cmake.org/)**

* A compiler :

	* **[Visual Studio](https://visualstudio.microsoft.com/)** (the software or the compiler only) *(recommended)*
	* **[MinGW](https://www.mingw-w64.org/)** *(not recommended)*

### How to compile it?

* **Visual Studio** *(recommended)* :

	* Run the **[vs32_launch.bat](https://github.com/angeluriot/Graphics_skeleton/blob/master/vs32_launch.bat)** *(for 32 bits)* or the **[vs64_launch.bat](https://github.com/angeluriot/Graphics_skeleton/blob/master/vs64_launch.bat)** *(for 64 bits)* to create the project
	* Then run the file in **.sln** in the build folder

*(Run the launch file again each time you add or remove a file)*

* **MinGW** *(not recommended)* :

	* Open a terminal in the project root and type : `.\mingw32_launch.bat` *(for 32 bits)* or `.\mingw64_launch.bat` *(for 64 bits)* to create and compile the project
	* Then type : `.\build\App.exe` to run the program *(or something else if you changed the name)*

*(Type the first command when you want to compile and the second when you want to run the program)*

## Unix

### What you need

* **[CMake](https://cmake.org/)**

* **A compiler :**

	* **[GCC](https://gcc.gnu.org/)** for **Linux**
	* **[Clang](https://clang.llvm.org/)** for **MacOS**

* **[GLEW](http://glew.sourceforge.net/)**

The easiest way is to open a terminal and type : `sudo apt update` and `sudo apt upgrade`, then type :

* For **Linux** : `sudo apt install gcc g++ make cmake gdb freeglut3 libglew`
* For **MacOS** : `sudo apt install clang clang++ make cmake lldb freeglut3 libglew`

### How to compile it?

* Open a terminal in the project root and type : `bash unix_launch.sh` to create and compile the project
* Then type : `./build/App` to run the program *(or something else if you changed the name)*

*(Type the first command when you want to compile and the second when you want to run the program)*

## Using VS Code *(recommended)*

### What you need

* The **"What you need"** part of your OS *(above)*
* The **[C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)**

### How to compile it?

* `Ctrl` + `Shift` + `P` and type *"scan for kits"*, then choose you compiler *(I recommend the Visual Studio compiler for Windows)*
* Choose *"debug"* or *"release"* at the bottom
* **Only for Windows :**

	* `Ctrl` + `Shift` + `P`, type *"kits"* and choose *"CMake: Edit User-Local CMake Kits"*, that will open the **cmake-tools-kits.json** file
	* For each configuration, add this at this end *(don't forget the comma on the previous element)* :
		```json
		"cmakeSettings": {
			"X64_BITS": <true or false>
		}
		```
	* Put `true` if the configuration is made for 64 bits and `false` otherwise

* Go to *"Preferences"*, then *"Settings"* and type *"cmake debug"*, then clic on *"Edit in settings.json"* that will open the **settings.json** file
* Add this at this end *(don't forget the comma on the previous element)* :
	```json
	"cmake.debugConfig": {
		"cwd": "${workspaceFolder}"
	}
	```
* If there is a **build** folder, delete it and reload VS Code
* Wait until the **CMakeLists.txt** runs or choose again *"debug"* or *"release"* at the bottom

*(Choose "debug" or "release" again each time you add or remove a file and clic on the play button at the bottom to compile and run the program)*

<br>

# Releases

If you want to test the demo without compiling it, you can see the **[releases](https://github.com/angeluriot/Graphics_skeleton/releases)**.

<br>

# Credits

* **[Angel Uriot](https://github.com/angeluriot) :** Creator of the skeleton project.
