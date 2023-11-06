//
// Created by Jaibeer Dugal on 06/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_NAIVEBLURPREFIXSUMMAT_HPP
#define CPPIMAGECOMPRESSION_NAIVEBLURPREFIXSUMMAT_HPP

class AImageData;

class NaiveBlur_PrefixSumMat
{
public:
    static void PerformNaive_PrefixSumBlur(AImageData &imageData, float blurFactor);
};


#endif //CPPIMAGECOMPRESSION_NAIVEBLURPREFIXSUMMAT_HPP
