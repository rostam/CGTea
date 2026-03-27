//
// Created by rostam on 15.10.19.
//

#include "CGTeaSidebar.h"

static const wxColour kRowEven(245, 248, 255);
static const wxColour kRowOdd (255, 255, 255);
static const wxColour kHeaderBg(55, 90, 145);
static const wxColour kHeaderFg(*wxWHITE);

static void fitGridColumns(wxGrid* grid) {
    int w = grid->GetClientSize().GetWidth();
    grid->AutoSizeColumn(0);
    int col1 = w - grid->GetColSize(0);
    if (col1 > 60)
        grid->SetColSize(1, col1);
}

CGTeaSidebar::CGTeaSidebar(wxWindow* parent, wxWindowID winid) : wxPanel(parent, winid) {
    auto* frame = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this));

    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

    statistics_grid = new wxGrid(this, wxID_ANY);
    statistics_grid->CreateGrid((int)frame->availableReports.size(), 2);
    statistics_grid->SetColLabelValue(0, "Report");
    statistics_grid->SetColLabelValue(1, "Value");
    statistics_grid->EnableEditing(false);
    statistics_grid->HideRowLabels();
    statistics_grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTRE);
    statistics_grid->SetDefaultRowSize(22, true);
    statistics_grid->SetColLabelSize(24);

    // Style column headers
    wxFont headerFont = statistics_grid->GetLabelFont();
    headerFont.MakeBold();
    statistics_grid->SetLabelFont(headerFont);
    statistics_grid->SetLabelBackgroundColour(kHeaderBg);
    statistics_grid->SetLabelTextColour(kHeaderFg);

    // Populate report names with zebra striping
    for (int i = 0; i < (int)frame->availableReports.size(); i++) {
        const wxColour& bg = (i % 2 == 0) ? kRowEven : kRowOdd;
        statistics_grid->SetCellValue(i, 0, wxString(frame->availableReports[i]->name()));
        statistics_grid->SetCellBackgroundColour(i, 0, bg);
        statistics_grid->SetCellBackgroundColour(i, 1, bg);
    }

    statistics_grid->Bind(wxEVT_SIZE, [this](wxSizeEvent& e) {
        e.Skip();
        fitGridColumns(statistics_grid);
    });

    auto* compute_stat = new wxButton(this, 100, "Compute Statistics");
    Connect(100, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CGTeaSidebar::computeStat));

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(statistics_grid, 1, wxEXPAND | wxALL, 6);
    sizer->Add(compute_stat,    0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
    SetSizer(sizer);
}

void CGTeaSidebar::computeStat(wxCommandEvent& WXUNUSED(event))
{
    auto* frame = static_cast<CGTeaFrame*>(wxGetTopLevelParent(this));
    const int total = (int)frame->availableReports.size();

    if (auto* btn = FindWindowById(100, this)) btn->Disable();

    for (int i = 0; i < total; i++)
        statistics_grid->SetCellValue(i, 1, "...");
    fitGridColumns(statistics_grid);
    wxSafeYield(frame);

    for (int i = 0; i < total; i++) {
        const std::string& name = frame->availableReports[i]->name();
        frame->SetStatusText(wxString::Format("Computing [%d/%d]: %s", i + 1, total, name));
        wxSafeYield(frame);

        std::string result;
        try {
            result = frame->availableReports[i]->report(frame->currentGraph);
        } catch (...) {
            result = "(error)";
        }
        statistics_grid->SetCellValue(i, 1, wxString(result));
        fitGridColumns(statistics_grid);
        wxSafeYield(frame);
    }

    frame->SetStatusText("Statistics computed.");
    if (auto* btn = FindWindowById(100, this)) btn->Enable();
}
