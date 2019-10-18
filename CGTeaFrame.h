//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_CGTEAFRAME_H
#define CGTEA_CGTEAFRAME_H

#include "datatypes.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include "datatypes.h"
#include <string>
#endif
#include <memory>

#include "generators/Cycle.h"
#include "generators/Complete.h"
#include "generators/Antiprism.h"
#include "generators/Prism.h"
#include "generators/Star.h"
#include "generators/Regular.h"
#include "generators/Banana.h"
#include "reports/NumOfVertices.h"
#include "reports/NumOfEdges.h"
#include "reports/MaxDegree.h"
#include "reports/MaxEigenValue.h"
#include "reports/MinEigenValue.h"
#include "reports/SumEigenValues.h"
#include "G6Format/G6Format.h"

class CGTeaFrame: public wxFrame {
public:
    Graph currentGraph;

    CGTeaFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    std::vector<std::unique_ptr<GeneratorInterface>> availableGenerators;
    std::vector<std::unique_ptr<ReportInterface>> availableReports;
//    std::tuple<Cycle, Complete, Antiprism> availableGenerators = std::make_tuple(Cycle(), Complete(), Antiprism());
private:

    void Generate(wxCommandEvent &event);
    void Report(wxCommandEvent &event);
    void Layout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void Open(wxCommandEvent &event);
    void Save(wxCommandEvent &event);

wxDECLARE_EVENT_TABLE();
};


#endif //CGTEA_CGTEAFRAME_H
