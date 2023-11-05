//
// Created by Jaibeer Dugal on 05/11/2023.
//

#include "ImageBlurrer.hpp"
#include "../FastGaussianBlur.hpp"
#include "../NaiveBlur.hpp"


// Factory class that will run the correct function based on the type of image blurring algorithm selected
void ImageBlurrer::BlurImage(AImageData &imageData, float blurFactor , ESupportedImageBlurringAlgos imageBlurringAlgorithm)
{
    switch (imageBlurringAlgorithm)
    {
        case ESupportedImageBlurringAlgos::NAIVE_BLUR:
            NaiveBlur::PerformNaiveBlur(imageData, blurFactor);
            break;
        case ESupportedImageBlurringAlgos::FAST_GAUSSIAN_BLUR:
            FastGaussianBlur::PerformFastGaussianBlur(imageData, blurFactor);
            break;
        default:
            std::cout << "Invalid image blurring algorithm selected" << std::endl;
            break;
    }
}
