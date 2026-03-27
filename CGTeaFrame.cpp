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
#include "generators/Tadpole.h"
#include "generators/Helm.h"
#include "generators/Kmn.h"
#include "generators/Pmn.h"
#include "generators/Lollipop.h"
#include "generators/FriendshipGraph.h"

#include "reports/NumOfVertices.h"
#include "reports/NumOfEdges.h"
#include "reports/MaxDegree.h"
#include "reports/MinDegree.h"
#include "reports/AverageDegree.h"
#include "reports/Density.h"
#include "reports/NumConnectedComponents.h"
#include "reports/MaxEigenValue.h"
#include "reports/MinEigenValue.h"
#include "reports/SumEigenValues.h"
#include "reports/GraphEnergy.h"
#include "reports/AlgebraicConnectivity.h"
#include "reports/Diameter.h"
#include "reports/Radius.h"
#include "reports/GirthSize.h"
#include "reports/WienerIndex.h"
#include "reports/NumOfTriangles.h"
#include "reports/HyperWienerIndex.h"
#include "reports/SzegedIndex.h"
#include "reports/NumOfQuadrangle.h"
#include "reports/DegreeDistance.h"
#include "reports/Harary.h"
#include "reports/TotalEccentricityIndex.h"
#include "reports/GutmanIndex.h"
#include "reports/WienerPolarityIndex.h"
#include "reports/EdgeDegree.h"
#include "reports/NumOfStars.h"
#include "reports/AdditiveHarary.h"
#include "reports/ReciprocalDegreeDistance.h"
#include "reports/MostarIndex.cpp"
#include "reports/MWienerIndex.cpp"
#include "reports/MultiplicativeHarary.cpp"

#include "actions/Coloring.h"
#include "actions/LineGraph.h"
#include "ConjectureCheckerDialog.h"
#include "CGTeaSidebar.h"


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
    availableGenerators.emplace_back(std::make_unique<Tadpole>());
    availableGenerators.emplace_back(std::make_unique<Helm>());
    availableGenerators.emplace_back(std::make_unique<Kmn>());
    availableGenerators.emplace_back(std::make_unique<Pmn>());
    availableGenerators.emplace_back(std::make_unique<Lollipop>());
    availableGenerators.emplace_back(std::make_unique<FriendshipGraph>());

    availableReports.emplace_back(std::make_unique<NumOfVertices>());
    availableReports.emplace_back(std::make_unique<NumOfEdges>());
    availableReports.emplace_back(std::make_unique<MaxDegree>());
    availableReports.emplace_back(std::make_unique<MinDegree>());
    availableReports.emplace_back(std::make_unique<AverageDegree>());
    availableReports.emplace_back(std::make_unique<Density>());
    availableReports.emplace_back(std::make_unique<NumConnectedComponents>());
    availableReports.emplace_back(std::make_unique<MaxEigenValue>());
    availableReports.emplace_back(std::make_unique<MinEigenValue>());
    availableReports.emplace_back(std::make_unique<SumEigenValues>());
    availableReports.emplace_back(std::make_unique<GraphEnergy>());
    availableReports.emplace_back(std::make_unique<AlgebraicConnectivity>());
    availableReports.emplace_back(std::make_unique<GraphDiameter>());
    availableReports.emplace_back(std::make_unique<GraphRadius>());
    availableReports.emplace_back(std::make_unique<GraphGirthSize>());
    availableReports.emplace_back(std::make_unique<WienerIndex>());
    availableReports.emplace_back(std::make_unique<NumberOfTriangles>());
    availableReports.emplace_back(std::make_unique<NumberOfQuadrangles>());
    availableReports.emplace_back(std::make_unique<NumberOfStars>());
    availableReports.emplace_back(std::make_unique<EdgeDegree>());
    availableReports.emplace_back(std::make_unique<HyperWienerIndex>());
    availableReports.emplace_back(std::make_unique<HararyIndex>());
    availableReports.emplace_back(std::make_unique<AdditiveHararyIndex>());
    availableReports.emplace_back(std::make_unique<ReciprocalDegreeDistance>());
    availableReports.emplace_back(std::make_unique<SzegedIndex>());
    availableReports.emplace_back(std::make_unique<MostarIndex>());
    availableReports.emplace_back(std::make_unique<DegreeDistance>());
    availableReports.emplace_back(std::make_unique<GutmanIndex>());
    availableReports.emplace_back(std::make_unique<TotalEccentricityIndex>());
    availableReports.emplace_back(std::make_unique<WienerPolarityIndex>());
    availableReports.emplace_back(std::make_unique<MultiplicativeWienerIndex>());
    availableReports.emplace_back(std::make_unique<MultiplicativeHararyIndex>());

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
    auto menuAnalysis = std::make_unique<wxMenu>();
    menuAnalysis->Append(1010, "&Conjecture Checker\tCtrl+J",
                         "Compute reports on multiple graphs and compare results");
    Connect(1010, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(CGTeaFrame::OnConjectureChecker));

    auto menuHelp = std::make_unique<wxMenu>();
    menuHelp->Append(wxID_ABOUT);
    auto menuBar = std::make_unique<wxMenuBar>();
    menuBar->Append(menuFile.release(), "&File");
    menuBar->Append(menuGenerate.release(), "&Generate");
    menuBar->Append(menuReport.release(), "&Report");
    menuBar->Append(menuAction.release(), "&Action");
    menuBar->Append(menuLayout.release(), "&Layout");
    menuBar->Append(menuAnalysis.release(), "&Analysis");
    menuBar->Append(menuHelp.release(), "&Help");
    SetMenuBar(menuBar.release());
    CreateStatusBar();
    SetStatusText("Welcome to CGTea!");

}

