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
    } else if (tgaImage->header.bitsperpixel == 32)
    {
        if (!tgaImage->ReadPixel32(file, pixeldata))
        {
            std::cerr << "Failed to read 32-bit TGA image." << std::endl;
            return nullptr;
        }
    } else
    {
        std::cerr << "Unsupported TGA format. Only 24-bit and 32-bit TGA files are supported." << std::endl;
        return nullptr;
    }

    tgaImage->SetPixelData(pixeldata);
    file.close();

    return tgaImage;
}

bool TGA::TGAImageData::ReadPixel24into32(std::ifstream &file, std::vector<Pixel32> &imageData)
{
    imageData.resize(header.width * header.height);

    for (size_t i = 0; i < imageData.size(); ++i)
    {
        file.read(reinterpret_cast<char *>(&imageData[i].r), sizeof(imageData[i].r));
        file.read(reinterpret_cast<char *>(&imageData[i].g), sizeof(imageData[i].g));
        file.read(reinterpret_cast<char *>(&imageData[i].b), sizeof(imageData[i].b));
        // Set alpha to 0
        imageData[i].a = 0;
    }

    if (!file.good())
    {
        std::cerr << "Failed to read 24-bit pixel data." << std::endl;
        return false;
    }

    return true;
}

bool TGA::TGAImageData::ReadPixel32(std::ifstream &file, std::vector<Pixel32> &imageData)
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
    this->SetWidth(header.width);
    ReadHeaderField(file, header.height, "height");
    this->SetHeight(header.height);
    ReadHeaderField(file, header.bitsperpixel, "bitsPerpixel");
    this->SetBitsPerPixel(header.bitsperpixel);
    ReadHeaderField(file, header.imagedescriptor, "ImageDescriptor");

    return file.good();
}

void TGA::TGAImageData::WritePixelDataToFile(const std::string &filePath)
{
    if (this->GetPixels().empty())
    {
        std::cerr << "No pixel data to write to file." << std::endl;
        return;
    }

    std::ofstream file(filePath, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }

    if (!this->WriteHeader(file))
    {
        std::cerr << "Failed to write the TGA header." << std::endl;
        return;
    }

    if (this->GetBitsPerPixel() == 24)
    {
        if (!WritePixel32into24File(file, this->GetPixels()))
        {
            std::cerr << "Failed to write 24-bit TGA image." << std::endl;
        }
    } else if (this->GetBitsPerPixel() == 32)
    {
        if (!WritePixel32(file, this->GetPixels()))
        {
            std::cerr << "Failed to write 32-bit TGA image." << std::endl;
        }
    } else
    {
        std::cerr << "Unsupported Write TGA format. Only 24-bit and 32-bit TGA files are supported." << std::endl;
        return;
    }
}

bool TGA::TGAImageData::WriteHeader(std::ofstream &file)
{
    // I might be missing something here but I think this is the best way to do it.
    // is there a rust style match in C++? that will make it so i can
    // do a unionized enum and then match on it.
    // TODO: Find out if there is a rust style match in C++.

    WriteHeaderField(file, header.idlength, "idLength");
    WriteHeaderField(file, header.colourmaptype, "colourMapType");
    WriteHeaderField(file, header.datatypecode, "datatypecode");
    WriteHeaderField(file, header.colourmaporigin, "colourMaporigin");
    WriteHeaderField(file, header.colourmaplength, "colourMapLength");
    WriteHeaderField(file, header.colourmapdepth, "colourDepth");
    WriteHeaderField(file, header.x_origin, "x-orig");
    WriteHeaderField(file, header.y_origin, "y-origin");
    WriteHeaderField(file, header.width, "width");
    WriteHeaderField(file, header.height, "height");
    WriteHeaderField(file, header.bitsperpixel, "bitsPerpixel");
    WriteHeaderField(file, header.imagedescriptor, "ImageDescriptor");

    return file.good();
}

bool TGA::TGAImageData::WritePixel32into24File(std::ofstream &file, const std::vector<Pixel32> &imageData)
{
    for (size_t i = 0; i < imageData.size(); ++i)
    {
        file.write(reinterpret_cast<const char *>(&imageData[i].r), sizeof(imageData[i].r));
        file.write(reinterpret_cast<const char *>(&imageData[i].g), sizeof(imageData[i].g));
        file.write(reinterpret_cast<const char *>(&imageData[i].b), sizeof(imageData[i].b));

        // we are ignoring the alpha channel. writing cause 24 bit does not have that.
    }

    return file.good();
}

bool TGA::TGAImageData::WritePixel32(std::ofstream &file, const std::vector<Pixel32> &imageData)
{
    file.write(reinterpret_cast<const char *>(imageData.data()), imageData.size() * sizeof(Pixel32));
    return file.good();
}

template<typename T>
bool TGA::TGAImageData::WriteHeaderField(std::ofstream &file, T &field, const char *fieldName)
{
    if (!file.write(reinterpret_cast<char *>(&field), sizeof(field)))
    {
        std::cerr << "Failed to write header field: " << fieldName << std::endl;
        return false;
    }
    return true;
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
