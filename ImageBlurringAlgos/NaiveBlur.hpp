//
// Created by Jaibeer Dugal on 05/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_NAIVEBLUR_HPP
#define CPPIMAGECOMPRESSION_NAIVEBLUR_HPP

class AImageData;

class NaiveBlur
{
private:
    static const int KernalSizeMin = 0;
    static const int KernelSizeMax = 15;

public:
    static void PerformNaiveBlur(AImageData &imageData, float sigma);
};


#endif //CPPIMAGECOMPRESSION_NAIVEBLUR_HPP
