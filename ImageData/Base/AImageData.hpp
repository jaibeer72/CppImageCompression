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
    std::vector<Pixel32> pixelData;
public:
    ~AImageData() override
    {

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

    const std::vector<Pixel32> GetPixels() const override
    {
        return pixelData;
    }

    // Setters
    void SetWidth(unsigned int Width)  override
    {
        width = Width;
    }

    void SetHeight(unsigned int Height)  override
    {
        height = Height;
    }

    void SetBitsPerPixel(unsigned int BitsPerPixel) override
    {
       bitsPerPixel = BitsPerPixel;
    }

    void SetPixelData(std::vector<Pixel32> Pixeldata) override
    {
        pixelData.clear();
        pixelData.resize(Pixeldata.size());
        pixelData = Pixeldata;
    }

    void WritePixelDataToFile(const std::string &filePath) override
    {
        // something to just make sure people are implementing this.
        throw std::logic_error("WritePixelDataToFile is not implemented in the derived class.");
    }

};

#endif //CPPIMAGECOMPRESSION_AIMAGEDATA_HPP
