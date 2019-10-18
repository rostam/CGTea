//
// Created by rostam on 15.10.19.
//

#include "CGTeaSidebar.h"

CGTeaSidebar::CGTeaSidebar(CGTeaFrame *parent, wxWindowID winid) : wxPanel(parent, winid) {

    statistics_text = new wxStaticText (this, wxID_ANY, "",wxDefaultPosition,wxSize(500,800));
    wxFont font = statistics_text->GetFont();
    font.SetPointSize(16);
    statistics_text->SetFont(font);
    wxButton* compute_stat = new wxButton(this, 100, "Compute Statistics");
    Connect(100, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CGTeaSidebar::computeStat));

    wxBoxSizer* panel1Sizer = new wxBoxSizer(wxVERTICAL);
    panel1Sizer->Add(statistics_text, 1, wxEXPAND | wxALL, 8);//, 1, wxLEFT, 8);
    panel1Sizer->Add(compute_stat, 1, wxEXPAND | wxBOTTOM, 8);
    SetSizer(panel1Sizer);
}

void CGTeaSidebar::computeStat(wxCommandEvent & WXUNUSED(event))
{
    auto frame = ((CGTeaFrame*)this->m_parent);
    string out;
    for(auto& gi : frame->availableReports) {
        out += gi->name() + ": " + gi->report(frame->currentGraph) + "\n";
    }
    statistics_text->SetLabelText(wxString(out.c_str()));
}
