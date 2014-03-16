#include "ImagePanel.h"

void ImagePanel::OnDraw(wxDC& dc)
{
    if(image.IsOk())
        dc.DrawBitmap( image, 0, 0, false );

}

void ImagePanel::loadFile(wxString file, wxBitmapType format)
{
    image.LoadFile(file);
}

void ImagePanel::saveFile(wxString file)
{
    image.SaveFile(file);
}

ImagePanel::ImagePanel(wxFrame* parent) : wxScrolledWindow(parent)
{
}

 wxImage ImagePanel::getImage()
 {
     return image;
 }

