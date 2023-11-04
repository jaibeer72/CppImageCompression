//
// Created by Jaibeer Dugal on 03/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_IIMAGEDATA_HPP
#define CPPIMAGECOMPRESSION_IIMAGEDATA_HPP

class IImageData
{
protected:
    int width;
    int height;
    int bitsPerPixel;
public:
    // You never know virtual distructos
    virtual ~IImageData(){}

    // Methods for getting image information
    virtual unsigned int GetWidth() const = 0;

    virtual unsigned int GetHeight() const = 0;

    virtual unsigned int GetBitsPerPixel() const = 0;

    virtual void SetWidth(unsigned int width) const =0;

    virtual void SetHeight(unsigned int height) const =0;

    virtual void SetBitsPerPixel(unsigned int bitsPerPixel) const = 0;

    virtual void SetPixelData(void *pixelData) const = 0;

    // Cause i want to support different pixel types i am using a void*
    virtual const void* GetPixels() const = 0;

};

#endif //CPPIMAGECOMPRESSION_IIMAGEDATA_HPP
