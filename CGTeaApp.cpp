//
// Created by rostam on 15.10.19.
//

#include "CGTeaApp.h"
#include "CGTeaFrame.h"
#include <wx/grid.h>
#include "CGTeaSidebar.h"

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
    auto sizer = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    auto frame = new CGTeaFrame("CGTea", wxPoint(100, 100), wxSize(1200, 600) );
    auto cgTeaSidebar = new CGTeaSidebar(frame, wxID_ANY);
    drawPane = new BasicDrawPane( frame );
    sizer->Add(cgTeaSidebar, 1, wxEXPAND | wxALL);
    sizer->Add(drawPane, 4, wxEXPAND | wxALL);
    frame->SetSizer(sizer.release());
    frame->SetAutoLayout(true);
    frame->SetIcon(wxIcon(wxT("gtea.xpm")));
    frame->Show( true );
    return true;
}

wxIMPLEMENT_APP(CGTeaApp);