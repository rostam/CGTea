//
// Created by rostam on 15.10.19.
//

#include "CGTeaApp.h"
#include "CGTeaFrame.h"


bool CGTeaApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    CGTeaFrame *frame = new CGTeaFrame("CGTea", wxPoint(100, 100), wxSize(1000, 1000) );

    // Create the sidebar
    wxPanel* panel1 = new wxPanel(frame, wxID_ANY);
    wxStaticText * textStatistics = new wxStaticText (panel1, wxID_ANY, L"Statistics",wxDefaultPosition, wxSize(350, 15));
    wxFont font = textStatistics->GetFont();
    font.SetPointSize(14);
    font.SetWeight(wxFONTWEIGHT_BOLD);
    textStatistics->SetFont(font);
    wxString string1="Number of vertices:\nNumber of edges:\nMaximum degree:\nMaximum eigenvalue:\n"
                     "Minimum eigenvalue:\nSum of eigenvalues:";
    frame->statistics_text = new wxStaticText (panel1, wxID_ANY, string1,wxDefaultPosition, wxDefaultSize);
    wxFont font2 = frame->statistics_text->GetFont();
    font2.SetPointSize(14);
    frame->statistics_text->SetFont(font2);
    wxBoxSizer* panel1Sizer = new wxBoxSizer(wxVERTICAL);
    panel1Sizer->Add(textStatistics, 1, wxLEFT, 8);
    panel1Sizer->Add(frame->statistics_text, 1, wxLEFT, 8);
    panel1->SetSizer(panel1Sizer);

    drawPane = new BasicDrawPane( frame );
    sizer->Add(panel1);
    sizer->Add(drawPane, 1, wxEXPAND);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show( true );

    return true;
}

wxIMPLEMENT_APP(CGTeaApp);