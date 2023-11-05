//
// Created by Jaibeer Dugal on 05/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_IMAGEBLURRER_HPP
#define CPPIMAGECOMPRESSION_IMAGEBLURRER_HPP

#include "ESupportedImageBlurringAlgos.hpp"

class AImageData;

class ImageBlurrer
{
public:
    static void BlurImage(AImageData& imageData, float blurFactor , ESupportedImageBlurringAlgos imageBlurringAlgorithm);
};


#endif //CPPIMAGECOMPRESSION_IMAGEBLURRER_HPP
