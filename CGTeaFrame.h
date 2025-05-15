//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_CGTEAFRAME_H
#define CGTEA_CGTEAFRAME_H

#include "datatypes.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dir.h>
#include <string>
#endif
#include <memory>

#include "generators/GeneratorInterface.h"
#include "reports/ReportInterface.h"
#include "actions/ActionInterface.h"

#include "G6Format/G6Format.h"

class CGTeaFrame: public wxFrame {
public:
    Graph currentGraph;

    CGTeaFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    VertexShape getCurrentVertexShape() const { return currentVertexShape; }
    EdgeShape getCurrentEdgeShape() const { return currentEdgeShape; }


    std::vector<std::unique_ptr<GeneratorInterface>> availableGenerators;
    std::vector<std::unique_ptr<ReportInterface>> availableReports;
    std::vector<std::unique_ptr<ActionInterface>> availableActions;
protected:
    static const long ID_FIT_WIDTH = wxID_HIGHEST + 1;
    void OnFitWidth(wxCommandEvent &event);

private:
    void Generate(wxCommandEvent &event);
    void Report(wxCommandEvent &event);
    void Layout(wxCommandEvent &event);
    void Action(wxCommandEvent &event);

    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void Open(wxCommandEvent &event);
    void Save(wxCommandEvent &event);

    void OnSettings(wxCommandEvent& event);

    VertexShape currentVertexShape = VertexShape::Circle;
    EdgeShape currentEdgeShape = EdgeShape::Line;



wxDECLARE_EVENT_TABLE();
};


#endif //CGTEA_CGTEAFRAME_H
