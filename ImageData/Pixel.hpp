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
    unsigned char r, g, b, a;
};


#endif //CPPIMAGECOMPRESSION_PIXEL_HPP
