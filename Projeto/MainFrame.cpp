#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Quit, MainFrame::OnQuit)
    EVT_MENU(ID_About, MainFrame::OnAbout)
    EVT_MENU(ID_Open, MainFrame::OnOpen)
    EVT_MENU(ID_SaveAs, MainFrame::OnSaveAs)
    EVT_MENU(ID_BW, MainFrame::BlackWhite)
    EVT_MENU(ID_MEAN, MainFrame::Mean)
    EVT_MENU(ID_MEDIAN, MainFrame::Median)
    EVT_MENU(ID_GAUSSIAN, MainFrame::Gaussian)
    EVT_MENU(ID_LAPLACIAN, MainFrame::Laplacian)
    EVT_MENU(ID_THRESHOLD, MainFrame::Threshold)
    EVT_MENU(ID_AUTOTHRES, MainFrame::AutoThreshold)
    EVT_MENU(ID_OTSU, MainFrame::Otsu)
    EVT_MENU(ID_WATERSHED, MainFrame::Watershed)
    EVT_MENU(ID_STATISTICS, MainFrame::Statistics)
    EVT_MENU(ID_HISTOGRAM, MainFrame::Histogram)
END_EVENT_TABLE()

MainFrame::MainFrame( wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( NULL, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar = new wxMenuBar( 0 );
	m_menufile = new wxMenu();
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menufile, ID_Open, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufile->Append( m_menuItemOpen );

	wxMenuItem* m_menuItemSave;
	m_menuItemSave = new wxMenuItem( m_menufile, ID_SaveAs, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufile->Append( m_menuItemSave );

	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menufile, ID_Quit, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufile->Append( m_menuItemExit );

	m_menubar->Append( m_menufile, wxT("File") );

	m_menufilter = new wxMenu();
	wxMenuItem* m_menuBlackWhite;
	m_menuBlackWhite = new wxMenuItem(m_menufilter, ID_BW, wxString(wxT("Black and White")), wxEmptyString, wxITEM_NORMAL);
	m_menufilter->Append(m_menuBlackWhite);

	wxMenuItem* m_menuMean;
	m_menuMean = new wxMenuItem( m_menufilter, ID_MEAN, wxString( wxT("Mean Filter") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufilter->Append( m_menuMean );

	wxMenuItem* m_menuMedian;
	m_menuMedian = new wxMenuItem( m_menufilter, ID_MEDIAN, wxString( wxT("Median Filter") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufilter->Append( m_menuMedian );

	wxMenuItem* m_menuGaussian;
	m_menuGaussian = new wxMenuItem( m_menufilter, ID_GAUSSIAN, wxString( wxT("Gaussian Filter") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufilter->Append( m_menuGaussian );

	wxMenuItem* m_menuLaplacian;
	m_menuLaplacian = new wxMenuItem( m_menufilter, ID_LAPLACIAN, wxString( wxT("Laplacian Filter") ) , wxEmptyString, wxITEM_NORMAL );
	m_menufilter->Append( m_menuLaplacian );

	m_menubar->Append( m_menufilter, wxT("Filter") );

	m_menuSegmentation = new wxMenu();
	wxMenuItem* m_menuThreshold = new wxMenuItem( m_menuSegmentation, ID_THRESHOLD, wxString( wxT("Thresholding") ) , wxEmptyString, wxITEM_NORMAL );
    m_menuSegmentation->Append(m_menuThreshold);

    wxMenuItem* m_menuAutoThres = new wxMenuItem( m_menuSegmentation, ID_AUTOTHRES, wxString( wxT("Auto Thresholding") ) , wxEmptyString, wxITEM_NORMAL );
    m_menuSegmentation->Append(m_menuAutoThres);

    wxMenuItem* m_menuOtsu = new wxMenuItem( m_menuSegmentation, ID_OTSU, wxString( wxT("Otsu") ) , wxEmptyString, wxITEM_NORMAL );
    m_menuSegmentation->Append(m_menuOtsu);

    wxMenuItem* m_menuWater = new wxMenuItem( m_menuSegmentation, ID_WATERSHED, wxString( wxT("Watershed") ) , wxEmptyString, wxITEM_NORMAL );
    m_menuSegmentation->Append(m_menuWater);

    m_menubar->Append(m_menuSegmentation, wxT("Segmentation"));

	m_menuTools = new wxMenu();
	wxMenuItem* m_menuHistogram;
	m_menuHistogram = new wxMenuItem( m_menuTools, ID_HISTOGRAM, wxString( wxT("Histogram") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuHistogram );
	wxMenuItem* m_menuStatistics = new wxMenuItem( m_menuTools, ID_STATISTICS, wxString( wxT("Connected objects") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuTools->Append( m_menuStatistics );

	m_menubar->Append( m_menuTools, wxT("Tools") );

	m_menuhelp = new wxMenu();
	wxMenuItem* m_menuItemAbout;
	m_menuItemAbout = new wxMenuItem( m_menuhelp, ID_About, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuhelp->Append( m_menuItemAbout );

	m_menubar->Append( m_menuhelp, wxT("Help") );

	this->SetMenuBar( m_menubar );

	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );

	sizer = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new ImagePanel(this);
	sizer->Add(drawPane, 1, wxEXPAND, 5);

    this->SetSizer(sizer);
    this->Layout();

	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("Trabalho de PDI\n\n Grupo:    Gustavo Alves Falleiros\n               Marco Aurelio Bosque\n               Rodrigo Moraes Pinto"), _("Editor de imagens"), wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{

    wxFileDialog openFileDialog(this, _("Open image file"), "", "", "Image files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::cout << openFileDialog.GetPath();
    std::cout.flush();
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    drawPane->loadFile(openFileDialog.GetPath(), wxBITMAP_DEFAULT_TYPE);
    int w = drawPane->getImage().GetWidth();
    int h = drawPane->getImage().GetHeight();
    drawPane->SetScrollbars( 1, 1, w, h, 0, 0 );
    filter = new Filter(openFileDialog.GetPath().mb_str());
    const wxSize& size = wxSize( w > 800 ? 800 : w, h > 600 ? 600 : h);
    sizer->SetMinSize(size);
    sizer->Fit(this);
    m_statusBar1->SetStatusText(wxT("Image loaded"), 0);
}

void MainFrame::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        wxFileDialog saveFileDialog(this, _("Save image file"), "", "", "Image files (*.jpg)|*.jpg", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL)
            return;
        wxFileOutputStream output_stream(saveFileDialog.GetPath());
        if (!output_stream.IsOk())
        {
            wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
                return;
        }
        drawPane->saveFile(saveFileDialog.GetPath());
        m_statusBar1->SetStatusText(wxT("Image saved!"), 0);
    }
}

void MainFrame::BlackWhite(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        filter->toBlackWhite("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Original black and white"),0);
    }

}


void MainFrame::Mean(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        m_statusBar1->SetStatusText(wxT("Applying mean filter..."),0);
        filter->meanFilter("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Mean filter"),0);
    }
}
void MainFrame::Median(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        m_statusBar1->SetStatusText(wxT("Applying median filter..."),0);
        filter->medianFilter("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Median filter"),0);
    }

}
void MainFrame::Gaussian(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        double sigma = 1.0;
        long int maxKernelSize = 50;
        wxTextEntryDialog dialog(this, "Enter sigma value. Default = 1.0", "Sigma", "1", wxOK | wxCANCEL);
        if (dialog.ShowModal() == wxID_OK)
        {
            if(!dialog.GetValue().ToDouble(&sigma))
                wxMessageBox( _("Not a number! Using default."), _("Error"), wxOK | wxICON_INFORMATION, this);
            wxTextEntryDialog dialog(this,"Enter max kernel size. Default = 50","Max kernel size","50", wxOK | wxCANCEL);
            if(dialog.ShowModal() == wxID_OK)
            {
                if(!dialog.GetValue().ToLong(&maxKernelSize))
                    wxMessageBox( _("Not a number! Using default."), _("Error"), wxOK | wxICON_INFORMATION, this);

                m_statusBar1->SetStatusText(wxT("Applying gaussian filter..."),0);
                filter->gaussianFilter("temp.jpg", sigma, maxKernelSize);
                drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
                remove("temp.jpg");
                Refresh();
                m_statusBar1->SetStatusText(wxT("Gaussian filter"),0);
            }

        }
    }
}

void MainFrame::Laplacian(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        m_statusBar1->SetStatusText(wxT("Applying laplacian filter..."),0);
        filter->laplacianFilter("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Laplacian filter"),0);
    }

}

void MainFrame::Threshold(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        long int upper = 200;
        long int lower = 100;

        wxTextEntryDialog dialog(this, "Enter lower Threshold value[0,255]. Default = 100", "Lower", "100", wxOK | wxCANCEL);
        if (dialog.ShowModal() == wxID_OK)
        {
            if(!dialog.GetValue().ToLong(&lower))
                wxMessageBox( _("Not a number! Using default."), _("Error"), wxOK | wxICON_INFORMATION, this);
            wxTextEntryDialog dialog(this, "Enter upper Threshold value[0,255]. Default = 200", "Upper", "200", wxOK | wxCANCEL);
            if (dialog.ShowModal() == wxID_OK)
            {
                if(!dialog.GetValue().ToLong(&upper))
                    wxMessageBox( _("Not a number! Using default."), _("Error"), wxOK | wxICON_INFORMATION, this);
                m_statusBar1->SetStatusText(wxT("Applying threshold segmentation..."),0);
                filter->threshold("temp.jpg",lower,upper);
                drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
                remove("temp.jpg");
                Refresh();
                m_statusBar1->SetStatusText(wxT("Threshold segmentation"),0);

            }
        }
    }
}

void MainFrame::AutoThreshold(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        m_statusBar1->SetStatusText(wxT("Applying auto threshold segmentation..."),0);
        filter->autoThreshold("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Auto threshold segmentation"),0);

    }
}

