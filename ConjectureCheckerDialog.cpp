//
// Created by rostam on 27.03.26.
//

#include "ConjectureCheckerDialog.h"
#include "G6Format/G6Format.h"
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/statline.h>
#include <fstream>

// ---------------------------------------------------------------------------
// AddGraphDialog — lets the user pick a generator and fill in n (and k)
// ---------------------------------------------------------------------------

class AddGraphDialog : public wxDialog {
public:
    AddGraphDialog(wxWindow* parent,
                   std::vector<std::unique_ptr<GeneratorInterface>>& generators)
        : wxDialog(parent, wxID_ANY, "Add Graphs",
                   wxDefaultPosition, wxDefaultSize,
                   wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
        , m_generators(generators)
    {
        auto* sizer = new wxBoxSizer(wxVERTICAL);

        // Generator drop-down
        sizer->Add(new wxStaticText(this, wxID_ANY, "Generator:"), 0, wxLEFT | wxTOP, 10);
        wxArrayString names;
        for (auto& g : generators)
            names.Add(wxString(g->name()));
        m_genChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, names);
        m_genChoice->SetSelection(0);
        sizer->Add(m_genChoice, 0, wxEXPAND | wxALL, 6);

        // n range row:  [label]  [from]  "to"  [to]
        auto* nRow = new wxBoxSizer(wxHORIZONTAL);
        m_nLabel   = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(160, -1));
        m_nFromCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1));
        m_nToCtrl   = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1));
        nRow->Add(m_nLabel,    0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        nRow->Add(m_nFromCtrl, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
        nRow->Add(new wxStaticText(this, wxID_ANY, "to"),
                  0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        nRow->Add(m_nToCtrl,   1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);
        sizer->Add(nRow, 0, wxEXPAND | wxTOP, 4);

        // k range row
        auto* kRow = new wxBoxSizer(wxHORIZONTAL);
        m_kLabel    = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(160, -1));
        m_kFromCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1));
        m_kToCtrl   = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1));
        kRow->Add(m_kLabel,    0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        kRow->Add(m_kFromCtrl, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
        kRow->Add(new wxStaticText(this, wxID_ANY, "to"),
                  0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
        kRow->Add(m_kToCtrl,   1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, 5);
        sizer->Add(kRow, 0, wxEXPAND | wxTOP, 4);

        sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxTOP, 10);
        sizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 8);
        SetSizer(sizer);
        Fit();
        SetMinSize(GetSize());
        Centre();

        UpdateFields(0);
        m_genChoice->Bind(wxEVT_CHOICE, &AddGraphDialog::OnGeneratorChanged, this);
    }

    int GetGeneratorIndex() const { return m_genChoice->GetSelection(); }

    unsigned int GetNFrom() const { return readCtrl(m_nFromCtrl); }
    unsigned int GetNTo()   const { return readCtrl(m_nToCtrl); }
    unsigned int GetKFrom() const { return readCtrl(m_kFromCtrl); }
    unsigned int GetKTo()   const { return readCtrl(m_kToCtrl); }

