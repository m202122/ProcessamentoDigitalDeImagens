#ifndef __IMAGEPANEL_H_
#define __IMAGEPANEL_H_
#include <wx/wx.h>

class ImagePanel : public wxScrolledWindow
{
        wxImage image;

    public:
        ImagePanel(wxFrame* parent);
        void paintNow();

        void render(wxDC& dc);
        void loadFile(wxString file, wxBitmapType format);
        wxImage getImage();
        void OnDraw(wxDC& dc);
        void saveFile(wxString file);

};

#endif // __IMAGEPANEL_H_


