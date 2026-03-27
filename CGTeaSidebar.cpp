//
// Created by rostam on 15.10.19.
//

#include "CGTeaSidebar.h"
#include <thread>
#include <future>
#include <chrono>

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

    // Snapshot the graph so the background thread has its own copy
    auto graphCopy = std::make_shared<Graph>(frame->currentGraph);

    std::thread([this, frame, graphCopy]() {
        constexpr auto timeout = std::chrono::seconds(30);
        string out;

        for (const auto& gi : frame->availableReports) {
            string reportName = gi->name();

            CallAfter([frame, reportName]() {
                frame->SetStatusText("Computing: " + reportName + "...");
            });

            // Run each report in a detached thread so we can enforce a timeout
            std::promise<string> promise;
            auto future = promise.get_future();
            ReportInterface* ri = gi.get();
            std::thread([ri, graphCopy, p = std::move(promise)]() mutable {
                try {
                    p.set_value(ri->report(*graphCopy));
                } catch (...) {
                    try { p.set_exception(std::current_exception()); } catch (...) {}
                }
            }).detach();

            if (future.wait_for(timeout) == std::future_status::ready) {
                try {
                    out += reportName + ": " + future.get() + "\n";
                } catch (...) {
                    out += reportName + ": (error)\n";
                }
            } else {
                out += reportName + ": (timed out)\n";
            }
        }

        CallAfter([this, frame, out]() {
            statistics_text->SetValue(wxString(out.c_str()));
            frame->SetStatusText("Statistics computed.");
            if (auto* btn = FindWindowById(100, this))
                btn->Enable();
        });
    }).detach();
}
