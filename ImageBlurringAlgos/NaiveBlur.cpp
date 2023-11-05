//
// Created by Jaibeer Dugal on 05/11/2023.
//

#include "NaiveBlur.hpp"
#include "../ImageData/Base/AImageData.hpp"
#include "../Utils/MathUtils.hpp"

#include <math.h>

void NaiveBlur::PerformNaiveBlur(AImageData &imageData, float blurFactor)
{
    std::vector<Pixel32> originalImage = imageData.GetPixels();
    std::vector<Pixel32> image = imageData.GetPixels();
    int height = imageData.GetHeight();
    int width = imageData.GetWidth();

    // we need to keep the kernal size to odd numbers between 0 - 15 as from testing that works the best
    int kernelSize = (int)MathUtils::lerp((float)KernalSizeMin, (float)KernelSizeMax, blurFactor);

    if(kernelSize % 2 == 0)
    {
        kernelSize++;
    }

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
    imageData.SetPixelData(image);
}
