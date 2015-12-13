#ifndef __IMAGE_BASE_H__
#define __IMAGE_BASE_H__

class ImageBase
{
 public:
  ImageBase(unsigned int dimension);
  ~ImageBase();

  virtual void Reallocate() = 0;
  virtual ImageBase* Clone(bool copyBuffer = false) = 0;

  unsigned int GetDimension()
  {
	  return this->Dimension;
  }
  unsigned char* GetBufferPointer()
  {
	  return this->Buffer;
  }

  void SetSize(unsigned int dim[3]);
  unsigned int* GetSize();

  void ReadFile(char* filename);
  void WriteFile(char* filename);

  //Adding just the pointer casting so that I can display using CImg..
  void get_data(unsigned char **data);
  //adding this to convert from CImg to ImageBase*
  void put_data(unsigned char *data,unsigned int width, unsigned int height);
 protected:
  unsigned char* Buffer;
  unsigned int BufferSize;
  unsigned int Dimension;
  unsigned int Size[3];
};

#endif
