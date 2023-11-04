//
// Created by Jaibeer Dugal on 04/11/2023.
//
// Currently a Header only file
// This is assuming most files will have a similar implementation of things.
// but this is ovveridable.

#ifndef CPPIMAGECOMPRESSION_AIMAGEDATA_HPP
#define CPPIMAGECOMPRESSION_AIMAGEDATA_HPP
#include "IImageData.hpp"
#include <iostream>
#include <memory>

class AImageData : public IImageData
{
private:
    unsigned int width;
    unsigned int height;
    unsigned int bitsPerPixel;
    // TODO: see if this works properly
    void* pixelData;
public:
    ~AImageData() override
    {
        // Free Pixel data here later
        free(pixelData);
    }

    unsigned int GetWidth() const override
    {
        return width;
    }

    unsigned int GetHeight() const override
    {
        return height;
    }

    unsigned int GetBitsPerPixel() const override
    {
        return bitsPerPixel;
    }

    const void *GetPixels() const override
    {
        return pixelData;
    }

    // Setters
    void SetWidth(unsigned int width) const override
    {
        width = width;
    }

    void SetHeight(unsigned int height) const override
    {
        height = height;
    }

    void SetBitsPerPixel(unsigned int bitsPerPixel) const override
    {
       bitsPerPixel = bitsPerPixel;
    }

    void SetPixelData(void *pixelData) const override
    {
        pixelData = pixelData;
    }

};

#endif //CPPIMAGECOMPRESSION_AIMAGEDATA_HPP
