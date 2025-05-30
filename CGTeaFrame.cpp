//
// Created by rostam on 15.10.19.
//

#include "CGTeaFrame.h"
#include "CGTeaSidebar.h"
#include <wx/filedlg.h>

#include "generators/Cycle.h"
#include "generators/Complete.h"
#include "generators/Antiprism.h"
#include "generators/Prism.h"
#include "generators/Star.h"
#include "generators/Regular.h"
#include "generators/Banana.h"
#include "generators/GeneralizedPeterson.h"
#include "generators/Cmn.h"
#include "generators/Path.h"
#include "generators/Flower.h"
#include "generators/Wheel.h"
#include "generators/Crown.h"
#include "generators/Web.h"
#include "generators/CocktailParty.h"
#include "generators/Gear.h"
#include "generators/Heawood.h"

#include "reports/NumOfVertices.h"
#include "reports/NumOfEdges.h"
#include "reports/MaxDegree.h"
#include "reports/MinDegree.h"
#include "reports/MaxEigenValue.h"
#include "reports/MinEigenValue.h"
#include "reports/SumEigenValues.h"
#include "reports/Diameter.h"
#include "reports/NumOfTriangles.h"

#include "actions/Coloring.h"
#include "actions/LineGraph.h"


#include <memory>

#include "Config.h"
#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(CGTeaFrame, wxFrame)
    EVT_MENU(wxID_ABOUT, CGTeaFrame::OnAbout)
wxEND_EVENT_TABLE()

CGTeaFrame::CGTeaFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    currentVertexShape = Config::LoadVertexShape();
    currentEdgeShape = Config::LoadEdgeShape();

    availableGenerators.emplace_back(std::make_unique<Antiprism>());
    availableGenerators.emplace_back(std::make_unique<Banana>());
    availableGenerators.emplace_back(std::make_unique<Cycle>());
    availableGenerators.emplace_back(std::make_unique<Complete>());
    availableGenerators.emplace_back(std::make_unique<Prism>());
    availableGenerators.emplace_back(std::make_unique<Regular>());
    availableGenerators.emplace_back(std::make_unique<GeneralizedPeterson>());
    availableGenerators.emplace_back(std::make_unique<Cmn>());
    availableGenerators.emplace_back(std::make_unique<Path>());
    availableGenerators.emplace_back(std::make_unique<Flower>());
    availableGenerators.emplace_back(std::make_unique<Star>());
    availableGenerators.emplace_back(std::make_unique<Wheel>());
    availableGenerators.emplace_back(std::make_unique<Crown>());
    availableGenerators.emplace_back(std::make_unique<Web>());
    availableGenerators.emplace_back(std::make_unique<CocktailParty>());
    availableGenerators.emplace_back(std::make_unique<Gear>());
    availableGenerators.emplace_back(std::make_unique<Heawood>());

    availableReports.emplace_back(std::make_unique<NumOfVertices>());
    availableReports.emplace_back(std::make_unique<NumOfEdges>());
    availableReports.emplace_back(std::make_unique<MaxDegree>());
    availableReports.emplace_back(std::make_unique<MinDegree>());
    availableReports.emplace_back(std::make_unique<MaxEigenValue>());
    availableReports.emplace_back(std::make_unique<MinEigenValue>());
    availableReports.emplace_back(std::make_unique<SumEigenValues>());
    availableReports.emplace_back(std::make_unique<GraphDiameter>());
    availableReports.emplace_back(std::make_unique<NumberOfTriangles>());

    availableActions.emplace_back(std::make_unique<Coloring>());
    availableActions.emplace_back(std::make_unique<LineGraph>());

    auto menuFile = std::make_unique<wxMenu>();
    menuFile->Append(1000, "&Open");
    menuFile->Append(1001, "&Save");
    menuFile->Append(1002, "&Settings");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    Connect(1000, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Open));
    Connect(1001, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Save));
    Connect(1002, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::OnSettings));

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::OnExit));

    auto menuGenerate = std::make_unique<wxMenu>();
    int i = 1;
