//
// Created by rostam on 15.10.19.
//

#include "CGTeaApp.h"
#include "CGTeaFrame.h"
#include <wx/grid.h>
#include <wx/splitter.h>
#include "CGTeaSidebar.h"
#include "gtea.xpm"

/*! \mainpage CGTea - A Brief Description.
 * A mini-version of GTea written in C++ in which the view is based on wxWidget.
 * The library part (Model) and the controllers need still a lot of improvements.
 * For now, I am implementing the algorithms, reports, actions... based on the Java code.

 * There are three main dependencies:
 * - The Eigen library should be copied in the main directory.
 * - wxWidget is also needed for the graphic-user interface. However, the library parts can be used without this library.
 * - The boost library should be installed:
     ```
     $ sudo apt-get to install build-essentials libboost-all-dev libmetis-dev metis
     ```
 * \image HTML image.png
 * \section Extension
 * \section Downloads
*/

bool CGTeaApp::OnInit()
{
    wxLog::SetLogLevel(wxLOG_Warning);
    auto* frame = new CGTeaFrame("CGTea", wxPoint(100, 100), wxSize(1200, 700));

    auto* splitter = new wxSplitterWindow(frame, wxID_ANY,
                                          wxDefaultPosition, wxDefaultSize,
                                          wxSP_LIVE_UPDATE | wxSP_THIN_SASH);
    splitter->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

    auto* sidebar = new CGTeaSidebar(splitter, wxID_ANY);
    drawPane = new BasicDrawPane(splitter);
    splitter->SplitVertically(sidebar, drawPane, 290);
    splitter->SetMinimumPaneSize(180);

    frame->sidebar = sidebar;

    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(splitter, 1, wxEXPAND);
    frame->SetSizer(mainSizer);
    frame->SetAutoLayout(true);

    wxBitmap iconBmp(adlpr_e3upj_0);
    wxIcon icon;
    icon.CopyFromBitmap(iconBmp);
    frame->SetIcon(icon);
    frame->Maximize(true);
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(CGTeaApp);