//
// Created by Jaibeer Dugal on 03/11/2023.
//
// Writing all in one for now this is an Abstract class
#ifndef CPPIMAGECOMPRESSION_IMAGEDATA_HPP
#define CPPIMAGECOMPRESSION_IMAGEDATA_HPP

#include <memory>

// Forward declaration to tell the compiler we good
class AImageData;

class ImageData
{
public:
    // Factory method to create ImageData instances based on file format
    static std::unique_ptr <AImageData> Create(const std::string &filePath);
};


#endif //CPPIMAGECOMPRESSION_IMAGEDATA_HPP
