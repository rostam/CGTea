//
// Created by rostam on 15.05.25.
//

#include "SettingsDialog.h"


SettingsDialog::SettingsDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxDefaultSize)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString shapeChoices;
    shapeChoices.Add("Circle");
    shapeChoices.Add("Square");
    shapeChoices.Add("Triangle");
    shapeChoices.Add("Diamond");

    shapeRadioBox = new wxRadioBox(this, wxID_ANY, "Vertex Shape",
                                  wxDefaultPosition, wxDefaultSize,
                                  shapeChoices, 1, wxRA_SPECIFY_COLS);

    mainSizer->Add(shapeRadioBox, 0, wxALL | wxEXPAND, 5);

    wxStdDialogButtonSizer* buttonSizer = new wxStdDialogButtonSizer();
    buttonSizer->AddButton(new wxButton(this, wxID_OK));
    buttonSizer->AddButton(new wxButton(this, wxID_CANCEL));
    buttonSizer->Realize();
    mainSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 5);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

VertexShape SettingsDialog::GetSelectedShape() const {
    switch (shapeRadioBox->GetSelection()) {
    case 0: return VertexShape::Circle;
    case 1: return VertexShape::Square;
    case 2: return VertexShape::Triangle;
    case 3: return VertexShape::Diamond;
    default: return VertexShape::Circle;
    }
}