#include "ImageBase.hxx"

#include <stdio.h>
#include <fstream>
#include <iostream>

ImageBase::ImageBase(unsigned int dim)
{
  this->Buffer = NULL;

  this->Dimension = dim;

  this->Size[0] = 0;
  this->Size[1] = 0;
  this->Size[2] = 0;
}

ImageBase::~ImageBase()
{
  if(this->Buffer)
 {
    delete this->Buffer;
  }
}

void ImageBase::SetSize(unsigned int dim[3])
{
  if(dim[0] != this->Size[0] ||
     dim[1] != this->Size[1] ||
     dim[2] != this->Size[2])
  {
    this->Size[0] = dim[0];
    this->Size[1] = dim[1];
    this->Size[2] = dim[2];

    this->Reallocate();
  }
}

unsigned int* ImageBase::GetSize()
{
  return this->Size;
}


void ImageBase::ReadFile(char* filename)
{
  std::fstream fin;
  fin.open(filename, std::ios::in|std::ios::binary);
  fin.read((char*)this->Buffer, this->BufferSize);
  fin.close();
}

void ImageBase::WriteFile(char* filename)
{
  std::fstream fout;
  fout.open(filename, std::ios::out|std::ios::binary);
  fout.write((char*)this->Buffer, this->BufferSize);
  fout.close();
}

void ImageBase::get_data(unsigned char **data){
    *data= this->Buffer;
}


void ImageBase::put_data(unsigned char *data, unsigned int width, unsigned int height){
    this->Buffer = new unsigned char[width*height];
    this->BufferSize = width*height;

    for(int i=0; i<width*height;++i){
        this->Buffer[i] = data[i];
    }

}
