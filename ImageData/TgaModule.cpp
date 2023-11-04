//
// Created by Jaibeer Dugal on 31/10/2023.
//

#include "TgaModule.hpp"
#include <fstream>

std::unique_ptr<TGA::TGAImageData> TGA::TGAImageData::CreateTGAImage(const std::string &filePath)
{
    std::unique_ptr<TGAImageData> tgaImage = std::make_unique<TGAImageData>();
    std::vector<Pixel32> pixeldata;

    std::ifstream file(filePath, std::ios::binary | std::ios_base::in);
    if (!file.is_open())
    {
        std::cerr << "\nFailed to open the TGA file." << std::endl;
        return nullptr;
    }

    if (!tgaImage->ReadHeader(file))
    {
        std::cerr << "Failed to read the TGA header." << std::endl;
        return nullptr;
    }

    if (tgaImage->header.bitsperpixel == 24)
    {
        if (!tgaImage->ReadPixel24into32(file, pixeldata))
        {
            std::cerr << "Failed to read 24-bit TGA image." << std::endl;
            return nullptr;
        }
    }
    else if (tgaImage->header.bitsperpixel == 32)
    {
        if (!tgaImage->ReadPixel32(file , pixeldata))
        {
            std::cerr << "Failed to read 32-bit TGA image." << std::endl;
            return nullptr;
        }
    }
    else
    {
        std::cerr << "Unsupported TGA format. Only 24-bit and 32-bit TGA files are supported." << std::endl;
        return nullptr;
    }
    tgaImage->SetPixelData(pixeldata);

    file.close();

    return tgaImage;
}

void TGA::TGAImageData::WriteImage(const std::string &filePath, std::unique_ptr<TGA::TGAImageData> imgData)
{

}

bool TGA::TGAImageData::ReadPixel24into32(std::ifstream &file, std::vector<Pixel32> &imageData)
{
    imageData.resize(header.width * header.height);

    for (size_t i = 0; i < imageData.size(); ++i) {
        file.read(reinterpret_cast<char *>(&imageData[i].r), sizeof(imageData[i].r));
        file.read(reinterpret_cast<char *>(&imageData[i].g), sizeof(imageData[i].g));
        file.read(reinterpret_cast<char *>(&imageData[i].b), sizeof(imageData[i].b));
        // Set alpha to 0
        imageData[i].a = 0;
    }

    if (!file.good()) {
        std::cerr << "Failed to read 24-bit pixel data." << std::endl;
        return false;
    }

    return true;
}

bool TGA::TGAImageData::ReadPixel32(std::ifstream &file , std::vector<Pixel32> &imageData)
{
    // I know resize and reserve in Unreal has been a source of issues
    // but ! it works
    // Ref : https://www.youtube.com/watch?v=algDLvbl1YY
    // vid 3:00 add point to spline.
    imageData.resize(header.width * header.height);
    file.read(reinterpret_cast<char *>(imageData.data()), imageData.size() * sizeof(Pixel32));

    return file.good();
}

bool TGA::TGAImageData::ReadHeader(std::ifstream &file)
{
    ReadHeaderField(file, header.idlength, "idLength");
    ReadHeaderField(file, header.colourmaptype, "colourMapType");
    ReadHeaderField(file, header.datatypecode, "datatypecode");
    ReadHeaderField(file, header.colourmaporigin, "colourMaporigin");
    ReadHeaderField(file, header.colourmaplength, "colourMapLength");
    ReadHeaderField(file, header.colourmapdepth, "colourDepth");
    ReadHeaderField(file, header.x_origin, "x-orig");
    ReadHeaderField(file, header.y_origin, "y-origin");
    ReadHeaderField(file, header.width, "width");
    ReadHeaderField(file, header.height, "height");
    ReadHeaderField(file, header.bitsperpixel, "bitsPerpixel");
    ReadHeaderField(file, header.imagedescriptor, "ImageDescriptor");

    return file.good();
}


template<typename T>
bool TGA::TGAImageData::ReadHeaderField(std::ifstream &file, T &field, const char *fieldName)
{
    if (!file.read(reinterpret_cast<char *>(&field), sizeof(field)))
    {
        std::cerr << "Failed to read header field: " << fieldName << std::endl;
        return false;
    }
    return true;
}
