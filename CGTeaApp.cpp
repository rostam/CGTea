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

    // Create the sidebar
    wxPanel* panel1 = new wxPanel(frame, wxID_ANY);
    wxString string1="Number of vertices:\nNumber of edges:\nMaximum degree:\nMaximum eigenvalue:\n"
                     "Minimum eigenvalue:\nSum of eigenvalues:";
//    frame->statistics_text = new wxStaticText (panel1, wxID_ANY, string1,wxDefaultPosition, wxDefaultSize);
    drawPane = new BasicDrawPane( frame );
    sizer->Add(new CGTeaSidebar(frame, wxID_ANY), 1, wxEXPAND | wxALL);
    sizer->Add(drawPane, 1, wxEXPAND | wxALL);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show( true );
    return true;
}

wxIMPLEMENT_APP(CGTeaApp);