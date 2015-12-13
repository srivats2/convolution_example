#include "ImageConvolutionFilter.hxx"

#include <iostream>
#include <cmath>
#include "ImageBase.hxx"
#include "omp.h"
ImageConvolutionFilter::ImageConvolutionFilter()
{
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
	{
      this->ConvolutionWindow[i][j] = 0;
    }
  }
}

ImageConvolutionFilter::~ImageConvolutionFilter()
{


}

void ImageConvolutionFilter::SetConvolutionWindow(float window[3][3])
{
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
	{
      this->ConvolutionWindow[i][j] = window[i][j];
    }
  }
}

ImageBase* ImageConvolutionFilter::DoFiltering(ImageBase* input)
{
  ImageBase* output = this->PrepareOutput(input);

  unsigned int* imageSize = output->GetSize();

  unsigned char* outputBuffer = output->GetBufferPointer();
  unsigned char* inputBuffer = input->GetBufferPointer();

  float val;

  for(int i=1; i<imageSize[0]-1; i++)
  {
    for(int j=1; j<imageSize[1]-1; j++)
	{
      val = 0;
      for(int a=0; a<3; a++)
	  {
		for(int b=0; b<3; b++)
		{
			val += this->ConvolutionWindow[a][b] * inputBuffer[(j+b)*imageSize[0]+(i+a)];
		}
      }
      outputBuffer[j*imageSize[0]+i] =  val;
    }
  }
  

  return output;
}


ImageBase* ImageConvolutionFilter::PrepareOutput(ImageBase *input){
ImageBase *output = input->Clone();
}

void ImageConvolutionFilter::SetConvolutionWindow(float *data, const int filter_width, const int filter_height){
    this->MultiScaleConvolutionWindow = new float*[filter_height];
       for(int i = 0 ; i < filter_height ; ++i){
           this->MultiScaleConvolutionWindow[i] = new float[filter_width];
       }

       for(int i = 0 ; i < filter_height ; ++i){
           for(int j = 0 ; j < filter_width ; ++j){
               this->MultiScaleConvolutionWindow[i][j] = data[i*filter_width+j];
           }
       }

}
ImageBase* ImageConvolutionFilter::perform_new_filtering(ImageBase* input, const int filter_width, const int filter_height,int num_threads){
    ImageBase* output = this->PrepareOutput(input);

    unsigned int* imageSize = output->GetSize();

    unsigned char* outputBuffer = output->GetBufferPointer();
    unsigned char* inputBuffer = input->GetBufferPointer();

    float val;

    int pad_size = std::ceil((filter_width-1)/2); //ceil is not really required if odd filter size check is introduced
    //std::cout<<"\n"<<"Pad Size: "<<pad_size<<std::endl;

    int max_threads = num_threads;
    omp_set_dynamic(0);
    omp_set_num_threads(max_threads);
#pragma omp parallel for private(val) shared(outputBuffer) num_threads(max_threads)
    for(int i=pad_size; i<imageSize[0]-pad_size; i++)
    {
#pragma omp parallel for private(val) shared(outputBuffer) num_threads(max_threads)
      for(int j=pad_size; j<imageSize[1]-pad_size; j++)
      {
        val = 0;
        for(int a=0; a<filter_height; a++)
        {
          for(int b=0; b<filter_width; b++)
          {
              val += this->MultiScaleConvolutionWindow[a][b] * inputBuffer[(j+b)*imageSize[0]+(i+a)];
          }
        }
        outputBuffer[j*imageSize[0]+i] =  val;
      }
    }
    return output;
}