void CGTeaFrame::OnExit(wxCommandEvent&) {
    Close(true);
}

void CGTeaFrame::OnAbout(wxCommandEvent&) {
    wxMessageBox("CGTea is a C++-version of GraphTea, a software for working with graphs.",
                 "CGTea 1.0", wxOK | wxICON_INFORMATION);
}

void CGTeaFrame::Generate(wxCommandEvent& event) {
    int id = event.GetId();
    auto& gen = availableGenerators[id - 1];

    long value_n = gen->defaultN();
    long value_k = gen->defaultK();

    if (!gen->hasAnyParam()) {
        // Fixed graph (e.g. Heawood) — no input needed
    } else if (gen->hasSecondParam()) {
        wxString defaultVal = wxString::Format("%ld, %ld", value_n, value_k);
        wxString label = wxString(gen->paramNName()) + ",  " + wxString(gen->paramKName());
        wxTextEntryDialog dlg(this, label, _("Enter graph parameters"), defaultVal);
        if (dlg.ShowModal() != wxID_OK) return;
        wxString val = dlg.GetValue();
        int comma = val.find(",");
        if (comma == wxNOT_FOUND) return;
        if (!val.substr(0, comma).Trim().ToLong(&value_n)) return;
        if (!val.substr(comma + 1).Trim().ToLong(&value_k)) return;
    } else {
        wxString label = wxString(gen->paramNName());
        wxTextEntryDialog dlg(this, label, _("Enter graph parameters"),
                              wxString::Format("%ld", value_n));
        if (dlg.ShowModal() != wxID_OK) return;
        if (!dlg.GetValue().Trim().ToLong(&value_n)) return;
    }

    currentGraph = gen->generate_with_positions(value_n, value_k, 300, 300);
    Refresh();
}

void CGTeaFrame::Layout(wxCommandEvent&) {
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
    const int idx = event.GetId() - (int)availableGenerators.size() - 1;
    const std::string result = availableReports[idx]->report(currentGraph);
    if (sidebar) {
        sidebar->statistics_grid->SetCellValue(idx, 1, wxString(result));
        sidebar->statistics_grid->AutoSizeColumn(1);
    }
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
}

void CGTeaFrame::Save(wxCommandEvent&) {
    wxFileDialog *saveFileDialog = new wxFileDialog(this, _("Save a file"), wxEmptyString, wxEmptyString,
                                                    _("G6 format files (*.g6)|*.g6|CGTea format files (*.tea)|*.tea|"
                                                      "MTX format files (*.mtx)|*.mtx"),
                                                    wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog->ShowModal() == wxID_OK) {
        wxString fileName = saveFileDialog->GetPath();
        if (fileName.find(".g6") != std::string::npos) {
            G6Format g6Format;
            std::string g6 = g6Format.graphToG6(currentGraph);
            ofstream out(fileName.mb_str());
            out << g6;
            out.close();
        }
    }
}

void CGTeaFrame::OnSettings(wxCommandEvent& event) {
    SettingsDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        currentVertexShape = dialog.GetSelectedShape();
        currentEdgeShape = dialog.GetSelectedEdgeShape();
        Config::SaveVertexShape(currentVertexShape);
        Config::SaveEdgeShape(currentEdgeShape);
        Refresh();
    }
}

void CGTeaFrame::OnConjectureChecker(wxCommandEvent&) {
    ConjectureCheckerDialog dlg(this, availableGenerators, availableReports);
    dlg.ShowModal();
}
