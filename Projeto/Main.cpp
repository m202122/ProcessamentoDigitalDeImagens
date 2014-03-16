#include "MainFrame.h"
#include <wx/sizer.h>


class Main: public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    wxInitAllImageHandlers();

	MainFrame *frame = new MainFrame();

    frame->Show(true);

    SetTopWindow(frame);
    return true;
}
