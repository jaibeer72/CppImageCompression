cmake_minimum_required(VERSION 3.26)
project(CppImageCompression)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppImageCompression main.cpp
        Arguments.hpp
        ImageData/TgaModule.cpp
        ImageData/TgaModule.hpp
        ImageData/Base/Pixel.hpp
        Utils/MathUtils.hpp
        ImageData/ImageData.cpp
        ImageData/ImageData.hpp
        ImageData/Base/IImageData.hpp
        ImageData/Base/AImageData.hpp
        ImageBlurringAlgos/FastGaussianBlur.cpp
        ImageBlurringAlgos/FastGaussianBlur.hpp
        ImageBlurringAlgos/Base/ImageBlurrer.cpp
        ImageBlurringAlgos/Base/ImageBlurrer.hpp
        ImageBlurringAlgos/Base/ESupportedImageBlurringAlgos.hpp
        ImageBlurringAlgos/NaiveBlur.cpp
        ImageBlurringAlgos/NaiveBlur.hpp
        ImageBlurringAlgos/NaiveBlurThreaded.cpp
        ImageBlurringAlgos/NaiveBlurThreaded.hpp
)
