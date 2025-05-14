//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_CGTEASIDEBAR_H
#define CGTEA_CGTEASIDEBAR_H

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "CGTeaFrame.h"

class CGTeaSidebar : public wxPanel {
public:
    wxTextCtrl* statistics_text = nullptr;
    CGTeaSidebar(CGTeaFrame *parent, wxWindowID winid);
    void computeStat(wxCommandEvent & event);
};


#endif //CGTEA_CGTEASIDEBAR_H
