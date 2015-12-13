#include <stdio.h>

#include "Image2D.hxx"
#include "ImageConvolutionFilter.hxx"
#include "GaussianFilterConvolution.hxx"
#include "CImg.h"
#include <iostream>
template<typename T>
void convert_to_grayscale(cimg_library::CImg<T> &image,cimg_library::CImg<T> &grayscale_image){
    grayscale_image.assign(image.width(),image.height(),1,1);
    grayscale_image.fill(0);
    if(image.spectrum()==3 || image.spectrum()==4){
        int R,G,B;
        for (int r = 0 ; r< image.height(); r++){
            for (int c= 0 ; c < image.width(); c++){
                R = (int)image(c,r,0,0);
                G = (int)image(c,r,0,1);
                B = (int)image(c,r,0,2);
                grayscale_image(c,r,0,0) = (float) (0.2989 * R + 0.5870 * G + 0.1140 * B);
            }
        }
    }else if(image.spectrum()==1){
        grayscale_image.assign(image);
    }

}


void large_image_multithreaded_test(void){
    cimg_library::CImg<unsigned char> new_im("../../data/Yosemite_large.jpg");
    cimg_library::CImg<unsigned char> grayscale_im;
    convert_to_grayscale(new_im,grayscale_im);
    ImageBase* new_input = new Image2D();
    unsigned int new_size[3] = {new_im.width(),new_im.height()};
    unsigned char *output_im;
    new_input->SetSize(new_size);
    new_input->put_data(grayscale_im.data(),grayscale_im.width(),grayscale_im.height());


    GaussianFilterConvolution *g_filter = new GaussianFilterConvolution(7);

    ImageBase* gaussian_output=g_filter->perform_new_convolution(new_input,4);
    gaussian_output->get_data(&output_im);
    cimg_library::CImg<>test3(output_im,grayscale_im.width(),grayscale_im.height(),1,1,false);
    //(new_im,test3).display("Large image example - Original Image, Gaussian Filtered image");

}

int main()
{
  ImageFilterBase* filter = new ImageConvolutionFilter();
  ImageBase* input = new Image2D();

  char inputFilename[256] = "lena.raw";
  char outputFilename[256] = "out.raw";

  float laplacianWindow[3][3] = {{-0.125, -0.125, -0.125},
				 {-0.125, 1, -0.125},
				 {-0.125, -0.125, -0.125}};

  float sobelHWindow[3][3] = {{-1, -2, -1},
			      { 0,  0,  0},
			      {-1, -2, -1}};

  float meanWindow[3][3] = {{1.0/9.0, 1.0/9.0, 1.0/9.0 },
			    {1.0/9.0, 1.0/9.0, 1.0/9.0 },
			    {1.0/9.0, 1.0/9.0, 1.0/9.0 }};

  float gaussianWindow[3][3] = {{1.0/16.0, 2.0/16.0, 1.0/16.0 },
				{2.0/16.0, 4.0/16.0, 2.0/16.0 },
				{1.0/16.0, 2.0/16.0, 1.0/16.0 }};

  unsigned int size[3] = {256, 256};
  input->SetSize(size);
  input->ReadFile(inputFilename);

  ((ImageConvolutionFilter*)filter)->SetConvolutionWindow(gaussianWindow);
  ImageBase* output = filter->DoFiltering(input);
  output->WriteFile(outputFilename);

 //just something simple to display input and output images side by side
// please do excuse my variable names...I usually have much better names
  unsigned int *Size;
  Size = input->GetSize();
  unsigned char *input_im;
  unsigned char *output_im;
  input->get_data(&input_im);
  output->get_data(&output_im);

  cimg_library::CImg<>test1(input_im,Size[0],Size[1],1,1,false);
  cimg_library::CImg<>test2(output_im,Size[0],Size[1],1,1,false);

  //Added for part 2
  //sigma specified here turns to 6*sigma meaning 3*sigma on either side in a zero-norm gaussian
  GaussianFilterConvolution *g_filter = new GaussianFilterConvolution(1);
  //call with just 1 thread
  ImageBase* gaussian_output=g_filter->perform_new_convolution(input,1);
  gaussian_output->get_data(&output_im);
  cimg_library::CImg<>test3(output_im,Size[0],Size[1],1,1,false);
  //(test1,test2,test3).display("Original, Given Implementation & Custom Gaussian Implementation");

  large_image_multithreaded_test();

  delete input;
  delete output;
  delete filter;
}