private:
    static unsigned int readCtrl(wxTextCtrl* c) {
        long v = 0;
        c->GetValue().Trim().ToLong(&v);
        return v > 0 ? (unsigned int)v : 0;
    }

    void OnGeneratorChanged(wxCommandEvent&) { UpdateFields(m_genChoice->GetSelection()); }

    void UpdateFields(int idx) {
        if (idx < 0 || idx >= (int)m_generators.size()) return;
        auto& gen = m_generators[idx];

        if (!gen->hasAnyParam()) {
            m_nLabel->SetLabel("(no parameters)");
            m_nFromCtrl->SetValue(""); m_nFromCtrl->Enable(false);
            m_nToCtrl->SetValue("");   m_nToCtrl->Enable(false);
            m_kLabel->SetLabel("");
            m_kFromCtrl->SetValue(""); m_kFromCtrl->Enable(false);
            m_kToCtrl->SetValue("");   m_kToCtrl->Enable(false);
            return;
        }

        m_nLabel->SetLabel(wxString(gen->paramNName()) + ":");
        wxString defN = wxString::Format("%d", gen->defaultN());
        m_nFromCtrl->SetValue(defN); m_nFromCtrl->Enable(true);
        m_nToCtrl->SetValue(defN);   m_nToCtrl->Enable(true);

        bool hasK = gen->hasSecondParam();
        m_kLabel->SetLabel(hasK ? wxString(gen->paramKName()) + ":" : wxString(""));
        wxString defK = wxString::Format("%d", gen->defaultK());
        m_kFromCtrl->SetValue(hasK ? defK : wxString(""));
        m_kToCtrl->SetValue(hasK ? defK : wxString(""));
        m_kFromCtrl->Enable(hasK);
        m_kToCtrl->Enable(hasK);
        m_kLabel->Enable(hasK);
    }

    std::vector<std::unique_ptr<GeneratorInterface>>& m_generators;
    wxChoice*     m_genChoice  = nullptr;
    wxTextCtrl*   m_nFromCtrl  = nullptr;
    wxTextCtrl*   m_nToCtrl    = nullptr;
    wxTextCtrl*   m_kFromCtrl  = nullptr;
    wxTextCtrl*   m_kToCtrl    = nullptr;
    wxStaticText* m_nLabel     = nullptr;
    wxStaticText* m_kLabel     = nullptr;
};

// ---------------------------------------------------------------------------
// ConjectureCheckerDialog
// ---------------------------------------------------------------------------

ConjectureCheckerDialog::ConjectureCheckerDialog(
    wxWindow* parent,
    std::vector<std::unique_ptr<GeneratorInterface>>& generators,
    std::vector<std::unique_ptr<ReportInterface>>&    reports)
    : wxDialog(parent, wxID_ANY, "Conjecture Checker",
               wxDefaultPosition, wxSize(950, 700),
               wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
    , m_generators(generators)
    , m_reports(reports)
{
    auto* main = new wxBoxSizer(wxVERTICAL);

    // ---- Top half: graphs (left) + reports (right) ----
    auto* top = new wxBoxSizer(wxHORIZONTAL);

    // Graphs panel
    auto* graphBox = new wxStaticBoxSizer(wxVERTICAL, this, "Graphs");
    m_graphList = new wxListBox(this, wxID_ANY);
    m_graphList->SetMinSize(wxSize(300, 140));
    graphBox->Add(m_graphList, 1, wxEXPAND | wxALL, 4);

    auto* graphBtns  = new wxBoxSizer(wxHORIZONTAL);
    auto* addBtn     = new wxButton(this, wxID_ANY, "Add Graph");
    auto* addFileBtn = new wxButton(this, wxID_ANY, "Add from G6 File...");
    auto* removeBtn  = new wxButton(this, wxID_ANY, "Remove Selected");
    graphBtns->Add(addBtn,     0, wxRIGHT, 6);
    graphBtns->Add(addFileBtn, 0, wxRIGHT, 6);
    graphBtns->Add(removeBtn,  0);
    graphBox->Add(graphBtns, 0, wxALL, 6);
    top->Add(graphBox, 1, wxEXPAND | wxALL, 6);

    // Reports panel
    auto* reportBox = new wxStaticBoxSizer(wxVERTICAL, this, "Reports");
    wxArrayString reportNames;
    for (auto& r : reports)
        reportNames.Add(wxString(r->name()));
    m_reportList = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                      reportNames);
    m_reportList->SetMinSize(wxSize(300, 140));
    for (unsigned int i = 0; i < reportNames.size(); i++)
        m_reportList->Check(i, true);
    reportBox->Add(m_reportList, 1, wxEXPAND | wxALL, 4);

    auto* reportBtns  = new wxBoxSizer(wxHORIZONTAL);
    auto* selAllBtn   = new wxButton(this, wxID_ANY, "Select All");
    auto* deselAllBtn = new wxButton(this, wxID_ANY, "Deselect All");
    reportBtns->Add(selAllBtn,   0, wxRIGHT, 6);
    reportBtns->Add(deselAllBtn, 0);
    reportBox->Add(reportBtns, 0, wxALL, 6);
    top->Add(reportBox, 1, wxEXPAND | wxALL, 6);

    main->Add(top, 1, wxEXPAND);  // proportion=1: shares vertical space with grid

    // ---- Results grid ----
    m_grid = new wxGrid(this, wxID_ANY);
    m_grid->CreateGrid(0, 1);
    m_grid->SetColLabelValue(0, "Graph");
    m_grid->EnableEditing(false);
    m_grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTRE);
    main->Add(m_grid, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

    // ---- Bottom buttons ----
    auto* btns      = new wxBoxSizer(wxHORIZONTAL);
    auto* computeBtn = new wxButton(this, wxID_ANY, "Compute");
    auto* saveBtn    = new wxButton(this, wxID_ANY, "Save CSV...");
    auto* closeBtn   = new wxButton(this, wxID_CANCEL, "Close");
    btns->Add(computeBtn, 0, wxRIGHT, 8);
    btns->Add(saveBtn,    0);
    btns->AddStretchSpacer();
    btns->Add(closeBtn, 0);
    main->Add(btns, 0, wxEXPAND | wxALL, 8);

    SetSizer(main);

    addBtn->Bind    (wxEVT_BUTTON, &ConjectureCheckerDialog::OnAddGraph,    this);
    addFileBtn->Bind(wxEVT_BUTTON, &ConjectureCheckerDialog::OnAddFromFile, this);
    removeBtn->Bind (wxEVT_BUTTON, &ConjectureCheckerDialog::OnRemoveGraph, this);
    computeBtn->Bind(wxEVT_BUTTON, &ConjectureCheckerDialog::OnCompute,     this);
    saveBtn->Bind   (wxEVT_BUTTON, &ConjectureCheckerDialog::OnSaveCSV,     this);
    selAllBtn->Bind (wxEVT_BUTTON, &ConjectureCheckerDialog::OnSelectAll,   this);
    deselAllBtn->Bind(wxEVT_BUTTON,&ConjectureCheckerDialog::OnDeselectAll, this);
}

