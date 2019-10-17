//
// Created by rostam on 15.10.19.
//

#include "CGTeaApp.h"
#include "CGTeaFrame.h"
#include <wx/grid.h>
#include "CGTeaSidebar.h"


bool CGTeaApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    CGTeaFrame *frame = new CGTeaFrame("CGTea", wxPoint(100, 100), wxSize(1200, 1000) );
    drawPane = new BasicDrawPane( frame );
    sizer->Add(new CGTeaSidebar(frame, wxID_ANY), 1, wxEXPAND | wxALL);
    sizer->Add(drawPane, 1, wxEXPAND | wxALL);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show( true );
    return true;
}

wxIMPLEMENT_APP(CGTeaApp);