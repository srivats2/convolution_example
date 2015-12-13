#ifndef __IMAGE_2D__
#define __IMAGE_2D__
#include "ImageBase.hxx"
class Image2D : public ImageBase{
public:

       Image2D():ImageBase(dim){
           dim=1;
       };
      ~Image2D(){};
void Reallocate();
ImageBase* Clone(bool);
void copy_data(unsigned char *);
private :
unsigned int dim;

};

#endif
