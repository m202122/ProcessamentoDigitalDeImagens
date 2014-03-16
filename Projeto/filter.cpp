#include "filter.h"

Filter::Filter(const char* input)
{
    this->reader = ReaderType::New();
    this->reader->SetFileName(input);
    this->reader->Update();
    this->writer = WriterType::New();
    this->indexRadius[0] = 15;
    this->indexRadius[1] = 15;
}

Filter::~Filter()
{

}

void Filter::setSaveName(const char* name)
{
    this->writer->SetFileName(name);
}

void Filter::toBlackWhite(const char* name)
{
    setSaveName(name);
    writer->SetInput(reader->GetOutput());
    writer->Update();
}

void Filter::medianFilter(const char* name)
{
    setSaveName(name);
    typedef itk::MedianImageFilter< ImageType, ImageType >  FilterType;
    FilterType::Pointer filter = FilterType::New();

    filter->SetRadius( indexRadius );
    filter->SetInput(reader->GetOutput());
    writer->SetInput(filter->GetOutput());
    writer->Update();
}

void Filter::meanFilter(const char* name)
{
    setSaveName(name);
    typedef itk::MeanImageFilter< ImageType, ImageType >  FilterType;
    FilterType::Pointer filter = FilterType::New();

    filter->SetRadius( indexRadius );
    filter->SetInput(reader->GetOutput());
    writer->SetInput(filter->GetOutput());
    writer->Update();
}


void Filter::gaussianFilter(const char* name, double sigma, int kernelWidth)
{
    setSaveName(name);
    typedef itk::ImageRegionIterator< ImageType  > IteratorType;
    typedef itk::ImageRegionConstIterator< ImageType  > ConstIteratorType;
    reader->Update();
    const ImageType  * image = reader->GetOutput();

    ImageType ::RegionType region = image->GetBufferedRegion();

    ConstIteratorType it( image, region );
    ImageType ::Pointer output = ImageType ::New();

    output->SetRegions( region );
    output->SetOrigin(  image->GetOrigin()  );
    output->SetSpacing( image->GetSpacing() );
    output->Allocate();

    IteratorType out( output, region );

    typedef itk::GaussianBlurImageFunction< ImageType  > GFunctionType;
    GFunctionType::Pointer gaussianFunction = GFunctionType::New();
    gaussianFunction->SetInputImage( image );

    GFunctionType::ErrorArrayType setError;
    setError.Fill( 0.01 );
    gaussianFunction->SetMaximumError( setError );
    gaussianFunction->SetSigma( sigma );
    gaussianFunction->SetMaximumKernelWidth( kernelWidth );

    it.GoToBegin();
    out.GoToBegin();

    while( !it.IsAtEnd() )
    {
        out.Set( gaussianFunction->EvaluateAtIndex(it.GetIndex() ) );
        ++it;
        ++out;
    }

    writer->SetInput(output);
    writer->Update();
}

void Filter::laplacianFilter(const char* name)
{
    setSaveName(name);
    typedef itk::RescaleIntensityImageFilter<ImageType, ImageType> RescaleFilter;
    typedef itk::LaplacianSharpeningImageFilter<ImageType, ImageType >    LaplacianSharpeningFilter;

    RescaleFilter::Pointer rescale = RescaleFilter::New();

    LaplacianSharpeningFilter::Pointer lapFilter = LaplacianSharpeningFilter::New();

    lapFilter->SetInput( reader->GetOutput() );

    rescale->SetInput( lapFilter->GetOutput() );
    writer->SetInput( rescale->GetOutput() );

    rescale->SetOutputMinimum(   0 );
    rescale->SetOutputMaximum( 255 );

    writer->Update();
}

void Filter::imageHistogram(const char* name)
{
    setSaveName(name);
    typedef itk::Statistics::ImageToListSampleAdaptor< ImageType >   AdaptorType;

    AdaptorType::Pointer adaptor = AdaptorType::New();

    adaptor->SetImage(  reader->GetOutput() );
    reader->Update();

    typedef PixelType HistogramMeasurementType;
    typedef itk::Statistics::Histogram< HistogramMeasurementType > HistogramType;
    typedef itk::Statistics::SampleToHistogramFilter< AdaptorType, HistogramType> FilterType;

    FilterType::Pointer filter = FilterType::New();

    const unsigned int numberOfComponents = 1;
    HistogramType::SizeType size( numberOfComponents );
    size.Fill( 255 );

    filter->SetInput( adaptor );
    filter->SetHistogramSize( size );
    filter->SetMarginalScale( 10 );

    HistogramType::MeasurementVectorType min( numberOfComponents );
    HistogramType::MeasurementVectorType max( numberOfComponents );

    min.Fill( 0 );
    max.Fill( 255 );

    filter->SetHistogramBinMinimum( min );
    filter->SetHistogramBinMaximum( max );

    filter->Update();

    HistogramType::ConstPointer histogram = filter->GetOutput();

    const unsigned int histogramSize = histogram->Size();

    std::cout << "\nHistogram size " << histogramSize << std::endl;

    unsigned int aux = 0;

    unsigned int totalFrequency = 0;
    for( unsigned int bin=0; bin < histogramSize; bin++ )
        totalFrequency+=histogram->GetFrequency( bin, 0 );

    for( unsigned int bin=0; bin < histogramSize; bin++ )
    {
        aux = (unsigned int) histogram->GetFrequency( bin, 0 )*2000/totalFrequency;
        std::cout << "bin " << bin << " : ";
        for(unsigned int k = 0; k < aux; ++k)
            std::cout << "*";
        std::cout << std::endl;
    }

}

