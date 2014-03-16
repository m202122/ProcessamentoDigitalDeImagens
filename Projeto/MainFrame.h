#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/textdlg.h>
#include "ImagePanel.h"
#include "filter.h"
#include <cstdio>

class MainFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menufile;
		wxMenu* m_menufilter;
		wxMenu* m_menuSegmentation;
		wxMenu* m_menuTools;
		wxMenu* m_menuhelp;
		wxStatusBar* m_statusBar1;
		ImagePanel* drawPane;
		wxBoxSizer* sizer;
		Filter* filter;

	public:

		MainFrame( wxWindowID id = wxID_ANY, const wxString& title = wxT("Editor de Imagens"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600, 400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();


        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnSaveAs(wxCommandEvent& event);
        void BlackWhite(wxCommandEvent& event);
        void Mean(wxCommandEvent& event);
        void Median(wxCommandEvent& event);
        void Gaussian(wxCommandEvent& event);
        void Laplacian(wxCommandEvent& event);
        void Threshold(wxCommandEvent& event);
        void AutoThreshold(wxCommandEvent& event);
        void Otsu(wxCommandEvent& event);
        void Watershed(wxCommandEvent& event);
        void Statistics(wxCommandEvent& event);
        void Histogram(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()

};

enum
{
    ID_Quit = 1,
    ID_About,
    ID_SaveAs,
    ID_Open,
    ID_BW,
    ID_MEAN,
    ID_MEDIAN,
    ID_GAUSSIAN,
    ID_LAPLACIAN,
    ID_THRESHOLD,
    ID_AUTOTHRES,
    ID_OTSU,
    ID_WATERSHED,
    ID_STATISTICS,
    ID_HISTOGRAM,
};

#endif
