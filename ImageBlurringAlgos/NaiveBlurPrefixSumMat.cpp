//
// Created by Jaibeer Dugal on 06/11/2023.
//

#include "NaiveBlurPrefixSumMat.hpp"
#include "../ImageData/Base/AImageData.hpp"


void NaiveBlur_PrefixSumMat::PerformNaive_PrefixSumBlur(AImageData &imageData, float blurFactor)
{
    std::vector<Pixel32> image = imageData.GetPixels();
    int height = imageData.GetHeight();
    int width = imageData.GetWidth();

    int kernelSize = (int)(std::max(width, height) * (blurFactor / 10)) / 4;

    if (kernelSize % 2 == 0)
    {
        kernelSize++;
    }

    // Create cumulative sum matrices for each color channel
    std::vector<int> cumulativeSumRed(width * height);
    std::vector<int> cumulativeSumGreen(width * height);
    std::vector<int> cumulativeSumBlue(width * height);

    // Calculate cumulative sums
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;
            int red = image[index].r;
            int green = image[index].g;
            int blue = image[index].b;

            if (x > 0)
            {
                red += cumulativeSumRed[index - 1];
                green += cumulativeSumGreen[index - 1];
                blue += cumulativeSumBlue[index - 1];
            }

            if (y > 0)
            {
                red += cumulativeSumRed[index - width];
                green += cumulativeSumGreen[index - width];
                blue += cumulativeSumBlue[index - width];
            }

            if (x > 0 && y > 0)
            {
                red -= cumulativeSumRed[index - width - 1];
                green -= cumulativeSumGreen[index - width - 1];
                blue -= cumulativeSumBlue[index - width - 1];
            }

            cumulativeSumRed[index] = red;
            cumulativeSumGreen[index] = green;
            cumulativeSumBlue[index] = blue;
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int pixelCount = 0;

            // Calculate the coordinates of the kernel corners
            // for now we will loose the corners 
            int x1 = std::max(0, x - kernelSize);
            int y1 = std::max(0, y - kernelSize);
            int x2 = std::min(width - 1, x + kernelSize);
            int y2 = std::min(height - 1, y + kernelSize);

            // Calculate the sum within the kernel using the prefix sums
            totalRed = cumulativeSumRed[y2 * width + x2];
            totalGreen = cumulativeSumGreen[y2 * width + x2];
            totalBlue = cumulativeSumBlue[y2 * width + x2];

            if (x1 > 0)
            {
                totalRed -= cumulativeSumRed[y2 * width + x1 - 1];
                totalGreen -= cumulativeSumGreen[y2 * width + x1 - 1];
                totalBlue -= cumulativeSumBlue[y2 * width + x1 - 1];
            }

            if (y1 > 0)
            {
                totalRed -= cumulativeSumRed[(y1 - 1) * width + x2];
                totalGreen -= cumulativeSumGreen[(y1 - 1) * width + x2];
                totalBlue -= cumulativeSumBlue[(y1 - 1) * width + x2];
            }

            if (x1 > 0 && y1 > 0)
            {
                totalRed += cumulativeSumRed[(y1 - 1) * width + x1 - 1];
                totalGreen += cumulativeSumGreen[(y1 - 1) * width + x1 - 1];
                totalBlue += cumulativeSumBlue[(y1 - 1) * width + x1 - 1];
            }

            // Calculate the number of pixels within the kernel
            pixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);

            image[y * width + x].r = totalRed / pixelCount;
            image[y * width + x].g = totalGreen / pixelCount;
            image[y * width + x].b = totalBlue / pixelCount;
        }
    }

    imageData.SetPixelData(image);
}