void Filter::watershed(const char* name, float level)
{

    typedef itk::RGBPixel<unsigned char>      RGBPixelType;

    typedef itk::Image< RGBPixelType, 2 >  RGBImageType;
    typedef itk::Image< float,  2 >  FloatType;

    typedef  itk::ImageFileWriter< RGBImageType  >        WriterType;

    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( name);

    typedef   itk::GradientMagnitudeRecursiveGaussianImageFilter<  ImageType, FloatType  > GradientMagnitudeFilterType;

    GradientMagnitudeFilterType::Pointer gradienMagnitudeFilter = GradientMagnitudeFilterType::New();

    gradienMagnitudeFilter->SetInput( reader->GetOutput() );
    gradienMagnitudeFilter->SetSigma( 1.0 );

    typedef  itk::WatershedImageFilter< FloatType  > WatershedFilterType;

    WatershedFilterType::Pointer watershedFilter = WatershedFilterType::New();

    watershedFilter->SetInput( gradienMagnitudeFilter->GetOutput() );

    watershedFilter->SetThreshold( 0.0);
    watershedFilter->SetLevel(level);


    typedef itk::Functor::ScalarToRGBPixelFunctor< unsigned long > ColorMapFunctorType;

    typedef WatershedFilterType::OutputImageType  LabeledImageType;

    typedef itk::UnaryFunctorImageFilter< LabeledImageType, RGBImageType, ColorMapFunctorType > ColorMapFilterType;

    ColorMapFilterType::Pointer colorMapFilter = ColorMapFilterType::New();

    colorMapFilter->SetInput(  watershedFilter->GetOutput() );

    writer->SetInput( colorMapFilter->GetOutput() );

    writer->Update();
}

void Filter::otsu(const char* name)
{
    setSaveName(name);
    typedef itk::OtsuThresholdImageFilter <ImageType, ImageType> FilterType;
    FilterType::Pointer otsuFilter  = FilterType::New();
    otsuFilter->SetInput(reader->GetOutput());
    otsuFilter->SetInsideValue(255);
    otsuFilter->SetOutsideValue(0);
    otsuFilter->Update();
    writer->SetInput(otsuFilter->GetOutput());
    writer->Update();
}


void Filter::threshold(const char* name, int lower, int upper)
{
    setSaveName(name);
    typedef itk::BinaryThresholdImageFilter <ImageType, ImageType> BinaryThresholdImageFilterType;
    BinaryThresholdImageFilterType::Pointer thresholdFilter = BinaryThresholdImageFilterType::New();
    thresholdFilter->SetInput(reader->GetOutput());
    thresholdFilter->SetLowerThreshold(lower);
    thresholdFilter->SetUpperThreshold(upper);
    thresholdFilter->SetInsideValue(255);
    thresholdFilter->SetOutsideValue(0);
    writer->SetInput(thresholdFilter->GetOutput());
    writer->Update();

}

void Filter::autoThreshold(const char* name)
{
    setSaveName(name);
    typedef itk::ThresholdMaximumConnectedComponentsImageFilter <ImageType> ThresholdMaximumConnectedComponentsImageFilter;
    ThresholdMaximumConnectedComponentsImageFilter::Pointer thresholdFilter = ThresholdMaximumConnectedComponentsImageFilter::New();
    thresholdFilter->SetInput(reader->GetOutput());
    thresholdFilter->Update();
    writer->SetInput(thresholdFilter->GetOutput());
    writer->Update();
}

void Filter::connectedObjects(const char *name, int* i)
{
    typedef itk::RGBPixel<unsigned char>           RGBPixelType;
    typedef unsigned short LabelPixelType;
    typedef itk::Image<LabelPixelType, 2 > LabelImageType;
    typedef itk::Image<RGBPixelType, 2>    RGBImageType;
    typedef itk::ScalarConnectedComponentImageFilter <ImageType, LabelImageType > ConnectedComponentImageFilterType;
    typedef itk::RelabelComponentImageFilter <LabelImageType, LabelImageType > RelabelFilterType;
    typedef itk::LabelToRGBImageFilter<LabelImageType, RGBImageType> RGBFilterType;

    typedef itk::ImageFileWriter< RGBImageType >  WriterType;
    WriterType::Pointer writer = WriterType::New();

    PixelType distanceThreshold = 4;

    ConnectedComponentImageFilterType::Pointer connected = ConnectedComponentImageFilterType::New ();
    connected->SetInput(reader->GetOutput());
    connected->SetDistanceThreshold(distanceThreshold);

    RelabelFilterType::Pointer relabel = RelabelFilterType::New();
    RelabelFilterType::ObjectSizeType minSize = 20;

    relabel->SetInput(connected->GetOutput());
    relabel->SetMinimumObjectSize(minSize);
    relabel->Update();

    *i = relabel->GetNumberOfObjects();

    RGBFilterType::Pointer rgbFilter = RGBFilterType::New();
    rgbFilter->SetInput( relabel->GetOutput() );
    writer->SetFileName(name);
    writer->SetInput(rgbFilter->GetOutput());
    writer->Update();


}