//    std::apply([&](auto&&... args) {((menuGenerate->Append(i, wxString(args.name().c_str(), wxConvUTF8), wxString(args.description().c_str(), wxConvUTF8)),i++), ...);}, availableGenerators);
    for (auto& gi : availableGenerators) {
        menuGenerate->Append(i, wxString(gi->name().c_str(), wxConvUTF8),
                             wxString(gi->description().c_str(), wxConvUTF8));
        Connect(i, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Generate));
        i++;
    }

    auto menuReport = std::make_unique<wxMenu>();
    for (auto& ri : availableReports) {
        menuReport->Append(i, wxString(ri->name().c_str(), wxConvUTF8),
                wxString(ri->description().c_str(), wxConvUTF8));
        Connect(i, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Report));
        i++;
    }

    auto menuAction = std::make_unique<wxMenu>();
    for (auto& ai : availableActions) {
        menuAction->Append(i, wxString(ai->name().c_str(), wxConvUTF8),
                           wxString(ai->description().c_str(), wxConvUTF8));
        Connect(i, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Action));
        i++;
    }

    auto menuLayout = std::make_unique<wxMenu>();
    menuLayout->Append(i, "Force-directed drawing", "Force-directed drawing");
    Connect(i, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::Layout));
    i++;
    menuLayout->Append(i, "&Fit Width", "Fit Graph to Width");
    Connect(i, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(CGTeaFrame::OnFitWidth));
    auto menuHelp = std::make_unique<wxMenu>();
    menuHelp->Append(wxID_ABOUT);
    auto menuBar = std::make_unique<wxMenuBar>();
    menuBar->Append(menuFile.release(), "&File");
    menuBar->Append(menuGenerate.release(), "&Generate");
    menuBar->Append(menuReport.release(), "&Report");
    menuBar->Append(menuAction.release(), "&Action");
    menuBar->Append(menuLayout.release(), "&Layout");
    menuBar->Append(menuHelp.release(), "&Help");
    SetMenuBar(menuBar.release());
    CreateStatusBar();
    SetStatusText("Welcome to CGTea!");

    wxDir dir(wxGetCwd() + "/mats/");
    if (!dir.IsOpened()) {
        // deal with the error here - wxDir would already log an error message
        // explaining the exact reason of the failure
        return;
    }

    wxString filename;
    bool cont = dir.GetFirst(&filename);//, filespec, flags);
    while (cont) {
        cout << filename.c_str() << endl;
        cont = dir.GetNext(&filename);
    }
}

void CGTeaFrame::OnExit(wxCommandEvent&) {
    Close(true);
}

void CGTeaFrame::OnAbout(wxCommandEvent&) {
    wxMessageBox("CGTea is a C++-version of GraphTea, a software for working with graphs.",
                 "CGTea 1.0", wxOK | wxICON_INFORMATION);
}

void CGTeaFrame::Generate(wxCommandEvent& event) {
    wxString valueTyped;
    wxTextEntryDialog myDialog(this, _("n,k"), _("Enter graph parameters"), _("10,0"));
    if (myDialog.ShowModal() == wxID_OK) {
        valueTyped = myDialog.GetValue();
    }
    long value_n, value_k;
    int position_of_comma = valueTyped.find(",");
    if (position_of_comma == -1) return;
    if (!valueTyped.substr(0, position_of_comma).ToLong(&value_n)) { return; }
    if (!valueTyped.substr(position_of_comma + 1).ToLong(&value_k)) { return; }
    int id = event.GetId();
    currentGraph = availableGenerators[id-1]->generate_with_positions(value_n, value_k, 300, 300);
    Refresh();
}

void CGTeaFrame::Layout(wxCommandEvent& event) {
    int id = event.GetId();
    cout << id;
    //    currentGraph = availableGenerators[id]->generate_with_force_directed(10,0,500,500);
    std::vector<cgtea_geometry::Point> pos = compute_force_directed(10, 10, 300, 300, currentGraph);
    int i = 0;
    for_each_v(currentGraph, [&](Ver v) {
        boost::put(boost::vertex_distance, currentGraph, v, pos[i]);
        i++;
    });
    Refresh();
}

