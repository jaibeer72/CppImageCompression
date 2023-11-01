#include "Arguments.hpp"
#include "ImageModules/TgaModule.hpp"
#include "ImageModules/Pixel.hpp"
#include <fstream>

int main(int argc , char* argv[]) {

    Args* appArgs = new Args(argc,argv);
    std::cout<< (appArgs->getIsRunnableConfig() ? "this is a runnable config" : "this is not a runnable config");

    std::ifstream file(appArgs->getSource().c_str(), std::ios::binary | std::ios_base::in);
    if (!file.is_open()) {
        std::cerr << "\nFailed to open the TGA file." << std::endl;
        return 1;
    }

    TGA::Header header;
    file.read(reinterpret_cast<char*>(&header.idlength), sizeof(header.idlength));
    file.read(reinterpret_cast<char*>(&header.colourmaptype), sizeof(header.colourmaptype));
    file.read(reinterpret_cast<char*>(&header.datatypecode), sizeof(header.datatypecode));
    file.read(reinterpret_cast<char*>(&header.colourmaporigin), sizeof(header.colourmaporigin));
    file.read(reinterpret_cast<char*>(&header.colourmaplength), sizeof(header.colourmaplength));
    file.read(reinterpret_cast<char*>(&header.colourmapdepth), sizeof(header.colourmapdepth));
    file.read(reinterpret_cast<char*>(&header.x_origin), sizeof(header.x_origin));
    file.read(reinterpret_cast<char*>(&header.y_origin), sizeof(header.y_origin));
    file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.read(reinterpret_cast<char*>(&header.bitsperpixel), sizeof(header.bitsperpixel));
    file.read(reinterpret_cast<char*>(&header.imagedescriptor), sizeof(header.imagedescriptor));

    if (!file) {
        std::cerr << "Failed to read the TGA header." << std::endl;
        return 1;
    }


//    if (header.bitsperpixel == 24) {
//        // Read 24-bit TGA image using Pixel24
//        std::vector<Pixel24> imageData(header.width * header.height);
//        file.read(reinterpret_cast<char*>(imageData.data()), imageData.size() * sizeof(Pixel24));
//        std::cout<<imageData.size();
//
//        // Process the imageData as Pixel24
//    } else if (header.bitsperpixel == 32) {
//        // Read 32-bit TGA image using Pixel32
//        std::vector<Pixel32> imageData(header.width * header.height);
//        file.read(reinterpret_cast<char*>(imageData.data()), imageData.size() * sizeof(Pixel32));
//
//        // Process the imageData as Pixel32
//    } else {
//        std::cerr << "Unsupported TGA format. Only 24-bit and 32-bit TGA files are supported." << std::endl;
//        return {};
//    }

    // Read the input image data
    std::vector<Pixel24> imageData(header.width * header.height);
    file.read(reinterpret_cast<char*>(imageData.data()), imageData.size() * sizeof(Pixel24));

    file.close();

    // Create an output TGA file with all red pixels
    std::ofstream outputFile(appArgs->getDestination().c_str(), std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "\nFailed to create the output TGA file." << std::endl;
        return 1;
    }

    // Write the header to the output file
    outputFile.write(reinterpret_cast<char*>(&header.idlength), sizeof(header.idlength));
    outputFile.write(reinterpret_cast<char*>(&header.colourmaptype), sizeof(header.colourmaptype));
    outputFile.write(reinterpret_cast<char*>(&header.datatypecode), sizeof(header.datatypecode));
    outputFile.write(reinterpret_cast<char*>(&header.colourmaporigin), sizeof(header.colourmaporigin));
    outputFile.write(reinterpret_cast<char*>(&header.colourmaplength), sizeof(header.colourmaplength));
    outputFile.write(reinterpret_cast<char*>(&header.colourmapdepth), sizeof(header.colourmapdepth));
    outputFile.write(reinterpret_cast<char*>(&header.x_origin), sizeof(header.x_origin));
    outputFile.write(reinterpret_cast<char*>(&header.y_origin), sizeof(header.y_origin));
    outputFile.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    outputFile.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    outputFile.write(reinterpret_cast<char*>(&header.bitsperpixel), sizeof(header.bitsperpixel));
    outputFile.write(reinterpret_cast<char*>(&header.imagedescriptor), sizeof(header.imagedescriptor));

    // Write the image data with all red pixels to the output file
    outputFile.write(reinterpret_cast<char*>(imageData.data()), imageData.size() * sizeof(Pixel24));

    outputFile.close();


    return 0;
}
