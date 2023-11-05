//
// Created by Jaibeer Dugal on 31/10/2023.
//

#ifndef CPPIMAGECOMPRESSION_PIXEL_HPP
#define CPPIMAGECOMPRESSION_PIXEL_HPP

#include <iostream>

// TGA pixel is stored in b g r
// https://stackoverflow.com/questions/75191/what-is-an-unsigned-char
struct Pixel24
{
    unsigned char r, g, b;
};

struct Pixel32
{
    uint8_t r, g, b, a;
};

static inline void ClampPixelValues(Pixel32& pixel)
{
    if(pixel.r > 255)
    {
        std::cerr<<"Pixel value is greater than 255\n";
        pixel.r = 255;
    }
    if(pixel.g > 255)
    {
        std::cerr<<"Pixel value is greater than 255\n";
        pixel.g = 255;
    }
    if(pixel.b > 255)
    {
        std::cerr<<"Pixel value is greater than 255\n";
        pixel.b = 255;
    }
    if(pixel.a > 255)
    {
        std::cerr<<"Pixel value is greater than 255\n";
        pixel.a = 255;
    }
    // now for below 0
    if(pixel.r < 0)
    {
        std::cerr<<"Pixel value is Less than 0\n";
        pixel.r = 0;
    }
    if(pixel.g < 0)
    {
        std::cerr<<"Pixel value is Less than 0\n";
        pixel.g = 0;
    }
    if(pixel.b < 0)
    {
        std::cerr<<"Pixel value is Less than 0\n";
        pixel.b = 0;
    }
    if(pixel.a < 0)
    {
        std::cerr<<"Pixel value is Less than 0\n";
        pixel.a = 0;
    }
}

// Add two Pixel32 values component-wise
static inline Pixel32 operator+(const Pixel32& lhs, const Pixel32& rhs)
{
    Pixel32 result;
    result.r = lhs.r + rhs.r;
    result.g = lhs.g + rhs.g;
    result.b = lhs.b + rhs.b;
    result.a = lhs.a + rhs.a;
    ClampPixelValues(result);
    return result;
}

// Subtract two Pixel32 values component-wise
static inline Pixel32 operator-(const Pixel32& lhs, const Pixel32& rhs)
{
    Pixel32 result;
    result.r = lhs.r - rhs.r;
    result.g = lhs.g - rhs.g;
    result.b = lhs.b - rhs.b;
    result.a = lhs.a - rhs.a;
    ClampPixelValues(result);
    return result;
}

static inline Pixel32 operator*(const Pixel32& lhs, const int& rhs)
{
    Pixel32 result;
    result.r = lhs.r * rhs;
    result.g = lhs.g * rhs;
    result.b = lhs.b * rhs;
    result.a = lhs.a * rhs;
    ClampPixelValues(result);
    return result;
}

#endif //CPPIMAGECOMPRESSION_PIXEL_HPP