void CGTeaFrame::OnFitWidth(wxCommandEvent& event)
{
    // Get the current graph bounds
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for_each_v_const(currentGraph, [&](Ver v) {
        const cgtea_geometry::Point pos = boost::get(boost::vertex_distance, currentGraph, v);
        minX = std::min(minX, pos.x);
        maxX = std::max(maxX, pos.x);
        minY = std::min(minY, pos.y);
        maxY = std::max(maxY, pos.y);
    });

    auto panelSize = this->GetSizer()->GetItem(1)->GetSize();
    double padding = 40;
    double scaleX = (panelSize.GetWidth() - 2 * padding) / (maxX - minX);
    double scaleY = (panelSize.GetHeight() - 2 * padding) / (maxY - minY);

    for_each_v(currentGraph, [&](const Ver v) {
        cgtea_geometry::Point pos = boost::get(boost::vertex_distance, currentGraph, v);
        pos.x = (pos.x - minX) * scaleX + padding;
        pos.y = (pos.y - minY) * scaleY + padding;
        boost::put(boost::vertex_distance, currentGraph, v, pos);
    });
    Refresh();
}


void CGTeaFrame::Report(wxCommandEvent& event) {
    const int id = event.GetId();
    const std::string report_results = availableReports[id - availableGenerators.size() - 1]->report(currentGraph);
    const std::string report_name = availableReports[id - availableGenerators.size() - 1]->name();
    static_cast<CGTeaSidebar*>(this->GetSizer()->GetChildren()[0]->GetWindow())->statistics_text->SetValue(report_name + ": " +report_results);
}

void CGTeaFrame::Action(wxCommandEvent& event) {
    int id = event.GetId();
    currentGraph = availableActions[id - availableGenerators.size() - availableReports.size() - 1]->action(currentGraph);
    Refresh();
}

void CGTeaFrame::Open(wxCommandEvent& event) {
    wxFileDialog *openFileDialog = new wxFileDialog(this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
                                                    _("G6 format files (*.g6)|*.g6|CGTea format files (*.tea)|*.tea|"
                                                      "MTX format files (*.mtx)|*.mtx"),
                                                    wxFD_OPEN);

    if (openFileDialog->ShowModal() == wxID_OK) {
        wxString fileName = openFileDialog->GetPath();
        if (fileName.find(".g6") != std::string::npos) {
            ifstream in(fileName.mb_str());
            std::string g6;
            in >> g6;
            in.close();
            G6Format g6Format;
            currentGraph = g6Format.stringToGraph(g6);
            std::vector<cgtea_geometry::Point> pos = compute_force_directed(10, 10, 300, 300, currentGraph);
            int i = 0;
            for_each_v(currentGraph, [&](Ver v) {
                boost::put(boost::vertex_distance, currentGraph, v, pos[i]);
                i++;
            });
        }
        Refresh();
    }
//    wxFileDialog
//            openFileDialog(this, _("Open XYZ file"), "", "",
//                           "XYZ files (*.xyz)|*.xyz", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
//    ifstream in("test.g6");
//    std::string g6;
//    in >> g6;
//    in.close();
//    G6Format g6Format;
//    currentGraph = g6Format.stringToGraph(g6);
}

void CGTeaFrame::Save(wxCommandEvent& event) {
    wxFileDialog *openFileDialog = new wxFileDialog(this, _("Save a file"), wxEmptyString, wxEmptyString,
                                                    _("G6 format files (*.g6)|*.g6|CGTea format files (*.tea)|*.tea|"
                                                      "MTX format files (*.mtx)|*.mtx"),
                                                    wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (openFileDialog->ShowModal() == wxID_OK) {
//        wxString fileName = openFileDialog->GetPath();
//        wxString fileName = openFileDialog->GetPath();
//        if (fileName.find(".g6") != std::string::npos) {
    }

    G6Format g6Format;
    std::string g6 = g6Format.graphToG6(currentGraph);
    std::cerr << "hre " << g6 << endl;
    ofstream out("test.g6");
    out << g6;
    out.flush();
    out.close();
    cerr << g6 << endl;
}

void CGTeaFrame::OnSettings(wxCommandEvent& event) {
    SettingsDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        currentVertexShape = dialog.GetSelectedShape();
        currentEdgeShape = dialog.GetSelectedEdgeShape();
        Config::SaveVertexShape(currentVertexShape);
        Config::SaveEdgeShape(currentEdgeShape);
        Refresh(); // Redraw the graph with the new vertex shape
    }
}