void ConjectureCheckerDialog::OnAddGraph(wxCommandEvent&) {
    AddGraphDialog dlg(this, m_generators);
    if (dlg.ShowModal() != wxID_OK) return;

    int idx = dlg.GetGeneratorIndex();
    if (idx < 0 || idx >= (int)m_generators.size()) return;

    auto& gen = m_generators[idx];

    unsigned int nFrom = dlg.GetNFrom(), nTo = dlg.GetNTo();
    unsigned int kFrom = dlg.GetKFrom(), kTo = dlg.GetKTo();
    if (nFrom > nTo) std::swap(nFrom, nTo);
    if (kFrom > kTo) std::swap(kFrom, kTo);

    // Warn if the combination would produce a very large number of graphs
    unsigned int nRange = nTo - nFrom + 1;
    unsigned int kRange = gen->hasSecondParam() ? (kTo - kFrom + 1) : 1;
    if (nRange * kRange > 200) {
        wxString msg = wxString::Format(
            "This will generate %u graphs. Continue?", nRange * kRange);
        if (wxMessageBox(msg, "Large Range", wxYES_NO | wxICON_QUESTION, this) != wxYES)
            return;
    }

    for (unsigned int n = nFrom; n <= nTo; n++) {
        unsigned int kBegin = gen->hasSecondParam() ? kFrom : 0;
        unsigned int kEnd   = gen->hasSecondParam() ? kTo   : 0;
        for (unsigned int k = kBegin; k <= kEnd; k++) {
            std::string label = gen->name();
            if (gen->hasAnyParam()) {
                label += "(" + gen->paramNName() + "=" + std::to_string(n);
                if (gen->hasSecondParam())
                    label += ", " + gen->paramKName() + "=" + std::to_string(k);
                label += ")";
            }
            Graph g = gen->generate(n, k);
            m_graphEntries.push_back({label, std::move(g)});
            m_graphList->Append(wxString(label));
        }
    }
}

