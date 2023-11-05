//
// Created by Jaibeer Dugal on 05/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_NAIVEBLURTHREADED_HPP
#define CPPIMAGECOMPRESSION_NAIVEBLURTHREADED_HPP

#include <iostream>

class AImageData;


class NaiveBlurThreaded
{
private:
    static const int KernalSizeMin = 0;
    static const int KernelSizeMax = 15;
public:
    static void PerformNaiveBlur_Threaded(AImageData &imageData , float blurFactor);

};


#endif //CPPIMAGECOMPRESSION_NAIVEBLURTHREADED_HPP
