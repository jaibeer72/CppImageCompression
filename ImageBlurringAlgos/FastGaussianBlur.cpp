//
// Created by Jaibeer Dugal on 05/11/2023.
//

#include "FastGaussianBlur.hpp"
#include "../Utils/MathUtils.hpp"
#include <cmath>

void FastGaussianBlur::PerformFastGaussianBlur(AImageData &imageData, float blurFactor)
{
    int sigma = MathUtils::lerp((float)sigmaMin, (float)simgaMax, blurFactor);

    std::vector<int> boxes = computeBoxes(sigma, numberOfBoxes);
    std::vector<Pixel32> pixelData = imageData.GetPixels();
    std::vector<Pixel32> tempPixelData = imageData.GetPixels();
    boxBlur(pixelData, tempPixelData, imageData.GetWidth(), imageData.GetHeight(), (boxes[0] - 1) / 2);
    boxBlur(tempPixelData, pixelData, imageData.GetWidth(), imageData.GetHeight(), (boxes[1] - 1) / 2);
    boxBlur(pixelData, tempPixelData, imageData.GetWidth(), imageData.GetHeight(), (boxes[2] - 1) / 2);

    imageData.SetPixelData(tempPixelData);
}

void FastGaussianBlur::boxBlurH(std::vector<Pixel32> &scl, std::vector<Pixel32> &tcl, int w, int h, int radius) {
    double iarr = (double)1.f / (radius + radius + 1);

    for (int y = 0; y < h; y++) {
        int targetIndex = y * w;
        int leftIndex = targetIndex;
        int rightIndex = targetIndex + radius;

        Pixel32 firstValue = scl[targetIndex];
        Pixel32 lastValue = scl[targetIndex + w - 1];
        Pixel32 value;

        value.r = (radius + 1) * firstValue.r;
        value.g = (radius + 1) * firstValue.g;
        value.b = (radius + 1) * firstValue.b;
        value.a = (radius + 1) * firstValue.a;

        for (int j = 0; j < radius; j++) {
            value = value + scl[targetIndex + j];
        }

        for (int j = 0; j <= radius; j++) {
            value = value + (scl[rightIndex++] - firstValue);

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            targetIndex++;
        }

        for (int j = radius + 1; j < w - radius; j++) {
            value = value + (scl[rightIndex++] - scl[leftIndex++]);

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            targetIndex++;
        }

        for (int j = w - radius; j < w; j++) {
            value = value + (lastValue - scl[leftIndex++]);

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            targetIndex++;
        }
    }
}

void FastGaussianBlur::boxBlurT(std::vector<Pixel32> &scl, std::vector<Pixel32> &tcl, int w, int h, int radius) {
    double iarr = (double)1.f / (radius + radius + 1);

    for (int x = 0; x < w; x++) {
        int targetIndex = x;
        int leftIndex = targetIndex;
        int rightIndex = targetIndex + radius * w;

        Pixel32 firstValue = scl[targetIndex];
        Pixel32 lastValue = scl[targetIndex + w * (h - 1)];
        Pixel32 value;

        value.r = (radius + 1) * firstValue.r;
        value.g = (radius + 1) * firstValue.g;
        value.b = (radius + 1) * firstValue.b;
        value.a = (radius + 1) * firstValue.a;

        for (int j = 0; j < radius; j++) {
            value = value + scl[targetIndex + j * w];
        }

        for (int j = 0; j <= radius; j++) {
            value = value + scl[rightIndex] - firstValue;

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            rightIndex += w;
            targetIndex += w;
        }

        for (int j = radius + 1; j < h - radius; j++) {
            value = value + scl[rightIndex] - scl[leftIndex];

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            leftIndex += w;
            rightIndex += w;
            targetIndex += w;
        }

        for (int j = h - radius; j < h; j++) {
            value = value + lastValue - scl[leftIndex];

            tcl[targetIndex].r = std::round(value.r * iarr);
            tcl[targetIndex].g = std::round(value.g * iarr);
            tcl[targetIndex].b = std::round(value.b * iarr);
            tcl[targetIndex].a = std::round(value.a * iarr);
            leftIndex += w;
            targetIndex += w;
        }
    }
}


void FastGaussianBlur::boxBlur(std::vector<Pixel32> &scl, std::vector<Pixel32> &tcl, int w, int h, int radius)
{
    if (radius < 0 || radius > w || radius > h) {
        throw std::invalid_argument("Invalid kernel radius");
    }

    std::swap(scl, tcl);
    boxBlurH(tcl, scl, w, h, radius);
    boxBlurT(scl, tcl, w, h, radius);
}

std::vector<int> FastGaussianBlur::computeBoxes(float sigma, int numberOfBoxes)
{
    double wIdeal = std::sqrt((12 * sigma * sigma / numberOfBoxes) + 1);
    int wl = std::floor(wIdeal);
    if (wl % 2 == 0) wl--;

    int wu = wl + 2;

    double mIdeal = (double)(12 * sigma * sigma - numberOfBoxes * wl * wl - 4 * numberOfBoxes * wl - 3 * numberOfBoxes) / (-4 * wl - 4);
    int m = std::round(mIdeal);

    std::vector<int> sizes;
    for (int i = 0; i < numberOfBoxes; i++) {
        sizes.push_back((i < m ? wl : wu));
    }

    return sizes;
}