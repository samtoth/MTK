# MTK (Music ToolKit)
A C++ API designed for Music software

![MTK Version](https://img.shields.io/github/v/tag/samtoth/MTK?label=Version)
![Build](https://github.com/samtoth/MTK/workflows/Build/badge.svg?branch=Development)
[![codecov](https://codecov.io/gh/samtoth/MTK/branch/Development/graph/badge.svg)](https://codecov.io/gh/samtoth/MTK)
[![CodeFactor](https://www.codefactor.io/repository/github/samtoth/mtk/badge)](https://www.codefactor.io/repository/github/samtoth/mtk)

This project is a work in progress, many features are not implemented and API likely to change. 

## Contents
* [Goals](#goals)
* [Current features](#current-features)
* [Building from source](#building-from-source)
* [License](#license)
 

## Goals
###### Highest priority first
* Define an API flexible enough to deal with music outside of Western traditions
* Interface with existing standards: 
    * Midi
    * MusicXML
* A python wrapper to access through scripting language
* Basic synthesis capabilities
* Notation rendering 
 
## Current features
* Reading, writing and primitive play back of  [MuDa files](https://samtoth.github.io/MTK/MuDaSpec.xhtml)
* See the state of the current API in [the docs](https://samtoth.github.io/MTK/classes.xhtml)
 
## Building from source
#### Dependencies
* [CMake](https://gitlab.kitware.com/cmake/cmake) - minimum version tested on version 3.16
* A C++11-standard-compliant compiler
    * (Only currently tested with MinGW on Windows and gcc on Linux)
###### Optional
* Doxygen (with option -DBUILD_DOCS=ON)
  
### Run:
```
git clone https://github.com/qoolander/MTK.git
cd MTK
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_TESTS=OFF -DBUILD_DOCS=OFF ..
cmake --build . --target all -- -j 4
```
##### Note
If using windows replace
```cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_TESTS=OFF -DBUILD_DOCS=OFF ..``` with ```cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_TESTS=OFF -DBUILD_DOCS=OFF -G "MinGW Makefiles" ..```
 
## Getting started
 
First make sure you have successfully [built MTK](#building-from-source). 

To play an example file, first confirm audio output is working by navigating to the {build_directory}/bin, and from the command line running `./testBeep(.exe)`.
If you hear a tone that lasts a few second before stopping then everything appears to be working!

To play a .MuDa file run `./MuDaCLI(.exe) -p <filename.MuDa>`. To begin with we can have the program generate an example file for us by running the command `./MuDaCLI(.exe) -e example.MuDa`. Finally run `./MuDaCLI(.exe) -p example.MuDa` to hear the result.
 
## Built using
* [gtest](https://github.com/google/googletest)
* [Doxygen](https://github.com/doxygen/doxygen)
* [Eigen3](https://gitlab.com/libeigen/eigen)
* [PortAudio](http://portaudio.com/docs/v19-doxydocs/index.html)

## License
Developed under GNU General Public License Version 3. [See full LICENSE](LICENSE) 
 