void MainFrame::Otsu(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        m_statusBar1->SetStatusText(wxT("Applying otsu segmentation..."),0);
        filter->otsu("temp.jpg");
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxT("Otsu segmentation"),0);

    }
}

void MainFrame::Watershed(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        double level = 0.25;
        wxTextEntryDialog dialog(this, "Enter Level value[0,1]. Default = 0.25", "Level", "0.25", wxOK | wxCANCEL);
        if (dialog.ShowModal() == wxID_OK)
        {
            if(!dialog.GetValue().ToDouble(&level))
                wxMessageBox( _("Not a number! Using default."), _("Error"), wxOK | wxICON_INFORMATION, this);
            m_statusBar1->SetStatusText(wxT("Applying watershed segmentation..."),0);
            filter->watershed("temp.jpg",level);
            drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
            remove("temp.jpg");
            Refresh();
            m_statusBar1->SetStatusText(wxT("Watershed segmentation"),0);
        }

    }
}

void MainFrame::Statistics(wxCommandEvent& WXUNUSED(event))
{

    if(drawPane->getImage().IsOk())
    {
        int i = 0;
        m_statusBar1->SetStatusText(wxT("Labeling connected objects..."),0);
        filter->connectedObjects("temp.jpg",&i);
        drawPane->loadFile(wxString(wxT("temp.jpg")), wxBITMAP_DEFAULT_TYPE);
        remove("temp.jpg");
        Refresh();
        m_statusBar1->SetStatusText(wxString::Format(wxT("Connected objects: %i"),i),0);
    }
}

void MainFrame::Histogram(wxCommandEvent& WXUNUSED(event))
{
    if(drawPane->getImage().IsOk())
    {
        filter->imageHistogram("null");
    }
}
