#include "Arguments.hpp"
#include "ImageModules/TgaModule.hpp"
#include "ImageModules/Pixel.hpp"
#include <fstream>

void NaiveBlur(std::vector<Pixel24>& image, int width, int height, int kernelSize) {
    std::vector<Pixel24> originalImage = image; // Create a copy of the original image

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int pixelCount = 0;

            for (int j = -kernelSize; j <= kernelSize; j++) {
                for (int i = -kernelSize; i <= kernelSize; i++) {
                    int newX = x + i;
                    int newY = y + j;

                    // Apply mirror boundary conditions for out-of-bounds pixels
                    if (newX < 0) {
                        newX = -newX;  // Mirror the x-coordinate
                    } else if (newX >= width) {
                        newX = 2 * width - newX - 1;  // Mirror the x-coordinate
                    }

                    if (newY < 0) {
                        newY = -newY;  // Mirror the y-coordinate
                    } else if (newY >= height) {
                        newY = 2 * height - newY - 1;  // Mirror the y-coordinate
                    }

                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                        totalRed += originalImage[newY * width + newX].r;
                        totalGreen += originalImage[newY * width + newX].g;
                        totalBlue += originalImage[newY * width + newX].b;
                        pixelCount++;
                    }
                }
            }

            image[y * width + x].r = totalRed / pixelCount;
            image[y * width + x].g = totalGreen / pixelCount;
            image[y * width + x].b = totalBlue / pixelCount;
        }
    }
}

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

    // Nieve blur with mirrieing in the edeges

    // Read the input image data
    std::vector<Pixel24> imageData(header.width * header.height);
    file.read(reinterpret_cast<char*>(imageData.data()), imageData.size() * sizeof(Pixel24));

    file.close();

    NaiveBlur(imageData,header.width, header.height , 9);

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
