#include "Arguments.hpp"
#include "ImageData/TgaModule.hpp"
#include "ImageData/ImageData.hpp"
#include "ImageBlurringAlgos/FastGaussianBlur.hpp"

void NaiveBlur(std::vector<Pixel32> &image, int width, int height, int kernelSize)
{
    std::vector<Pixel32> originalImage = image; // Create a copy of the original image

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int pixelCount = 0;

            for (int j = -kernelSize; j <= kernelSize; j++)
            {
                for (int i = -kernelSize; i <= kernelSize; i++)
                {
                    int newX = x + i;
                    int newY = y + j;

                    // Apply mirror boundary conditions for out-of-bounds pixels
                    if (newX < 0)
                    {
                        newX = -newX;  // Mirror the x-coordinate
                    } else if (newX >= width)
                    {
                        newX = 2 * width - newX - 1;  // Mirror the x-coordinate
                    }

                    if (newY < 0)
                    {
                        newY = -newY;  // Mirror the y-coordinate
                    } else if (newY >= height)
                    {
                        newY = 2 * height - newY - 1;  // Mirror the y-coordinate
                    }

                    if (newX >= 0 && newX < width && newY >= 0 && newY < height)
                    {
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

int main(int argc, char *argv[])
{

    Args *appArgs = new Args(argc, argv);
    std::cout << (appArgs->getIsRunnableConfig() ? "this is a runnable config" : "this is not a runnable config");


    auto tgaImage = ImageData::Create(appArgs->getSource());
    std::cout<<"\n randome pixels color" << tgaImage->GetPixels()[0].r;

    auto pixelData = tgaImage->GetPixels();
    //NaiveBlur(pixelData, tgaImage->GetWidth(), tgaImage->GetHeight(), 5);
    //tgaImage->SetPixelData(pixelData);
    FastGaussianBlur::PerformFastGaussianBlur(*tgaImage, appArgs->getBlurFactor());
    std::vector<Pixel32> pixelData2 = tgaImage->GetPixels();
    for(int i = 0; i < pixelData2.size(); i++)
    {
        if(pixelData2[i].r > 255)
        {
            std::cerr << "pixel red value is greater than 255";
        } else if (pixelData2[i].g > 255)
        {
            std::cerr << "pixel green value is greater than 255";
        } else if (pixelData2[i].b > 255)
        {
            std::cerr << "pixel blue value is greater than 255";
        } else if (pixelData2[i].a > 255)
        {
            std::cerr << "pixel alpha value is greater than 255";
        } else if(pixelData2[i].r < 0)
        {
            std::cerr <<"pixel red value is less than 0";
        } else if (pixelData2[i].g < 0)
        {
            std::cerr << "pixel green value is less than 0";
        } else if (pixelData2[i].b < 0)
        {
            std::cerr << "pixel blue value is less than 0";
        } else if (pixelData2[i].a < 0)
        {
            std::cerr << "pixel alpha value is less than 0";
        }
        ClampPixelValues(pixelData2[i]);
    }
    tgaImage->WritePixelDataToFile(appArgs->getDestination());

    return 0;
}
