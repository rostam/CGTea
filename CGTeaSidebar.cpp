//
// Created by rostam on 15.10.19.
//

#include "CGTeaSidebar.h"
#include <thread>

CGTeaSidebar::CGTeaSidebar(CGTeaFrame *parent, wxWindowID winid) : wxPanel(parent, winid) {

    statistics_text = new wxTextCtrl (this, wxID_ANY, "",wxDefaultPosition,wxSize(500,400),
            wxHSCROLL | wxST_NO_AUTORESIZE | wxTE_MULTILINE | wxTE_RICH2 | wxTE_NOHIDESEL);
    wxFont font = statistics_text->GetFont();
    font.SetPointSize(16);
    statistics_text->SetFont(font);
    auto compute_stat = std::make_unique<wxButton>(this, 100, "Compute Statistics");
    Connect(100, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CGTeaSidebar::computeStat));
    auto panel1Sizer = std::make_unique<wxBoxSizer>(wxVERTICAL);
    panel1Sizer->Add(statistics_text, 4, wxEXPAND | wxALL, 8);//, 1, wxLEFT, 8);
    panel1Sizer->Add(compute_stat.release(), 1, wxEXPAND | wxBOTTOM, 8);
    SetSizer(panel1Sizer.release());
}

void CGTeaSidebar::computeStat(wxCommandEvent & WXUNUSED(event))
{
    auto frame = static_cast<CGTeaFrame*>(this->m_parent);

    if (auto* btn = FindWindowById(100, this))
        btn->Disable();
    statistics_text->SetValue("Computing...");
    frame->SetStatusText("Computing statistics...");

    // Snapshot graph and report list before leaving the main thread
    auto graphCopy = std::make_shared<Graph>(frame->currentGraph);
    std::vector<ReportInterface*> reports;
    for (const auto& r : frame->availableReports)
        reports.push_back(r.get());

    std::thread([this, frame, graphCopy, reports]() {
        std::string out;
        for (auto* ri : reports) {
            std::string name = ri->name();
            CallAfter([frame, name]() {
                frame->SetStatusText("Computing: " + name + "...");
            });
            try {
                out += name + ": " + ri->report(*graphCopy) + "\n";
            } catch (...) {
                out += name + ": (error)\n";
            }
        }
        CallAfter([this, frame, out]() {
            statistics_text->SetValue(wxString(out));
            frame->SetStatusText("Statistics computed.");
            if (auto* btn = FindWindowById(100, this))
                btn->Enable();
        });
    }).detach();
}
