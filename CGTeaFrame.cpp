//
// Created by rostam on 15.10.19.
//

#include "CGTeaFrame.h"


wxBEGIN_EVENT_TABLE(CGTeaFrame, wxFrame)
                EVT_MENU(wxID_EXIT, CGTeaFrame::OnExit)
                EVT_MENU(wxID_ABOUT, CGTeaFrame::OnAbout)
wxEND_EVENT_TABLE()



CGTeaFrame::CGTeaFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
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
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CGTeaFrame::Generate));
        i++;
    }

    wxMenu *menuReport = new wxMenu;
    for(ReportInterface* ri : availableReports) {
        menuReport->Append(i, wxString(ri->name().c_str(), wxConvUTF8), wxString(ri->description().c_str(), wxConvUTF8));
        Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CGTeaFrame::Report));
        i++;
    }

    wxMenu *menuLayout = new wxMenu;
    menuLayout->Append(i, "Force-directed drawing", "Force-directed drawing");
    Connect(i,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(CGTeaFrame::Layout));
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

    wxDir dir(wxGetCwd()+"/mats/");
    if ( !dir.IsOpened() )
    {
        // deal with the error here - wxDir would already log an error message
        // explaining the exact reason of the failure
        return;
    }
    
    wxString filename;
    bool cont = dir.GetFirst(&filename);//, filespec, flags);
    while ( cont )
    {
        cout << filename.c_str() << endl;
        cont = dir.GetNext(&filename);
    }
}

void CGTeaFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void CGTeaFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "CGTea is a c++-version of GraphTea, a software for working with graphs.",
                  "CGTea 1.0", wxOK | wxICON_INFORMATION );
}

void CGTeaFrame::Generate(wxCommandEvent& event)
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

void CGTeaFrame::Layout(wxCommandEvent& event)
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

void CGTeaFrame::Report(wxCommandEvent& event)
{

}
