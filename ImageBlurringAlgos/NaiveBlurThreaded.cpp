//
// Created by Jaibeer Dugal on 05/11/2023.
//

#include "NaiveBlurThreaded.hpp"
#include "../ImageData/Base/AImageData.hpp"
#include "../Utils/MathUtils.hpp"
#include <thread>

void NaiveBlurThreaded::PerformNaiveBlur_Threaded(AImageData &imageData, float blurFactor)
{
    std::vector<Pixel32> originalImage = imageData.GetPixels();
    std::vector<Pixel32> image = imageData.GetPixels();
    int height = imageData.GetHeight();
    int width = imageData.GetWidth();

    int kernelSize = (int)(std::max(width, height) * (blurFactor / 10)) / 4;

    std::cout<<"Kernel Size : "<<kernelSize<<std::endl;

    if (kernelSize % 2 == 0)
    {
        kernelSize++;
    }

    std::mutex mtx;

    auto threadFunc = [&](int startY, int endY)
    {
        for (int y = startY; y < endY; y++)
        {
            std::cout << "Interations completed: " << y << " out of " << endY << " on thread " << std::this_thread::get_id() << std::endl;
            float percentile = (float)(y / endY) * 100.0f;
            std::cout << "Percentile completed: " << percentile << "%" << std::endl;
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
                        }
                        else if (newX >= width)
                        {
                            newX = 2 * width - newX - 1;  // Mirror the x-coordinate
                        }

                        if (newY < 0)
                        {
                            newY = -newY;  // Mirror the y-coordinate
                        }
                        else if (newY >= height)
                        {
                            newY = 2 * height - newY - 1;  // Mirror the y-coordinate
                        }

                        if (newX >= 0 && newX < width && newY >= 0 && newY < height)
                        {
                            mtx.lock();
                            totalRed += originalImage[newY * width + newX].r;
                            totalGreen += originalImage[newY * width + newX].g;
                            totalBlue += originalImage[newY * width + newX].b;
                            pixelCount++;
                            mtx.unlock();
                        }
                    }
                }

                mtx.lock();
                image[y * width + x].r = totalRed / pixelCount;
                image[y * width + x].g = totalGreen / pixelCount;
                image[y * width + x].b = totalBlue / pixelCount;
                mtx.unlock();
            }
        }
    };

    int numThreads = std::thread::hardware_concurrency();
    const int rowsPerThread = height / numThreads;
    // Create and run multiple threads.
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++)
    {
        int startY = i * rowsPerThread;
        int endY = (i == numThreads - 1) ? height : (startY + rowsPerThread);

        threads.emplace_back(threadFunc, startY, endY);
    }

    // Wait for all threads to finish.
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Set the processed image data to imageData.
    imageData.SetPixelData(image);
}