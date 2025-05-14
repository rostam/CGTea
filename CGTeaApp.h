//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_CGTEAAPP_H
#define CGTEA_CGTEAAPP_H

#include "BasicDrawPane.h"

class CGTeaApp: public wxApp {
    BasicDrawPane * drawPane = nullptr;
public:
    bool OnInit() override;
};

#endif //CGTEA_CGTEAAPP_H
