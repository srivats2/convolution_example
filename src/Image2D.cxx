#include "Image2D.hxx"

ImageBase* Image2D::Clone(bool copy){

ImageBase* output = new Image2D();
unsigned int *Size;
Size =this->GetSize();
output->SetSize(Size);


if(copy){
unsigned char *data;
this->get_data(&data);
this->copy_data(data);
}

return output;
}

void Image2D::copy_data(unsigned char *data){
    unsigned int *Size = this->GetSize();

    for(unsigned int i = 0 ; i<Size[0]*Size[1] ; ++i){
        this->Buffer[i] = data[i];
    }
}

void Image2D::Reallocate(){
this->Buffer = new unsigned char[this->Size[0]*this->Size[1]];
this->BufferSize=this->Size[0]*this->Size[1];
this->Dimension=this->dim;

    for(int i=0; i<this->Size[0]*this->Size[1]; ++i){
        this->Buffer[i] = 0;
    }
}
