//
// Created by rostam on 27.03.26.
//

#ifndef CGTEA_CONJECTURECHECKERDIALOG_H
#define CGTEA_CONJECTURECHECKERDIALOG_H

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/grid.h>
#include <wx/checklst.h>

#include "datatypes.h"
#include "generators/GeneratorInterface.h"
#include "reports/ReportInterface.h"

#include <vector>
#include <string>
#include <memory>

class ConjectureCheckerDialog : public wxDialog {
public:
    ConjectureCheckerDialog(wxWindow* parent,
                            std::vector<std::unique_ptr<GeneratorInterface>>& generators,
                            std::vector<std::unique_ptr<ReportInterface>>& reports);

private:
    void OnAddGraph(wxCommandEvent&);
    void OnRemoveGraph(wxCommandEvent&);
    void OnCompute(wxCommandEvent&);
    void OnSaveCSV(wxCommandEvent&);
    void OnSelectAll(wxCommandEvent&);
    void OnDeselectAll(wxCommandEvent&);

    struct GraphEntry {
        std::string label;
        Graph graph;
    };

    std::vector<std::unique_ptr<GeneratorInterface>>& m_generators;
    std::vector<std::unique_ptr<ReportInterface>>&    m_reports;
    std::vector<GraphEntry>                           m_graphEntries;

    wxListBox*      m_graphList  = nullptr;
    wxCheckListBox* m_reportList = nullptr;
    wxGrid*         m_grid       = nullptr;
};

#endif //CGTEA_CONJECTURECHECKERDIALOG_H
