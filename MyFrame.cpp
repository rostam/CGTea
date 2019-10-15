//
// Created by rostam on 15.10.19.
//

#include "MyFrame.h"


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
                EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()



MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
//    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H","Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuGenerate = new wxMenu;
    int i=0;
//    std::apply([&](auto&&... args) {((menuGenerate->Append(i, wxString(args.name().c_str(), wxConvUTF8), wxString(args.description().c_str(), wxConvUTF8)),i++), ...);}, availableGenerators);
    for(GeneratorInterface* gi : availableGenerators) {
        menuGenerate->Append(i, wxString(gi->name().c_str(), wxConvUTF8), wxString(gi->description().c_str(), wxConvUTF8));
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Generate));
        i++;
    }

    wxMenu *menuReport = new wxMenu;
    for(ReportInterface* ri : availableReports) {
        menuReport->Append(i, wxString(ri->name().c_str(), wxConvUTF8), wxString(ri->description().c_str(), wxConvUTF8));
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Report));
        i++;
    }

    wxMenu *menuLayout = new wxMenu;
    menuLayout->Append(i, "Force-directed drawing", "Force-directed drawing");
    Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::Layout));
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append(menuGenerate, "&Generate");
    menuBar->Append(menuReport, "&Report");
    menuBar->Append(menuLayout, "&Layout");
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "CGTea is a c++-version of GraphTea, a software for working with graphs.",
                  "CGTea 1.0", wxOK | wxICON_INFORMATION );
}

void MyFrame::Generate(wxCommandEvent& event)
{
    wxString valueTyped;
    wxTextEntryDialog myDialog(this, _("n"), _("Enter graph parameters"), _("10"));
    if ( myDialog.ShowModal() == wxID_OK ) {
        valueTyped = myDialog.GetValue();
    }
    long value;
    if(!valueTyped.ToLong(&value)) { return; }

    int id = event.GetId();
    currentGraph = availableGenerators[id]->generate_with_positions(value, 0, 300, 300);
    this->statistics_text->SetLabelText(wxString(statistics(currentGraph)));
    Refresh();
}

void MyFrame::Layout(wxCommandEvent& event)
{
//    int id = event.GetId();
//    currentGraph = availableGenerators[id]->generate_with_force_directed(10,0,500,500);
    std::vector<cgtea_geometry::Point> pos = compute_force_directed(10,10, 300, 300, currentGraph);
    int i = 0;
    for_each_v(currentGraph, [&](Ver v) {
        boost::put(boost::vertex_distance, currentGraph, v, pos[i]);
        i++;
    });
    Refresh();
}

void MyFrame::Report(wxCommandEvent& event)
{

}
