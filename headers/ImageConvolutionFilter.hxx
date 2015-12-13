#ifndef __IMAGE_CONVOLUTION_FILTER_H__
#define __IMAGE_CONVOLUTION_FILTER_H__

#include "ImageFilterBase.hxx"

class ImageBase;

class ImageConvolutionFilter : public ImageFilterBase
{
 public:
  ImageConvolutionFilter();
  ~ImageConvolutionFilter();

  ImageBase* PrepareOutput(ImageBase *);
  void SetConvolutionWindow(float window[3][3]);
  //overloaded
  void SetConvolutionWindow(float *data, const int filter_width, const int filter_height);
  virtual ImageBase* DoFiltering(ImageBase* input);
  //new function
  virtual ImageBase* perform_new_filtering(ImageBase* input, const int filter_width, const int filter_height, int num_threads);
 protected:
  float ConvolutionWindow[3][3];
  //added for the generic convolution filter;
  float **MultiScaleConvolutionWindow;
};

#endif
