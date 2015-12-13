#include "GaussianFilterConvolution.hxx"
#include "iostream"
GaussianFilterConvolution::GaussianFilterConvolution(int sigma){

    gfilter.assign(6*sigma+1);
    Gx.assign(6*sigma+1);

    for(int i =0 ; i<6*sigma+1; i++){
        gfilter(i) =(float) i -(3*sigma);
    }
    sigma2 = sigma*sigma;
    sigma4 = sigma4*sigma4;
    D =((std::sqrt(2*MUPI))*sigma);

    cimg_foroff(Gx,off){
           Gx[off] = (std::exp(-0.5*((gfilter[off]*gfilter[off])/sigma2))/D);
       }
}


ImageBase* GaussianFilterConvolution::perform_new_convolution(ImageBase *I,int num_threads){
    cimg_library::CImg<> full2D = this->Gx.get_transpose();
    full2D*=this->Gx;
    this->SetConvolutionWindow(full2D.data(),full2D.width(),full2D.height());
    //I.get_convolve(full2D).display();
    ImageBase *output = this->perform_new_filtering(I,full2D.width(),full2D.height(),num_threads);
    return output;



}
