cmake_minimum_required(VERSION 3.26)
project(CppImageCompression)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppImageCompression main.cpp
        Arguments.hpp
        ImageModules/TgaModule.cpp
        ImageModules/TgaModule.hpp
        ImageModules/Pixel.hpp
        ImageModules/IImageLoader.hpp)
