//
// Created by Jaibeer Dugal on 01/11/2023.
//

#ifndef CPPIMAGECOMPRESSION_MATHUTILS_HPP
#define CPPIMAGECOMPRESSION_MATHUTILS_HPP

namespace MathUtils
{
    template<typename T>
    static T lerp(T a, T b, T t)
    {
        return (1 - t) * a + t * b;
    }
}

#endif //CPPIMAGECOMPRESSION_MATHUTILS_HPP
