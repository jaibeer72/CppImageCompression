//
// Created by Jaibeer Dugal on 31/10/2023.
//

#include "TgaModule.hpp"

std::unique_ptr<TGAImageData> TGA::TGAImageData::CreateTGAImage(const std::string &filePath)
{
    return std::unique_ptr<TGAImageData>();
}

void TGA::TGAImageData::WriteImage(const std::string &filePath, std::unique_ptr<TGAImageData> imgData)
{

}
