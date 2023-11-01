//
// Created by Jaibeer Dugal on 31/10/2023.
//

#ifndef CPPIMAGECOMPRESSION_IIMAGELOADER_HPP
#define CPPIMAGECOMPRESSION_IIMAGELOADER_HPP

#include <string>

class IImageLoader
{
public:
    virtual void ReadFile(std::string source) = 0;

    virtual void WriteFile(std::string dest) = 0;
};

#endif //CPPIMAGECOMPRESSION_IIMAGELOADER_HPP
