//
// Created by Jaibeer Dugal on 31/10/2023.
//

#ifndef CPPIMAGECOMPRESSION_PIXEL_HPP
#define CPPIMAGECOMPRESSION_PIXEL_HPP

#include <iostream>

// TGA pixel is stored in b g r ?
// TODO : maybe we need to redo the structure to do something differently. so it can be used more universially
typedef struct Pixel24{
    uint8_t b, g, r;
};

typedef struct Pixel32{
    uint8_t r, g, b, a;
};


#endif //CPPIMAGECOMPRESSION_PIXEL_HPP