void ConjectureCheckerDialog::OnAddFromFile(wxCommandEvent&) {
    wxFileDialog dlg(this, "Open G6 File", "", "",
                     "G6 files (*.g6)|*.g6|All files (*)|*",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if (dlg.ShowModal() != wxID_OK) return;

    wxArrayString paths;
    dlg.GetPaths(paths);
    G6Format g6fmt;

    for (const wxString& path : paths) {
        std::ifstream in(path.ToStdString());
        if (!in) continue;
        std::string basename = wxFileName(path).GetFullName().ToStdString();
        std::string line;
        int count = 0;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') continue;
            std::string label = basename + " #" + std::to_string(++count);
            Graph g = g6fmt.stringToGraph2(line);
            m_graphEntries.push_back({label, std::move(g)});
            m_graphList->Append(wxString(label));
        }
    }
}

void ConjectureCheckerDialog::OnRemoveGraph(wxCommandEvent&) {
    int sel = m_graphList->GetSelection();
    if (sel == wxNOT_FOUND) return;
    m_graphList->Delete(sel);
    m_graphEntries.erase(m_graphEntries.begin() + sel);
}

void ConjectureCheckerDialog::OnCompute(wxCommandEvent&) {
    if (m_graphEntries.empty()) {
        wxMessageBox("Add at least one graph.", "No Graphs", wxOK | wxICON_WARNING, this);
        return;
    }

    // Collect checked reports
    std::vector<ReportInterface*> active;
    for (unsigned int i = 0; i < m_reports.size(); i++)
        if (m_reportList->IsChecked(i))
            active.push_back(m_reports[i].get());

    if (active.empty()) {
        wxMessageBox("Select at least one report.", "No Reports", wxOK | wxICON_WARNING, this);
        return;
    }

    // Rebuild grid
    if (m_grid->GetNumberRows() > 0) m_grid->DeleteRows(0, m_grid->GetNumberRows());
    if (m_grid->GetNumberCols() > 0) m_grid->DeleteCols(0, m_grid->GetNumberCols());

    m_grid->AppendCols(1 + (int)active.size());
    m_grid->SetColLabelValue(0, "Graph");
    for (int c = 0; c < (int)active.size(); c++)
        m_grid->SetColLabelValue(c + 1, wxString(active[c]->name()));

    m_grid->AppendRows((int)m_graphEntries.size());
    for (int r = 0; r < (int)m_graphEntries.size(); r++) {
        m_grid->SetCellValue(r, 0, wxString(m_graphEntries[r].label));
        for (int c = 0; c < (int)active.size(); c++)
            m_grid->SetCellValue(r, c + 1, wxString(active[c]->report(m_graphEntries[r].graph)));
    }

    m_grid->AutoSizeColumns();
}

void ConjectureCheckerDialog::OnSaveCSV(wxCommandEvent&) {
    if (m_grid->GetNumberRows() == 0 || m_grid->GetNumberCols() == 0) {
        wxMessageBox("Nothing to save. Click Compute first.", "Empty Table",
                     wxOK | wxICON_WARNING, this);
        return;
    }

    wxFileDialog dlg(this, "Save CSV", "", "conjecture_results.csv",
                     "CSV files (*.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK) return;

    std::ofstream out(dlg.GetPath().ToStdString());
    if (!out) {
        wxMessageBox("Could not open file for writing.", "Error", wxOK | wxICON_ERROR, this);
        return;
    }

    int nCols = m_grid->GetNumberCols();
    // Header
    for (int c = 0; c < nCols; c++) {
        out << m_grid->GetColLabelValue(c).ToStdString();
        out << (c < nCols - 1 ? "," : "\n");
    }
    // Rows
    for (int r = 0; r < m_grid->GetNumberRows(); r++) {
        for (int c = 0; c < nCols; c++) {
            out << m_grid->GetCellValue(r, c).ToStdString();
            out << (c < nCols - 1 ? "," : "\n");
        }
    }
}

void ConjectureCheckerDialog::OnSelectAll(wxCommandEvent&) {
    for (unsigned int i = 0; i < m_reportList->GetCount(); i++)
        m_reportList->Check(i, true);
}

void ConjectureCheckerDialog::OnDeselectAll(wxCommandEvent&) {
    for (unsigned int i = 0; i < m_reportList->GetCount(); i++)
        m_reportList->Check(i, false);
}
