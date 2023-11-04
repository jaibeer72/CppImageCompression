//
// Created by Jaibeer Dugal on 03/11/2023.
//

#include "ImageData.hpp"
#include "TgaModule.hpp"

std::unique_ptr<AImageData> ImageData::Create(const std::string &filePath)
{
    // TODO: check file extention before extinding the fucntion.
    return TGA::TGAImageData::CreateTGAImage(filePath);
}

void ImageData::WriteImage(const std::string &filePath, std::unique_ptr<AImageData> imgData)
{
    //TGA::TGAImageData::WriteImage(filePath,imgData);
}
