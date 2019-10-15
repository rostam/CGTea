//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_MYFRAME_H
#define CGTEA_MYFRAME_H

#include "datatypes.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/sizer.h>
#include "datatypes.h"
#include <string>
#endif
#include "generators/Cycle.h"
#include "generators/Complete.h"
#include "generators/Antiprism.h"
#include "generators/Prism.h"
#include "generators/Star.h"
#include "reports/NumOfVertices.h"

class MyFrame: public wxFrame {
public:
    Graph currentGraph;
    wxStaticText* statistics_text = nullptr;
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    std::vector<GeneratorInterface*> availableGenerators =
            vector<GeneratorInterface*>({new Cycle(), new Complete(), new Antiprism(),
                                         new Prism(), new Star()});

    std::vector<ReportInterface*> availableReports =
            vector<ReportInterface*>({new NumOfVertices()});
//    std::tuple<Cycle, Complete, Antiprism> availableGenerators = std::make_tuple(Cycle(), Complete(), Antiprism());

    void Generate(wxCommandEvent &event);

    void Report(wxCommandEvent &event);

    void Layout(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};


#endif //CGTEA_MYFRAME_H
