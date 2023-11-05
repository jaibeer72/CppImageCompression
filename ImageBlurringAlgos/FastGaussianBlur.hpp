//
// Created by Jaibeer Dugal on 05/11/2023.
//
// Look below for refrances

#ifndef CPPIMAGECOMPRESSION_FASTGAUSSIANBLUR_HPP
#define CPPIMAGECOMPRESSION_FASTGAUSSIANBLUR_HPP

#include "../ImageData/Base/AImageData.hpp"

class FastGaussianBlur
{
public:
    static void PerformFastGaussianBlur(AImageData &imageData, float blurFactor);

private:
    static const int numberOfBoxes = 3;
    static constexpr float simgaMax = 5.0f;
    static constexpr float sigmaMin = 0.0f;

private:
    static std::vector<int> computeBoxes(float sigma, int numberOfBoxes);
    static void boxBlurH(std::vector<Pixel32>& scl, std::vector<Pixel32>& tcl, int w, int h, int radius);
    static void boxBlurT(std::vector<Pixel32>& scl, std::vector<Pixel32>& tcl, int w, int h, int radius);
    static void boxBlur(std::vector<Pixel32>& scl, std::vector<Pixel32>& tcl, int w, int h, int radius);

};

/*
 * Refrances: https://www.youtube.com/watch?v=C_zFhWdM4ic
 *  https://blog.ivank.net/fastest-gaussian-blur.html
 *  code being converted from JS to C++:
 *  Currently this is not working as expected and fails to run properly
 *  creates huge amout of artifacts.
 *
 *  function gaussBlur_4 (scl, tcl, w, h, r) {
    var bxs = boxesForGauss(r, 3);
    boxBlur_4 (scl, tcl, w, h, (bxs[0]-1)/2);
    boxBlur_4 (tcl, scl, w, h, (bxs[1]-1)/2);
    boxBlur_4 (scl, tcl, w, h, (bxs[2]-1)/2);
}
function boxBlur_4 (scl, tcl, w, h, r) {
    for(var i=0; i<scl.length; i++) tcl[i] = scl[i];
    boxBlurH_4(tcl, scl, w, h, r);
    boxBlurT_4(scl, tcl, w, h, r);
}
function boxBlurH_4 (scl, tcl, w, h, r) {
    var iarr = 1 / (r+r+1);
    for(var i=0; i<h; i++) {
        var ti = i*w, li = ti, ri = ti+r;
        var fv = scl[ti], lv = scl[ti+w-1], val = (r+1)*fv;
        for(var j=0; j<r; j++) val += scl[ti+j];
        for(var j=0  ; j<=r ; j++) { val += scl[ri++] - fv       ;   tcl[ti++] = Math.round(val*iarr); }
        for(var j=r+1; j<w-r; j++) { val += scl[ri++] - scl[li++];   tcl[ti++] = Math.round(val*iarr); }
        for(var j=w-r; j<w  ; j++) { val += lv        - scl[li++];   tcl[ti++] = Math.round(val*iarr); }
    }
}
function boxBlurT_4 (scl, tcl, w, h, r) {
    var iarr = 1 / (r+r+1);
    for(var i=0; i<w; i++) {
        var ti = i, li = ti, ri = ti+r*w;
        var fv = scl[ti], lv = scl[ti+w*(h-1)], val = (r+1)*fv;
        for(var j=0; j<r; j++) val += scl[ti+j*w];
        for(var j=0  ; j<=r ; j++) { val += scl[ri] - fv     ;  tcl[ti] = Math.round(val*iarr);  ri+=w; ti+=w; }
        for(var j=r+1; j<h-r; j++) { val += scl[ri] - scl[li];  tcl[ti] = Math.round(val*iarr);  li+=w; ri+=w; ti+=w; }
        for(var j=h-r; j<h  ; j++) { val += lv      - scl[li];  tcl[ti] = Math.round(val*iarr);  li+=w; ti+=w; }
    }
}

 */


#endif //CPPIMAGECOMPRESSION_FASTGAUSSIANBLUR_HPP
