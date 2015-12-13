#ifndef __IM_FILTER_BASE__
#define __IM_FILTER_BASE__
class ImageBase;
class ImageFilterBase
{
public:
    ImageFilterBase(){};
    ~ImageFilterBase(){};
    virtual ImageBase* DoFiltering(ImageBase* input)=0;
};

#endif
