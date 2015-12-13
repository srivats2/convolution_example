#ifndef __GAUSSIAN_FILTER__
#define __GAUSSIAN_FILTER__

#include "CImg.h"
#include "constants.h"
#include "ImageConvolutionFilter.hxx"
#include "ImageBase.hxx"
class GaussianFilterConvolution : public ImageConvolutionFilter{

public:
    ImageBase* perform_new_convolution(ImageBase *, int num_threads);
    GaussianFilterConvolution(int sigma);

protected:
    cimg_library::CImg<>gfilter, Gx;
    unsigned int sigma2, sigma4;
    float D;

};

#endif
