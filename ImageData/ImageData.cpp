//
// Created by Jaibeer Dugal on 03/11/2023.
//

#include "ImageData.hpp"
#include "TgaModule.hpp"

std::unique_ptr<AImageData> ImageData::Create(const std::string &filePath)
{
    // check if tga File extention else thorow error
    // I know we are not checking at the end of the file but this is a prototype
    if(filePath.find(".tga") == std::string::npos)
        throw std::runtime_error("File format not supported");

    return TGA::TGAImageData::CreateTGAImage(filePath);
}
