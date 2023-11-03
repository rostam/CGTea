//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_CGTEASIDEBAR_H
#define CGTEA_CGTEASIDEBAR_H

#include "datatypes.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include "datatypes.h"
#include <string>
#endif

#include "CGTeaFrame.h"

class CGTeaSidebar : public wxPanel {
public:
    wxTextCtrl* statistics_text = nullptr;
    CGTeaSidebar(CGTeaFrame *parent, wxWindowID winid);
    void computeStat(wxCommandEvent & event);
};


#endif //CGTEA_CGTEASIDEBAR_H
