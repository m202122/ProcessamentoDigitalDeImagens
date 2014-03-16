#ifndef __FILTER_H_
#define __FILTER_H_

#include "itkImage.h"
#include "itkMedianImageFilter.h"
#include "itkMeanImageFilter.h"
#include "itkGaussianBlurImageFunction.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkLaplacianSharpeningImageFilter.h"

#include "itkHistogram.h"
#include "itkSampleToHistogramFilter.h"
#include "itkImageToListSampleAdaptor.h"

#include "itkOtsuThresholdImageFilter.h"

#include "itkWatershedImageFilter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"

#include "itkBinaryThresholdImageFilter.h"
#include "itkThresholdMaximumConnectedComponentsImageFilter.h"

#include "itkLabelToRGBImageFilter.h"
#include "itkRelabelComponentImageFilter.h"
#include "itkScalarConnectedComponentImageFilter.h"

//brack white
typedef unsigned char PixelType;
typedef itk::Image< PixelType,  2 >  ImageType;
typedef itk::ImageFileReader< ImageType  >  ReaderType;
typedef itk::ImageFileWriter< ImageType >  WriterType;

class Filter
{
private:
    ReaderType::Pointer reader;
    WriterType::Pointer writer;
    ImageType::SizeType indexRadius;

    void setSaveName(const char* name);

public:

    Filter(const char* input);
    ~Filter();


    void toBlackWhite(const char* name);
    void medianFilter(const char* name);
    void meanFilter(const char* name);
    void gaussianFilter(const char* name, double sigma, int kernalWidth);
    void laplacianFilter(const char* name);
    void imageHistogram(const char* name);
    void watershed(const char* name, float level);
    void otsu(const char* name);
    void threshold(const char* name, int lower, int upper);
    void autoThreshold(const char* name);
    void connectedObjects(const char* name, int* i);
};


#endif // __FILTER_H_

