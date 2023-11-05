#include "Arguments.hpp"
#include "ImageData/TgaModule.hpp"
#include "ImageData/ImageData.hpp"
#include "ImageBlurringAlgos/Base/ImageBlurrer.hpp"

void NaiveBlur(std::vector<Pixel32> &image, int width, int height, int kernelSize)
{

}

int main(int argc, char *argv[])
{

    Args *appArgs = new Args(argc, argv);

    if(!appArgs->getIsRunnableConfig())
    {
        std::cerr << "Invalid arguments passed" << std::endl;
        Args::showHelp();
        return 0;
    }


    auto tgaImage = ImageData::Create(appArgs->getSource());
    ImageBlurrer::BlurImage(*tgaImage, appArgs->getBlurFactor(), appArgs->getAlgo());
    tgaImage->WritePixelDataToFile(appArgs->getDestination());

    return 0;
}
