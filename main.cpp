#include "Arguments.hpp"
#include "ImageData/TgaModule.hpp"
#include "ImageData/ImageData.hpp"
#include "ImageBlurringAlgos/Base/ImageBlurrer.hpp"

#include <chrono>

int main(int argc, char *argv[])
{

    Args *appArgs = new Args(argc, argv);

    if(!appArgs->getIsRunnableConfig())
    {
        std::cerr << "Invalid arguments passed" << std::endl;
        Args::showHelp();
        return 0;
    }

    // total time to create the image
    auto start = std::chrono::high_resolution_clock::now();
    auto tgaImage = ImageData::Create(appArgs->getSource());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to create the image: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    // total time to blur the image
    start = std::chrono::high_resolution_clock::now();
    ImageBlurrer::BlurImage(*tgaImage, appArgs->getBlurFactor(), appArgs->getAlgo());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to blur the image: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    // total time to write the image to file
    start = std::chrono::high_resolution_clock::now();
    tgaImage->WritePixelDataToFile(appArgs->getDestination());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to write the image to file: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    return 0;
}
