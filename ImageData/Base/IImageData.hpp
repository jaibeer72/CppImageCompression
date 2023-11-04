//
// Created by Jaibeer Dugal on 03/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_IIMAGEDATA_HPP
#define CPPIMAGECOMPRESSION_IIMAGEDATA_HPP

#include "Pixel.hpp"

class IImageData
{

public:
    // You never know virtual distructos
    virtual ~IImageData(){}

    // Methods for getting image information
    virtual unsigned int GetWidth() const = 0;

    virtual unsigned int GetHeight() const = 0;

    virtual unsigned int GetBitsPerPixel() const = 0;

    virtual void SetWidth(unsigned int width)  =0;

    virtual void SetHeight(unsigned int height)  =0;

    virtual void SetBitsPerPixel(unsigned int bitsPerPixel)  = 0;

    virtual void SetPixelData(std::vector<Pixel32> pixelData)  = 0;

    virtual

    virtual const std::vector<Pixel32> GetPixels() const = 0;

};

#endif //CPPIMAGECOMPRESSION_IIMAGEDATA_HPP
