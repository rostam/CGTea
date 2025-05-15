//
// Created by rostam on 15.05.25.
//

#ifndef CGTEA_SETTINGSDIALOG_H
#define CGTEA_SETTINGSDIALOG_H

#include <wx/wx.h>
#include <wx/radiobox.h>
#include "const_values.h"

class SettingsDialog : public wxDialog {
public:
    explicit SettingsDialog(wxWindow* parent);
    VertexShape GetSelectedShape() const;
    EdgeShape GetSelectedEdgeShape() const;


private:
    wxRadioBox* shapeRadioBox;
    wxRadioBox* edgeShapeRadioBox;

};

#endif //CGTEA_SETTINGSDIALOG_H

