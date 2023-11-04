//
// Created by Jaibeer Dugal on 03/11/2023.
//

#include "ImageData.hpp"

std::unique_ptr<AImageData> ImageData::Create(const std::string &filePath)
{
    return std::unique_ptr<AImageData>();
}

void ImageData::WriteImage(const std::string &filePath, std::unique_ptr<AImageData> imgData)
{

}
